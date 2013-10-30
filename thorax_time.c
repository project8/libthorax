/*
 * thorax_time.c
 *
 *  Created on: Oct 29, 2013
 *      Author: nsoblath
 */

#include "thorax_time.h"

char date_time_format[] = "%FT%TZ";

int get_time_monotonic(struct timespec* time)
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
