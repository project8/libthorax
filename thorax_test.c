/*
 * thorax_test.c
 *
 *  Created on: Oct 29, 2013
 *      Author: nsoblath
 */


#include <stdio.h>

#include "digital.h"
#include "thorax_time.h"



int main()
{
    struct timespec time;
    get_time_monotonic(&time);
    printf("%" PRIu64 "  %f\n", time_to_nsec(time), time_to_sec(time));
    printf("date_time_format: %s\n", date_time_format);

    char date_time[512];
    get_time_absolute_str(date_time);
    printf("date/time string (UTC): %s\n", date_time);

    return 0;
}
