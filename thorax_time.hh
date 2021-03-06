#ifndef THORAX_TIME_H_
#define THORAX_TIME_H_

#include "thorax_types.hh"

#ifndef _WIN32
#include <sys/time.h>
#else
#include <Windows.h>
#endif
#include <time.h>
#include <string>

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
#endif // __MACH__

namespace thorax
{

#ifdef __MACH__
    extern double thorax_timebase;
    extern time_nsec_type thorax_timestart;
#endif // __MACH__


    extern THORAX_API char date_time_format[];

#ifdef _WIN32
struct timespec
    {
        time_t tv_sec;
        long tv_nsec;
    #ifdef __cplusplus
        inline bool operator==( const timespec& rhs ) const { return tv_nsec==rhs.tv_nsec && tv_sec==rhs.tv_sec; }
        inline bool operator<( const timespec& rhs ) const { return tv_sec != rhs.tv_sec ? tv_sec < rhs.tv_sec : tv_nsec < rhs.tv_nsec; }
    #endif
    };

    THORAX_API LARGE_INTEGER getFILETIMEoffset();
    THORAX_API int clock_gettime( int X, struct timespec* tv );
#else
    inline bool operator==( const timespec& lhs, const timespec& rhs ) { return lhs.tv_nsec==rhs.tv_nsec && lhs.tv_sec==rhs.tv_sec; }
    inline bool operator<( const timespec& lhs, const timespec& rhs ) { return lhs.tv_sec != rhs.tv_sec ? lhs.tv_sec < rhs.tv_sec : lhs.tv_nsec < rhs.tv_nsec; }
#endif

    THORAX_API int get_time_monotonic( struct timespec* time );

    THORAX_API int get_time_current( struct timespec* time );

    THORAX_API time_nsec_type time_to_nsec( struct timespec time );

    THORAX_API double time_to_sec( struct timespec time );

    THORAX_API void time_diff( struct timespec start, struct timespec end, struct timespec* diff );

    THORAX_API size_t get_time_absolute_str( char* ptr );

    THORAX_API std::string get_absolute_time_string();

}
#endif // THORAX_TIME_H_
