/*
 * thorax_time.c
 *
 *  Created on: Oct 29, 2013
 *      Author: nsoblath
 */

#include "thorax_time.h"

char date_time_format[] = "%FT%TZ";

#ifdef __MACH__
double thorax_timebase = 0.0;
time_nsec_type thorax_timestart = 0;
#endif

int get_time_monotonic(struct timespec* time)
{
#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
    if (! thorax_timestart)
    {
        mach_timebase_info_data_t tb = { .numer = 0, .denom = 1 };
        mach_timebase_info(&tb);
        thorax_timebase = tb.numer;
        thorax_timebase /= tb.denom;
        thorax_timestart = mach_absolute_time();
    }
    double diff = (mach_absolute_time() - thorax_timestart) * thorax_timebase;
    time->tv_sec = diff * MACNANO;
    time->tv_nsec = diff - (time->tv_sec * MACGIGA);
    return 0;
#else
    return clock_gettime( CLOCK_MONOTONIC, time );
#endif
}

int get_time_current(struct timespec* time)
{
#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
    if (! thorax_timestart)
    {
        mach_timebase_info_data_t tb = { .numer = 0, .denom = 1 };
        mach_timebase_info(&tb);
        thorax_timebase = tb.numer;
        thorax_timebase /= tb.denom;
        thorax_timestart = mach_absolute_time();
    }
    double diff = (mach_absolute_time() - thorax_timestart) * thorax_timebase;
    time->tv_sec = diff * MACNANO;
    time->tv_nsec = diff - (time->tv_sec * MACGIGA);
    return 0;
#else
    return clock_gettime(CLOCK_PROCESS_CPUTIME_ID, time);
#endif

}

time_nsec_type time_to_nsec(struct timespec time)
{
    return (long long int)time.tv_sec * (long long int)NSEC_PER_SEC + (long long int)time.tv_nsec;
}

double time_to_sec(struct timespec time)
{
    return (double)time.tv_sec + (double)time.tv_nsec / (double)NSEC_PER_SEC;
}

void time_diff(struct timespec start, struct timespec end, struct timespec* diff)
{
    if ((end.tv_nsec - start.tv_nsec < 0))
    {
        diff->tv_sec = end.tv_sec - start.tv_sec - 1;
        diff->tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    }
    else
    {
        diff->tv_sec = end.tv_sec - start.tv_sec;
        diff->tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return;
}

size_t get_time_absolute_str(char* ptr)
{
    time_t raw_time;
    struct tm* processed_time;

    time(&raw_time);
    processed_time = gmtime(&raw_time);
    return strftime(ptr, 512, date_time_format, processed_time);
}
