#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

class material;

struct hit_record {
  double t;
  point3 p;
  vec3 normal;
  material *mat_ptr;
};

class hitable {
public:
  virtual bool hit(const ray &r, double tmin, double tmax,
                   hit_record &rec) const = 0;
};

#endif
