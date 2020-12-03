#ifndef METALH
#define METALH

#include "material.h"
#include "vec3.h"
#include <math.h>

class metal : public material {
public:
  metal(const vec3 &a, double f) : albedo(a) {
    name = "metal";
    fuzz = fmin(1.0, f);
  };
  virtual bool scatter(const ray &r_in, const hit_record &rec,
                       vec3 &attenuation, ray &scattered) const {
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
    attenuation = albedo;
    return dot(scattered.direction(), rec.normal) > 0;
  };
  vec3 albedo;
  double fuzz;
};

#endif
