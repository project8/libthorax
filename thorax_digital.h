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
#define px1500_data_type_size 1
#define px1500_min_val -0.25
#define px1500_max_val 0.25
#define px1500_range (px1500_max_val - px1500_min_val)

/*
 * the signatec PX14400 is an 14 bit digitizer
 */
#define px14400_bits 14
#define px14400_data_type_size 2
#define px14400_min_val -0.25
#define px14400_max_val 0.25
#define px14400_range (px1500_max_val - px1500_min_val)

struct dig_calib_params
{
    unsigned bit_depth;
    unsigned levels;
    double v_range;
    double v_min;
    double inv_levels;
    double inv_v_range;
    unsigned data_type_size;
};


struct dig_calib_params get_calib_params( unsigned n_bits, unsigned data_type_size, double v_min, double v_range );

struct dig_calib_params get_px1500_calib_params();
struct dig_calib_params get_px14400_calib_params();

/*
 * convert a digital <=64 bit value to a double or float.
 */
float fd2a(uint64_t dig, struct dig_calib_params* params);
double dd2a(uint64_t dig, struct dig_calib_params* params);

/*
 * convert an analog value to a digital value.
 */
uint64_t a2d(double analog, struct dig_calib_params* params);

#endif // THORAX_DIGITAL_H_
