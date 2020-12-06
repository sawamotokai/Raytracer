#ifndef RECTANGLEH
#define RECTANGLEH

#include "hitable.h"
#include "material.h"
#include "ray.h"
#include "triangle.h"
#include "vec3.h"

class rectangle : public hitable {
public:
  rectangle(triangle *t1, triangle *t2, material *mtr)
      : tri{t1, t2}, mtr_ptr(mtr){};
  rectangle(const point3 &a, const point3 &b, const point3 &c, material *mtr)
      : mtr_ptr(mtr) {
    vec3 ab = b - a;
    vec3 ac = c - a;
    vec3 d = ab + ac + a;
    vec3 ad = d - a;
    double cad = dot(ac, ad);
    double bad = dot(ab, ad);
    double bac = dot(ab, ac);
    if (cad <= bad && cad <= bac) {
      // cad & cbd;
      tri[0] = new triangle(c, a, d, mtr_ptr);
      tri[1] = new triangle(c, d, b, mtr_ptr);
    } else if (bad <= bac) {
      // bad & bcd
      tri[0] = new triangle(b, a, d, mtr_ptr);
      tri[1] = new triangle(b, c, d, mtr_ptr);
    } else {
      // bac & bdc
      tri[0] = new triangle(b, a, c, mtr_ptr);
      tri[1] = new triangle(b, d, c, mtr_ptr);
    }
  };
  virtual bool hit(const ray &r, double tmin, double tmax,
                   hit_record &rec) const {
    if (tri[0]->hit(r, tmin, tmax, rec)) {
      rec.normal *= -1;
      return true;
    }
    if (tri[1]->hit(r, tmin, tmax, rec)) {
      return true;
    }
    return false;
  };
  triangle *tri[2];
  material *mtr_ptr;
};

#endif
