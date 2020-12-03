#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere : public hitable {
public:
  sphere(){};
  sphere(point3 center, double radius, material *mtr_ptr)
      : center(center), radius(radius), mtr_ptr(mtr_ptr){};
  point3 center;
  virtual bool hit(const ray &r, double tmin, double tmax,
                   hit_record &rec) const;
  double radius;
  material *mtr_ptr;
};

bool sphere::hit(const ray &r, double tmin, double tmax,
                 hit_record &rec) const {
  double a = dot(r.direction(), r.direction());
  double b = 2.0 * dot(r.direction(), r.origin() - center);
  double c = dot(r.origin() - center, r.origin() - center) - radius * radius;
  double d = b * b - 4 * a * c;
  if (d < 0)
    return false;
  assert(a != 0);
  double t = (-b - sqrt(d)) / 2.0 / a;
  if (t <= tmax && t >= tmin) {
    rec.t = t;
    rec.p = r.at(t);
    rec.normal = (rec.p - center) / radius;
    rec.mat_ptr = mtr_ptr;
    return true;
  }
  t = (-b + sqrt(d)) / 2.0 / a;
  if (t <= tmax && t >= tmin) {
    rec.t = t;
    rec.p = r.at(t);
    rec.normal = (rec.p - center) / radius;
    rec.mat_ptr = mtr_ptr;
    return true;
  }
  return false;
}

#endif
