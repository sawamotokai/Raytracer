#ifndef LIGHTSOURCEH
#define LIGHTSOURCEH

#include "hitable.h"
#include "ray.h"

class light_source {
public:
  virtual ray get_ray(const point3 &hit_point) const = 0;
  virtual double get_dist(const point3 &p) const = 0;
  color col;
  double intensity;
};

#endif
