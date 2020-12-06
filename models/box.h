#ifndef BOXH
#define BOXH

#include "hitable.h"
#include "rectangle.h"
#include "vec3.h"

class box : public hitable {
public:
  box(){};
  box(point3 corner, vec3 basis1, double a, double b, double c,
      material *mtr_ptr)
      : corner(corner), a(a), b(b), c(c), mtr_ptr(mtr_ptr) {
    vec3 u, v, w, upv;
    u = unit_vector(basis1);
    upv = vec3(0, 1, 0);
    v = unit_vector(cross(u, upv));
    w = unit_vector(cross(u, v));
    basis[0] = u;
    basis[1] = v;
    basis[2] = w;
    rectangle *bottom =
        new rectangle(corner, corner + u * a, corner + v * b, mtr_ptr);
    rectangle *top = new rectangle(corner + w * c, corner + u * a + w * c,
                                   corner + v * b + w * c, mtr_ptr);
    rectangle *right = new rectangle(corner + a * u + w * c, corner + u * a,
                                     corner + v * b + u * a + w * c, mtr_ptr);
    rectangle *left =
        new rectangle(corner, corner + w * c, corner + v * b, mtr_ptr);
    rectangle *back =
        new rectangle(corner + v * b + u * a, corner + w * c + u * a + v * b,
                      corner + v * b, mtr_ptr);
    rectangle *front =
        new rectangle(corner, corner + u * a, corner + w * c, mtr_ptr);
    sides[0] = top;
    sides[1] = bottom;
    sides[2] = right;
    sides[3] = left;
    sides[4] = back;
    sides[5] = front;
  };
  virtual bool hit(const ray &r, double tmin, double tmax,
                   hit_record &rec) const;
  point3 corner;
  double a, b, c;
  vec3 basis[3];
  material *mtr_ptr;
  rectangle *sides[6];
};

bool box::hit(const ray &r, double tmin, double tmax, hit_record &rec) const {
  // TODO Jfind closes t
  double closest_t = 1e9 + 1;
  hit_record temp;
  for (int i = 0; i < 6; i++) {
    if (sides[i]->hit(r, tmin, tmax, temp)) {
      if (temp.t < closest_t) {
        rec = temp;
        closest_t = temp.t;
      }
    }
  }
  return closest_t != 1e9 + 1;
}

#endif
