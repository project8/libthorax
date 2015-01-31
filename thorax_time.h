#ifndef THORAX_TIME_H_
#define THORAX_TIME_H_

#include "thorax_types.h"

#ifndef _WIN32
#include <sys/time.h>
#endif
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#endif

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

extern double thorax_timebase;
extern time_nsec_type thorax_timestart;
#endif // __MACH__


extern char date_time_format[];

#ifdef _WIN32
struct timespec
{
	time_t tv_sec;
	long tv_nsec;
};
LARGE_INTEGER getFILETIMEoffset();
int clock_gettime(int X, struct timespec* tv);
#endif

int get_time_monotonic(struct timespec* time);

int get_time_current(struct timespec* time);

time_nsec_type time_to_nsec(struct timespec time);

double time_to_sec(struct timespec time);

void time_diff(struct timespec start, struct timespec end, struct timespec* diff);

size_t get_time_absolute_str(char* ptr);

#endif // THORAX_TIME_H_
