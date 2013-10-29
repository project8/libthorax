#ifndef TIME_HH_
#define TIME_HH_

//#include "types.hh"

//#include <cstddef>

#include "thorax_types.h"

#include <sys/time.h>
#include <time.h>
//#include <string>

#ifndef NSEC_PER_SEC
#define NSEC_PER_SEC 1000000000
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


typedef uint64_t time_nsec_type;

extern char date_time_format[];


inline int get_time_monotonic(struct timespec* time)
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

inline time_nsec_type time_to_nsec(struct timespec time)
{
    return (long long int)time.tv_sec * (long long int)NSEC_PER_SEC + (long long int)time.tv_nsec;
}

inline double time_to_sec(struct timespec time)
{
    return (double)time.tv_sec + (double)time.tv_nsec / (double)NSEC_PER_SEC;
}


inline size_t get_time_absolute_str(char* ptr)
{
    time_t raw_time;
    struct tm* processed_time;

    time(&raw_time);
    processed_time = gmtime(&raw_time);
    return strftime(ptr, 512, date_time_format, processed_time);
}

/*
inline std::string get_time_absolute_str()
{
    time_t t_raw_time;
    struct tm* t_processed_time;
    char t_string_time[ 512 ];

    time( &t_raw_time );
    t_processed_time = localtime( &t_raw_time );
    strftime( t_string_time, 512, "%Y-%m-%d %H:%M:%S %z", t_processed_time ); // sDateTimeFormat is defined in MonarchTypes.hpp
    return std::string( t_string_time );
}
*/

/*
    inline timestamp_t get_integer_time()
    {
        timeval t_timeval;
        gettimeofday( &t_timeval, NULL );
        return( 1000000 * t_timeval.tv_sec + t_timeval.tv_usec );
    }

    inline std::string get_string_time()
    {
        time_t t_raw_time;
        struct tm* t_processed_time;
        char t_string_time[ 512 ];

        time( &t_raw_time );
        t_processed_time = localtime( &t_raw_time );
        strftime( t_string_time, 512, "%Y-%m-%d %H:%M:%S %z", t_processed_time ); // sDateTimeFormat is defined in MonarchTypes.hpp
        return std::string( t_string_time );
    }
*/

#endif
