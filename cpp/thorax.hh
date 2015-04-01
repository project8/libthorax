/*
 * thorax.hh
 *
 *  Created on: Oct 28, 2013
 *      Author: nsoblath
 */

#ifndef THORAX_HH_
#define THORAX_HH_

#include <ostream>

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

inline std::ostream& operator<<( std::ostream& out, const dig_calib_params& params )
{
    out << "Bit depth: " << params.bit_depth << " bits\n";
    out << "Levels: " << params.levels << '\n';
    out << "Data type size: " << params.data_type_size << " bytes\n";
    out << "Voltage offset: " << params.v_offset << " V\n";
    out << "Voltage range: " << params.v_range << " V\n";
    out << "1 / levels: " << params.inv_levels << '\n';
    out << "1 / v_range: " << params.inv_v_range << " 1/V";
    return out;
}


#endif /* THORAX_HH_ */
