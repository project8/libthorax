#ifndef THORAX_TIME_H_
#define THORAX_TIME_H_

#include "thorax_types.h"

#include <sys/time.h>
#include <time.h>

#ifndef NSEC_PER_SEC
#define NSEC_PER_SEC 1000000000
#endif

#ifndef SEC_PER_NSEC
#define SEC_PER_NSEC 1.e-9
#endif

#ifdef __MACH__
#include <mach/mach_time.h>

#ifndef MACNANO
#define MACNANO (+1.0E-9)
#define MACGIGA UINT64_C(1000000000)
#endif // MACNANO

static double mantis_timebase = 0.0;
static uint64_t mantis_timestart = 0;
#endif // __MACH__


extern char date_time_format[];


extern inline int get_time_monotonic(struct timespec* time)
{
#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
    if (!mantis_timestart) {
        mach_timebase_info_data_t tb = { 0 };
        mach_timebase_info(&tb);
        mantis_timebase = tb.numer;
        mantis_timebase /= tb.denom;
        mantis_timestart = mach_absolute_time();
    }
    double diff = (mach_absolute_time() - mantis_timestart) * mantis_timebase;
    time->tv_sec = diff * MACNANO;
    time->tv_nsec = diff - (time->tv_sec * MACGIGA);
    return 0;
#else
    return clock_gettime( CLOCK_MONOTONIC, time );
#endif
}

extern inline time_nsec_type time_to_nsec(struct timespec time)
{
    return (long long int)time.tv_sec * (long long int)NSEC_PER_SEC + (long long int)time.tv_nsec;
}

extern inline double time_to_sec(struct timespec time)
{
    return (double)time.tv_sec + (double)time.tv_nsec / (double)NSEC_PER_SEC;
}


extern inline size_t get_time_absolute_str(char* ptr)
{
    time_t raw_time;
    struct tm* processed_time;

    time(&raw_time);
    processed_time = gmtime(&raw_time);
    return strftime(ptr, 512, date_time_format, processed_time);
}

#endif // THORAX_TIME_H_
