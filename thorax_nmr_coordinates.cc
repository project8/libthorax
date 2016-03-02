/*
 * thorax_nmr_coordinates.c
 *
 * written by jared kofron <jared.kofron@gmail.com>
 */

#define THORAX_API_EXPORTS

#include "thorax_nmr_coordinates.hh"

namespace thorax
{
    THORAX_API void magnet2cartesian( magnet_coord* m, cartesian_coord* c )
    {
      // first the easy part.  z is just z.
      c->z = m->z;

      // now we use the conversions derived from the machine drawing
      // from p. hirtle
      c->x = r_eccentric*sin(m->theta_eccentric+m->theta_concentric)
        - r_concentric*sin(m->theta_concentric);
      c->y = r_eccentric*cos(m->theta_eccentric+m->theta_concentric)
        - r_concentric*cos(m->theta_concentric);
    }

    THORAX_API float cartesian_distance( cartesian_coord* x1, cartesian_coord* x2 )
    {
      return sqrt(pow((x1->x - x2->x),2.0) + pow(x1->y - x2->y,2.0) + pow(x1->z - x2->z,2.0));
    }

}
