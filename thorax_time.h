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

extern double mantis_timebase;
extern time_nsec_type mantis_timestart;
#endif // __MACH__


extern char date_time_format[];


int get_time_monotonic(struct timespec* time);

time_nsec_type time_to_nsec(struct timespec time);

double time_to_sec(struct timespec time);

size_t get_time_absolute_str(char* ptr);

#endif // THORAX_TIME_H_
