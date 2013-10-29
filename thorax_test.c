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

    return 0;
}
