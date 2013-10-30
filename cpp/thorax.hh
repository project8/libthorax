/*
 * thorax.hh
 *
 *  Created on: Oct 28, 2013
 *      Author: nsoblath
 */

#ifndef THORAX_HH_
#define THORAX_HH_

extern "C"
{
    #include "thorax_digital.h"
    #include "thorax_time.h"
    #include "thorax_types.h"
}

#include <string>

inline std::string get_absolute_time_string()
{
    char t_string_time[ 512 ];
    get_time_absolute_str( t_string_time );
    return std::string( t_string_time );
}


#endif /* THORAX_HH_ */
