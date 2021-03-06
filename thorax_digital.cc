/*
 * digital.c
 *
 * written by jared kofron <jared.kofron@gmail.com>
 *
 * documented prototypes are in digital.h
 */

#define THORAX_API_EXPORTS

#include "thorax_digital.hh"

#include <cstdio>

namespace thorax
{

    THORAX_API void get_calib_params( unsigned n_bits, unsigned data_type_size, double v_offset, double v_range, bool bits_r_aligned, struct dig_calib_params *params )
    {
        params->bit_depth = n_bits;
        params->levels = 1 << n_bits;
        params->data_type_size = data_type_size;
        params->v_range = v_range;
        params->v_offset = v_offset;
        params->inv_levels = 1. / (double)params->levels;
        params->inv_v_range = 1. / params->v_range;
        params->dac_gain = params->v_range * params->inv_levels;
        params->bits_right_aligned = bits_r_aligned;
        return;
    }

    THORAX_API void get_calib_params2( unsigned n_bits, unsigned data_type_size, double v_offset, double v_range, double dac_gain, bool bits_r_aligned, struct dig_calib_params *params )
    {
        params->bit_depth = n_bits;
        params->levels = 1 << n_bits;
        params->data_type_size = data_type_size;
        params->v_range = v_range;
        params->v_offset = v_offset;
        params->inv_levels = 1. / ( double )params->levels;
        params->inv_v_range = 1. / params->v_range;
        params->dac_gain = dac_gain;
        params->bits_right_aligned = bits_r_aligned;
        return;
    }

    THORAX_API void get_px1500_calib_params( struct dig_calib_params *params )
    {
        return get_calib_params( px1500_bits, px1500_data_type_size, px1500_min_val, px1500_range, false, params );
    }

    THORAX_API void get_px14400_calib_params( struct dig_calib_params *params )
    {
        return get_calib_params( px14400_bits, px14400_data_type_size, px14400_min_val, px14400_range, false, params );
    }

    THORAX_API void get_u1084a_calib_params( struct dig_calib_params *params )
    {
        return get_calib_params( u1084a_bits, u1084a_data_type_size, u1084a_min_val, u1084a_range, false, params );
    }


    // digital to analog
    THORAX_API float d2a_uf( uint64_t dig, const struct dig_calib_params* params )
    {
        return ( *params ).v_offset + ( float )( *params ).dac_gain * ( float )dig;
    }
    THORAX_API double d2a_ud( uint64_t dig, const struct dig_calib_params* params )
    {
        return ( *params ).v_offset + ( *params ).dac_gain * ( double )dig;
    }
    THORAX_API float d2a_if( int64_t dig, const struct dig_calib_params* params )
    {
        return ( *params ).v_offset + ( float )( *params ).dac_gain * ( float )dig;
    }
    THORAX_API double d2a_id( int64_t dig, const struct dig_calib_params* params )
    {
        return ( *params ).v_offset + ( *params ).dac_gain * ( double )dig;
    }

    THORAX_API float fd2a( uint64_t dig, const struct dig_calib_params* params )
    {
        // fd2a and dd2a are deprecated; use d2a_uf and d2a_ud instead
        return d2a_uf( dig, params );
        //return (*params).v_min + (*params).v_range * (float)dig * (float)((*params).inv_levels);
        ////float scale_pct = (unsigned)(dig)/((1 << (px1500_bits - 1)) - 1);
        ////return (float)(px1500_min_val + px1500_range*scale_pct);
    }

    THORAX_API double dd2a( uint64_t dig, const struct dig_calib_params* params )
    {
        // fd2a and dd2a are deprecated; use d2a_uf and d2a_ud instead
        return d2a_ud( dig, params );
        //return (*params).v_min + (*params).v_range * (double)dig * (double)((*params).inv_levels);
        ////double scale_pct = (unsigned)(dig)/((1 << (px1500_bits - 1)) - 1);
        ////return (double)(px1500_min_val + px1500_range*scale_pct);
    }


    // analog to digital
    THORAX_API uint64_t a2d( double analog, const struct dig_calib_params* params )
    {
        analog = ( analog - (*params).v_offset ) * (*params).inv_v_range * (double)((*params).levels);
        if( analog > (double)((*params).levels - 1) ) analog = (*params).levels - 1;
        else if( analog < 0. ) analog = 0.;
        return (uint64_t)analog;
    }

    THORAX_API std::ostream& operator<<( std::ostream& out, const dig_calib_params& params )
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

}
