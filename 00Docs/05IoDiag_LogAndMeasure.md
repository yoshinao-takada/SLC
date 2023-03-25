# Diagnostics-Logging
This module defines the following functions.
* Logging with log levels, ERR, INF, DBG,
* Stop watch with multiple beginning of watching,
* Macros of standard calling signature of logging functions

## Basic logging functions and macros
```
#include <stdio.h>
#include <pthread.h>
typedef enum {
    SLC_LogLevelNONE = 0, // disable output
    SLC_LogLevelERR = 1, // output only ERR
    SLC_LogLevelINF = 2, // output ERR and INF
    SLC_LogLevelDBG = 4, // output ERR, INF, and DBG
    SLC_LogLevelPERF = 8, // output performance test message
    SLC_LogLevelTEST = 16, // output test message
} SLC_LogLevel_t;

// Log-sink file.
// NULL disables logging. Default value is stdout.
extern FILE* SLC_LogSink = stdout;

// Log level
extern SLC_LogLevel_t SLC_LogLevel = SLC_LogLevelNONE;

// write timestamp and log-level
void SLC_LogWriteHeader(SLC_LogLevel_t loglevel);

void SLC_LogWriteErrHeader(intt err);

// Error log output
#define SLC_LogERR(err, ...) if ((SLC_LogSink) && (SLC_LogLevel & (int)SLC_LogLevelERR)) { \
    SLC_LogWriteErrHeader(err); \
    fprintf(SLC_LogSink, __VA_ARGS__); \
}

// Info log output
#define SLC_LogINF(...) if ((SLC_LogSink) && (SLC_LogLevel & (int)SLC_LogLevelINF)) { \
    SLC_LogWriteHeader(SLC_LogLevelINF); fprintf(SLC_LogSink, __VA_ARGS__); }

// Debug log output
#define SLC_LogDBG(...) if ((SLC_LogSink) && (SLC_LogLevel & (int)SLC_LogLevelDBG)) { \
    SLC_LogWriteHeader(SLC_LogLevelDBG); fprintf(SLC_LogSink, __VA_ARGS__); }

// Performance test log output
#define SLC_LogPERF(...) if ((SLC_LogSink) && (SLC_LogLevel & (int)SLC_LogLevelPERF)) { \
    SLC_LogWriteHeader(SLC_LogLevelPERF); fprintf(SLC_LogSink, __VA_ARGS__); }

// Test log output
#define SLC_LogTEST(...) if ((SLC_LogSink) && (SLC_LogLevel & (int)SLC_LogLevelTEST)) { \
    SLC_LogWriteHeader(SLC_LogLevelTEST); fprintf(SLC_LogSink, __VA_ARGS__); }
```

## Stopwatch and logging
Stopwatch message is always written in the loglevel SLC_LogLevelPERF.
All stopwatch operations are recorded in performance log.

```
// initialize stopwatch.
void SLC_Stopwatch_Init(SLC_size_t channels, SLC_size_t caption_length);

// Release the resources initialized by SLC_Stopwatch_Init.
void SLC_Stopwatch_Destroy();

// Start time measurement using a selected channel.
SLC_i32_t SLC_Stopwatch_Start(const char* caption);

// Measure and record time.
void SLC_Stopwatch_Measure(SLC_i32_t channel_index);

// Release the channel.
void SLC_Stopwatch_Release(SLC_i32_t channel_index);

// Difference between two timespec instances
void SLC_Timespec_A_minus_B(struct timespec& a_minus_b, struct timespec& a, struct timespec& b);
```
## Test utility functions and macros
Comparison macros
```
// SLC_<NTID>_abs(__numbre) are defined in SLC_Numbers.h.
#include "SLC/SLC_Numbers.h"

#define SLC_<NTID>_sumabs(__a, __b) (SLC_<NTID>_abs(__a) + SLC_<NTID>_abs(__b))
#define SLC_<NTID>_absdiff(__a, __b) SLC_<NTID>_abs((__a) - (__b))
#define SLC_<NTID>_relabsdiff(__a, __b) SLC_<NTID>_absdiff(__a, __b) / SLC_<NTID>_sumabs(__a, __b)
#define SLC_<NTID>_areequal(__a, __b, __tol) \
    ((SLC_<NTID>_abs(__a) < __tol) || (SLC_<NTID>_abs(__b) < __tol)) ? \
    (SLC_<NTID>_absdiff(__a, __b) < __tol) : (SLC_<NTID>_relabsdiff(__a, __b) < __tol)

// standard test method signature
typedef SLC_errno_t (*SLC_TESTMETHOD)(SLC_i32_t settings);

// test method calling macro
#define SLC_TEST_ABORT_ON_FAIL  1
#define SLC_test(__errno, __method_to_test, __setting, __func, __line) \
    __errno = __method_to_test(__setting); \
    if (__errno) { \
        SLC_LogERR(__errno, "setting=%d(0x%x), func=%s, line=%d", __setting, __setting, __func, __line); \
        if (SLC_TEST_ABORT_ON_FAIL) break; }
#define SLC_testend(__errno, __func, __line) \
    SLC_LogTEST("errno=0x%x(%d) @ %s,%d\n", __errno, __errno, __func, __line)
```