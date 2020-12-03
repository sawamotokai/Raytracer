#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

struct hit_record {
  double t;
  point3 p;
  vec3 normal;
};

class hitable {
public:
  virtual bool hit(const ray &r, double tmin, double tmax,
                   hit_record &rec) const = 0;
};

#endif
