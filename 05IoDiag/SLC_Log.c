#define SLC_LOG_C_
#include "SLC/SLC_Log.h"
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>

static const char* LogLabelERR = "ERR";
static const char* LogLabels[] = { NULL, "INF", "DBG", NULL, "PERF", NULL, NULL, NULL,
    "TEST" };

void SLC_LogWriteHeader(SLC_LogLevel_t loglevel)
{
    struct timespec ts;
    struct tm tm;
    clock_gettime(CLOCK_REALTIME, &ts);
    localtime_r(&ts.tv_sec, &tm);
    fprintf(SLC_LogSink, "%04d-%02d-%02d %02d:%02d:%02d.%06ld,%s,",
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,
        ts.tv_nsec/1000, LogLabels[loglevel >> 1]);
}

void SLC_LogWriteErrHeader(SLC_errno_t err)
{
    struct timespec ts;
    struct tm tm;
    clock_gettime(CLOCK_REALTIME, &ts);
    localtime_r(&ts.tv_sec, &tm);
    fprintf(SLC_LogSink, "%04d-%02d-%02d %02d:%02d:%02d.%06ld,%s,0x%08x(%d)",
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,
        ts.tv_nsec/1000, LogLabelERR, err, err);
}

static pthread_spinlock_t lock;
typedef struct {
    struct timespec start;
    char caption[0];
} StopwatchEntry_t, *pStopwatchEntry_t;

static pStopwatchEntry_t entries = NULL;
static size_t entrysize = 0;
static size_t entrycount = 0;
static size_t caption_buffersize = 0;

void SLC_Stopwatch_Init(SLC_size_t channels, SLC_size_t caption_length)
{
    entrysize = SLC_ALIGN8(sizeof(StopwatchEntry_t)) + SLC_ALIGN8(caption_length);
    entries = (pStopwatchEntry_t)aligned_alloc(8, entrysize * channels);
    entrycount = channels;
    memset(entries, 0, entrysize * channels);
    assert(0 == pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE));
    caption_buffersize = caption_length;
}

void SLC_Stopwatch_Destroy()
{
    free(entries);
    entries = NULL;
    entrysize = entrycount = 0;
    assert(0 == pthread_spin_destroy(&lock));
}

#define Stopwatch_ENTRY(__index) (pStopwatchEntry_t)(((uint8_t*)entries) + (__index) * entrysize)

static SLC_i32_t UnusedEntry()
{
    SLC_i32_t found = -1;
    for (size_t i = 0; i < entrycount; i++)
    {
        pStopwatchEntry_t entry = Stopwatch_ENTRY(i);
        if (entry->start.tv_sec != 0)
        {
            found = (SLC_i32_t)i;
            break;
        }
    }
    return found;
}

SLC_i32_t SLC_Stopwatch_Start(const char* caption)
{
    SLC_i32_t entry_index = UnusedEntry();
    if (-1 == entry_index)
    { // no entry is available.
        SLC_LogERR(ENOBUFS, "No Stopwatch entry.\n");
        return entry_index;
    }
    if (strlen(caption) + 1 > caption_buffersize)
    {
        SLC_LogERR(E2BIG, "caption:\"%s\" too long/n", caption);
        return -1;
    }
    pStopwatchEntry_t entry = Stopwatch_ENTRY(entry_index);
    strcpy(entry->caption, caption);
    clock_gettime(CLOCK_REALTIME, &entry->start);
    return entry_index;
}

void SLC_Stopwatch_Measure(SLC_i32_t channel_index)
{
    pStopwatchEntry_t entry = Stopwatch_ENTRY(channel_index);
    struct timespec now, elapsed;
    clock_gettime(CLOCK_REALTIME, &now);
    SLC_Timespec_A_minus_B(&elapsed, &now, &entry->start);
    SLC_LogPERF("elapsed time = %ld.%06ld [sec]\n", elapsed.tv_sec, elapsed.tv_nsec / 1000);
}

void SLC_Stopwatch_Release(SLC_i32_t channel_index)
{
    pStopwatchEntry_t entry = Stopwatch_ENTRY(channel_index);
    memset(entry, 0, entrysize);
}

void SLC_Timespec_A_minus_B(
    struct timespec* a_minus_b, struct timespec* a, struct timespec* b
) {
    if (b->tv_nsec > a->tv_nsec)
    {
        b->tv_nsec += 1000000000;
        b->tv_sec--;
    }
    a_minus_b->tv_sec = a->tv_sec - b->tv_sec;
    a_minus_b->tv_nsec = a->tv_nsec - b->tv_nsec;
}