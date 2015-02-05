/*
 * digital.c
 *
 * written by jared kofron <jared.kofron@gmail.com>
 *
 * documented prototypes are in digital.h
 */

#define THORAX_API_EXPORTS

#include "thorax_digital.h"

#include <stdio.h>

THORAX_API void get_calib_params( unsigned n_bits, unsigned data_type_size, double v_min, double v_range, struct dig_calib_params *params )
{
    params->bit_depth = n_bits;
    params->levels = 1 << n_bits;
    params->data_type_size = data_type_size;
    params->v_range = v_range;
    params->v_min = v_min;
    params->inv_levels = 1. / (double)params->levels;
    params->inv_v_range = 1. / params->v_range;
    params->dac_gain = params->v_range * params->inv_levels;
    return;
}

THORAX_API void get_calib_params2( unsigned n_bits, unsigned data_type_size, double v_min, double v_range, double dac_gain, struct dig_calib_params *params )
{
    params->bit_depth = n_bits;
    params->levels = 1 << n_bits;
    params->data_type_size = data_type_size;
    params->v_range = v_range;
    params->v_min = v_min;
    params->inv_levels = 1. / ( double )params->levels;
    params->inv_v_range = 1. / params->v_range;
    params->dac_gain = dac_gain;
    return;
}

THORAX_API void get_px1500_calib_params( struct dig_calib_params *params )
{
    return get_calib_params( px1500_bits, px1500_data_type_size, px1500_min_val, px1500_range, params );
}

THORAX_API void get_px14400_calib_params( struct dig_calib_params *params )
{
    return get_calib_params( px14400_bits, px14400_data_type_size, px14400_min_val, px14400_range, params );
}

THORAX_API void get_u1084a_calib_params( struct dig_calib_params *params )
{
    return get_calib_params( u1084a_bits, u1084a_data_type_size, u1084a_min_val, u1084a_range, params );
}


// digital to analog
THORAX_API float fd2a( uint64_t dig, const struct dig_calib_params* params )
{
    return ( *params ).v_min + ( float )( *params ).dac_gain * ( float )dig;
    //return (*params).v_min + (*params).v_range * (float)dig * (float)((*params).inv_levels);
    ////float scale_pct = (unsigned)(dig)/((1 << (px1500_bits - 1)) - 1);
    ////return (float)(px1500_min_val + px1500_range*scale_pct);
}

THORAX_API double dd2a( uint64_t dig, const struct dig_calib_params* params )
{
    return ( *params ).v_min + ( *params ).dac_gain * ( double )dig;
    //return (*params).v_min + (*params).v_range * (double)dig * (double)((*params).inv_levels);
    ////double scale_pct = (unsigned)(dig)/((1 << (px1500_bits - 1)) - 1);
    ////return (double)(px1500_min_val + px1500_range*scale_pct);
}


// analog to digital
THORAX_API uint64_t a2d( double analog, const struct dig_calib_params* params )
{
    analog = ( analog - (*params).v_min ) * (*params).inv_v_range * (double)((*params).levels);
    if( analog > (double)((*params).levels - 1) ) analog = (*params).levels - 1;
    else if( analog < 0. ) analog = 0.;
    return (uint64_t)analog;
}
