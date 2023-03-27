#if !defined(SLC_LOG_H_)
#define SLC_LOG_H_
#include "SLC/SLC_Numbers.h"
#include "SLC/SLC_errno.h"
#include <stdio.h>
#include <pthread.h>
#pragma region Loggging_related_definitions
typedef enum {
    SLC_LogLevelNONE = 0, // disable output
    SLC_LogLevelERR = 1, // output only ERR
    SLC_LogLevelINF = 2, // output ERR and INF
    SLC_LogLevelDBG = 4, // output ERR, INF, and DBG
    SLC_LogLevelPERF = 8, // output performance test message
    SLC_LogLevelTEST = 16, // output test message
    SLC_LogLevelALL = 31, // enable all log levels.
} SLC_LogLevel_t;

// Log-sink file.
// NULL disables logging. Default value is stdout.
#if !defined(SLC_LOG_C_)
extern
#endif
    FILE* SLC_LogSink
#if defined(SLC_LOG_C_)
    = NULL
#endif
;

// Log level
#if !defined(SLC_LOG_C_)
extern
#endif
    SLC_LogLevel_t SLC_LogLevel
#if defined(SLC_LOG_C_)
    = SLC_LogLevelALL
#endif
;

// write timestamp and log-level
void SLC_LogWriteHeader(SLC_LogLevel_t loglevel);

void SLC_LogWriteErrHeader(SLC_errno_t err);

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
#pragma endregion
#pragma region test_utility_macros
// standard test method signatures
typedef struct {
    SLC_i32_t settings;
    const void* data;
} SLC_TestArgs_t, *SLC_PTestArgs_t;
typedef const SLC_TestArgs_t *SLC_PCTestArgs_t;
typedef SLC_errno_t (*SLC_TESTMETHOD)(SLC_i32_t settings);
typedef SLC_errno_t (*SLC_TESTMETHOD2)(SLC_PCTestArgs_t args);

// test method calling macro
#define SLC_TEST_ABORT_ON_FAIL  1
#define SLC_test(__errno, __method_to_test, __setting, __func, __line) \
    __errno = __method_to_test(__setting); \
    if (__errno) { \
        SLC_LogERR(__errno, "setting=%d(0x%x), func=%s, line=%d", __setting, __setting, __func, __line); \
        if (SLC_TEST_ABORT_ON_FAIL) break; }
#define SLC_test2(__errno, __method_to_test, __pvsetting, __func, __line) \
    __errno = __method_to_test(__pvsetting); \
    if (__errno) { \
        SLC_LogERR(__errno, "func=%s, line=%d", __func, __line); \
        if (SLC_TEST_ABORT_ON_FAIL) break; }
#define SLC_testend(__errno, __func, __line) \
    SLC_LogTEST("errno=0x%x(%d) @ %s,%d\n", __errno, __errno, __func, __line)
#pragma endregion
#pragma regioon stopwatch_functions
// initialize stopwatch.
void SLC_Stopwatch_Init(SLC_size_t channels, SLC_size_t caption_length);

// Release the resources initialized by SLC_Stopwatch_Init.
void SLC_Stopwatch_Destroy();

// Start time measurement using a selected channel.
SLC_i32_t SLC_Stopwatch_Start(const char* caption);

// Measure and record time.
void SLC_Stopwatch_Measure(SLC_i32_t channel);

// Release the channel.
void SLC_Stopwatch_Release(SLC_i32_t channel);

// Difference between two timespec instances
void SLC_Timespec_A_minus_B(struct timespec* a_minus_b, struct timespec* a, struct timespec* b);
#pragma endregion
#pragma region comparison_of_SLC_r32_t_numbers
#define SLC_r32_sumabs(__a, __b) (SLC_r32_abs(__a) + SLC_r32_abs(__b))
#define SLC_r32_absdiff(__a, __b) SLC_r32_abs((__a) - (__b))
#define SLC_r32_relabsdiff(__a, __b) SLC_r32_absdiff(__a, __b)/SLC_r32_sumabs(__a, __b)
#define SLC_r32_areequal(__a, __b, __tol) \
    (((SLC_r32_abs(__a) < __tol) || (SLC_r32_abs(__b) < __tol)) ? \
    (SLC_r32_absdiff(__a, __b) < __tol) : (SLC_r32_relabsdiff(__a, __b) < __tol))
#pragma endregion
#pragma region comparison_of_SLC_r64_t_numbers
#define SLC_r64_sumabs(__a, __b) (SLC_r64_abs(__a) + SLC_r64_abs(__b))
#define SLC_r64_absdiff(__a, __b) SLC_r64_abs((__a) - (__b))
#define SLC_r64_relabsdiff(__a, __b) SLC_r64_absdiff(__a, __b)/SLC_r64_sumabs(__a, __b)
#define SLC_r64_areequal(__a, __b, __tol) \
    (((SLC_r64_abs(__a) < __tol) || (SLC_r64_abs(__b) < __tol)) ? \
    (SLC_r64_absdiff(__a, __b) < __tol) : (SLC_r64_relabsdiff(__a, __b) < __tol))
#pragma endregion
#pragma region comparison_of_SLC_c64_t_numbers
#define SLC_c64_sumabs(__a, __b) (SLC_c64_abs(__a) + SLC_c64_abs(__b))
#define SLC_c64_absdiff(__a, __b) SLC_c64_abs((__a) - (__b))
#define SLC_c64_relabsdiff(__a, __b) SLC_c64_absdiff(__a, __b)/SLC_c64_sumabs(__a, __b)
#define SLC_c64_areequal(__a, __b, __tol) \
    (((SLC_c64_abs(__a) < __tol) || (SLC_c64_abs(__b) < __tol)) ? \
    (SLC_c64_absdiff(__a, __b) < __tol) : (SLC_c64_relabsdiff(__a, __b) < __tol))
#pragma endregion
#pragma region comparison_of_SLC_c128_t_numbers
#define SLC_c128_sumabs(__a, __b) (SLC_c128_abs(__a) + SLC_c128_abs(__b))
#define SLC_c128_absdiff(__a, __b) SLC_c128_abs((__a) - (__b))
#define SLC_c128_relabsdiff(__a, __b) SLC_c128_absdiff(__a, __b)/SLC_c128_sumabs(__a, __b)
#define SLC_c128_areequal(__a, __b, __tol) \
    (((SLC_c128_abs(__a) < __tol) || (SLC_c128_abs(__b) < __tol)) ? \
    (SLC_c128_absdiff(__a, __b) < __tol) : (SLC_c128_relabsdiff(__a, __b) < __tol))
#pragma endregion
#endif
