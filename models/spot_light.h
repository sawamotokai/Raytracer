#ifndef SPOTLIGHTH
#define SPOTLIGHTH

#include "hitable.h"
#include "light_source.h"
#include "ray.h"
#include "vec3.h"
#include <bits/stdc++.h>
using namespace std;

class spot_light : public light_source {
public:
  spot_light(const point3 &pos, const color &col, double intensity)
      : pos(pos), col(col) {
    this->intensity = intensity;
  };
  virtual ray get_ray(const point3 &hit_point) const {
    return ray(hit_point, pos - hit_point);
  };
  virtual double get_dist(const point3 &p) const { return dist(p, pos); }
  color col;
  point3 pos;
};

#endif
