/*
 * digital.h
 *
 * written by jared kofron <jared.kofron@gmail.com>
 *
 * functions for converting from D2A and A2D.  prototypes are declared in
 * digital.h.  versions are included for both floats and doubles.  there are
 * two styles of the functions inspired by the GSL way of doing things - a 
 * normal version which returns the simple type of interest, and an 'error' 
 * version which can return information about bad arguments.
 */

#ifndef THORAX_DIGITAL_H_
#define THORAX_DIGITAL_H_

#include "thorax_types.h"

/*
 * the signatec PX1500 is an 8 bit digitizer
 */
#define px1500_bits 8
#define px1500_min_val -0.25
#define px1500_max_val 0.25
#define px1500_range (px1500_max_val - px1500_min_val)

struct dig_calib_params
{
    unsigned levels;
    double v_range;
    double v_min;
};

struct dig_calib_params get_px1500_calib_params();

/*
 * convert a digital 8 bit value (an unsigned char) to a double or float.
 */
float fd2a(data_type dig, struct dig_calib_params* params);
double dd2a(data_type dig, struct dig_calib_params* params);

#endif // THORAX_DIGITAL_H_
