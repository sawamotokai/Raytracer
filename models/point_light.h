#ifndef POINTLIGHTH
#define POINTLIGHTH

#include "hitable.h"
#include "light_source.h"
#include "ray.h"
#include "vec3.h"
#include <bits/stdc++.h>
using namespace std;

class point_light : public light_source {
public:
  point_light(const point3 &pos, const color &col, double intensity)
      : pos(pos) {
    this->intensity = intensity;
    this->col = col;
  };
  virtual ray get_ray(const point3 &hit_point, const hit_record &rec) const {
    return ray(hit_point, pos - hit_point);
  };
  virtual double get_dist(const point3 &p) const { return dist(p, pos); }
  point3 pos;
};

#endif
