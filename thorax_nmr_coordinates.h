/*
 * thorax_nmr_coordinates.h
 *
 * written by jared kofron <jared.kofron@gmail.com>
 *
 * functions for converting between nmr probe holder coordinates 
 * (eccentric angle, concentric angle, and z) and "normal" coordinate
 * systems such as cartesian and cylindrical.
 */

#ifndef THORAX_NMR_COORDS_H
#define THORAX_NMR_COORDS_H

#include "math.h"

/*
 * as-built dimensions from p. hirtle in meters
 * TODO: double check these!
 */
static const float r_eccentric = 0.0161798;
static const float r_concentric = 0.0161798;

/* 
 * first off we have the "magnet coordinates", which are defined in
 * terms of the nmr probe holder.  they consist of an eccentric angle,
 * a concentric angle, and a height z. 
 */
typedef struct {
  float theta_concentric;
  float theta_eccentric;
  float z;
} magnet_coord;

/*
 * next we have cartesian coordinates.  simple x, y, z.
 */
typedef struct {
  float x;
  float y;
  float z;
} cartesian_coord;

/*
 * next we have cylindrical coordinates.  radius rho, angle theta, height z.
 */
typedef struct {
  float rho;
  float theta;
  float z;
} cylindrical_coord;

/*
 * conversion functions from magnet coordinates to normal coordinates
 */
void magnet2cartesian(magnet_coord*, cartesian_coord*);

/*
 * compute distances
 */
float cartesian_distance(cartesian_coord*, cartesian_coord*);


#endif //THORAX_NMR_COORDS_H
