#ifndef LIGHTSOURCEH
#define LIGHTSOURCEH

#include "hitable.h"
#include "material.h"
#include "ray.h"

class light_source : public material {
public:
  virtual ray get_ray(const point3 &hit_point, const hit_record &rec) const = 0;
  virtual double get_dist(const point3 &p) const = 0;
  virtual color emittedd() { return col; };
  virtual bool scatter(const ray &r_in, const hit_record &rec,
                       vec3 &attenuation, ray &scattered) const {
    return false;
  }
  color col;
  double intensity;
};

#endif
