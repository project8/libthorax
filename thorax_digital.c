/*
 * digital.c
 *
 * written by jared kofron <jared.kofron@gmail.com>
 *
 * documented prototypes are in digital.h
 */
#include "thorax_digital.h"

struct dig_calib_params get_px1500_calib_params()
{
    struct dig_calib_params params;
    params.levels = 1 << px1500_bits;
    params.v_range = px1500_range;
    params.v_min = px1500_min_val;
    return params;
}


// digital to analog
float fd2a(byte_type dig, struct dig_calib_params* params)
{
    return (*params).v_min + (*params).v_range * (float)dig / (float)((*params).levels);
    //float scale_pct = (unsigned)(dig)/((1 << (px1500_bits - 1)) - 1);
    //return (float)(px1500_min_val + px1500_range*scale_pct);
}

double dd2a(byte_type dig, struct dig_calib_params* params)
{
    return (*params).v_min + (*params).v_range * (float)dig / (float)((*params).levels);
    //double scale_pct = (unsigned)(dig)/((1 << (px1500_bits - 1)) - 1);
    //return (double)(px1500_min_val + px1500_range*scale_pct);
}
