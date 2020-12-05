#ifndef PARALLELLIGHTH
#define PARALLELLIGHTH

#include "hitable.h"
#include "light_source.h"
#include "ray.h"

class parallel_light : public light_source {
public:
  parallel_light(vec3 dir, color col, double intensity) : dir(dir), col(col) {
    this->intensity = intensity;
  };
  virtual ray get_ray(const point3 &hit_point) const {
    return ray(hit_point, dir);
  };
  virtual double get_dist(const point3 &p) const { return 1e10; }
  color col;
  vec3 dir;
};

#endif
