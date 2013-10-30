/*
 * digital.c
 *
 * written by jared kofron <jared.kofron@gmail.com>
 *
 * documented prototypes are in digital.h
 */
#include "thorax_digital.h"

// digital to analog
float fd2a(data_type dig) {
  float scale_pct = (unsigned)(dig)/((1 << (px1500_bits - 1)) - 1);
  return (float)(px1500_min_val + px1500_range*scale_pct);
}

double dd2a(data_type dig) {
  double scale_pct = (unsigned)(dig)/((1 << (px1500_bits - 1)) - 1);
  return (double)(px1500_min_val + px1500_range*scale_pct);
}
