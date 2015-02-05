/*
 * thorax_test.c
 *
 *  Created on: Oct 29, 2013
 *      Author: nsoblath
 */


#include <stdio.h>
#include <unistd.h>

#include "thorax_digital.h"
#include "thorax_time.h"



int main()
{
    // wait a little to advance the time stamp
#ifndef _WIN32
    usleep( 5000 );
#else
    Sleep( 5 );
#endif

    struct timespec time;
    get_time_monotonic(&time);
    printf("%" PRIu64 "  %f\n", time_to_nsec(time), time_to_sec(time));
    printf("date_time_format: %s\n", date_time_format);

    char date_time[512];
    get_time_absolute_str(date_time);
    printf("date/time string (UTC): %s\n", date_time);

    return 0;
}
