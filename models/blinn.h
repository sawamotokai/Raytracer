#ifndef BLINNH
#define BLINNH

#include "light_source.h"
#include "material.h"
#include "vec3.h"
#include <math.h>
#include <vector>

class blinn : public material {
public:
  blinn(const vec3 &a, double f) : albedo(a) {
    name = "blinn";
    fuzz = fmin(1.0, f);
  };
  virtual bool scatter(const ray &r_in, const hit_record &rec,
                       vec3 &attenuation, ray &scattered,
                       const std::vector<light_source *> &lights) const {
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());

    attenuation = albedo;
    return dot(scattered.direction(), rec.normal) > 0;
  };
  vec3 albedo;
  double fuzz;
};

#endif
