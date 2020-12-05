#ifndef PARALLELLIGHTH
#define PARALLELLIGHTH

#include "hitable.h"
#include "light_source.h"
#include "ray.h"

class parallel_light : public light_source {
public:
  parallel_light(vec3 dir, color col, double intensity) : dir(dir) {
    this->intensity = intensity;
    this->col = col;
  };
  virtual ray get_ray(const point3 &hit_point, const hit_record &rec) const {
    if (dot(dir, rec.normal) > 0)
      return ray(hit_point, dir);
    return ray(hit_point, -dir);
  };
  virtual double get_dist(const point3 &p) const { return 1e10; }
  vec3 dir;
};

#endif
