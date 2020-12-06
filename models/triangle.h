#ifndef TRIANGLEH
#define TRIANGLEH

#include "hitable.h"
#include "material.h"
#include "ray.h"
#include "vec3.h"

class triangle : public hitable {
public:
  triangle(const point3 &a, const point3 &b, const point3 &c, material *mtr)
      : v{a, b, c}, mtr_ptr(mtr){};

  virtual bool hit(const ray &r, double tmin, double tmax,
                   hit_record &rec) const {
    vec3 ab = v[1] - v[0];
    vec3 ac = v[2] - v[0];
    vec3 normal = unit_vector(cross(ab, ac));
    // TODO flip the normal so that all the normal looks outward
    vec3 w = v[0] - r.origin();
    assert(dot(r.direction(), normal) != 0);
    double k = dot(w, normal) / dot(r.direction(), normal);
    if (k <= 0) {
      return false;
    }
    point3 p = r.direction() * k + r.origin();
    vec3 pa = v[0] - p;
    vec3 pb = v[1] - p;
    vec3 pc = v[2] - p;
    double At = cross(ab, ac).length() / 2.0;
    double Aa = cross(pb, pc).length() / 2.0;
    double Ab = cross(pa, pc).length() / 2.0;
    double Ac = cross(pb, pa).length() / 2.0;
    double alpha = Aa / At;
    double beta = Ab / At;
    double gamma = Ac / At;
    double s = alpha + beta + gamma;
    // printf("%f\n", s);
    if (s < 1 + 1e-4 && s > 1 - 1e-4) {
      rec.mat_ptr = mtr_ptr;
      rec.t = k;
      rec.normal = normal;
      rec.p = p;
      return true;
    }
    return false;
  };
  point3 v[3];
  material *mtr_ptr;
};

#endif
