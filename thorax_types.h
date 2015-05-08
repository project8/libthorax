#ifndef THORAX_TYPES_H_
#define THORAX_TYPES_H_

// Standard fixed-width integers (plus support for use in printf, etc)
#include <inttypes.h>


// API export macros for windows
#ifdef _WIN32
#  ifdef THORAX_API_EXPORTS
#    define THORAX_API __declspec(dllexport)
#  else
#    define THORAX_API __declspec(dllimport)
#  endif
#else
#  define THORAX_API
#endif


//convenience typedefs for readability
typedef uint64_t acquisition_id_type;
typedef uint64_t record_id_type;
typedef uint64_t time_nsec_type;
typedef uint8_t byte_type;



//#include <stdlib.h>
//#include <time.h>
//#include <string>

/*
template<typename T, typename U>
struct is_same
{
    static const bool value = false;
};

template<typename T>
struct is_same<T,T>  //specialization
{
   static const bool value = true;
};

template<bool> struct staticassert;
template<> struct staticassert<true> {};  //specialization
*/


/*
typedef size_t PreludeType;

typedef uint32_t AccessModeType;
static const AccessModeType sAccessRead = 0;
static const AccessModeType sAccessWrite = 1;

typedef uint32_t InterfaceModeType;
static const AccessModeType sInterfaceInterleaved = 0;
static const AccessModeType sInterfaceSeparate = 1;

typedef uint32_t AcquisitionModeType;
static const AcquisitionModeType sOneChannel = 1;
static const AcquisitionModeType sTwoChannel = 2;

typedef uint32_t RunType;
static const RunType sRunTypeSignal = 0;
static const RunType sRunTypeBackground = 1;
static const RunType sRunTypeOther = 999;

typedef uint32_t RunSourceType;
static const RunSourceType sSourceMantis = 0;
static const RunSourceType sSourceSimulation = 1;

typedef uint32_t FormatModeType;
static const FormatModeType sFormatSingle = 0;
static const FormatModeType sFormatMultiSeparate = 1;
static const FormatModeType sFormatMultiInterleaved = 2;

typedef uint64_t AcquisitionIdType; // 8 bytes
typedef uint64_t RecordIdType; // 8 bytes
typedef uint64_t TimeType; // 8 bytes
typedef uint8_t DataType; // 1 byte
*/

//static const std::string sDateTimeFormat("%Y-%m-%d %H:%M:%S %z");

#endif // THORAX_TYPES_H_
