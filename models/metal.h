#ifndef METALH
#define METALH

#include "material.h"
#include "vec3.h"

class metal : public material {
public:
  metal(const vec3 &a) : albedo(a) { name = "meta;"; };
  virtual bool scatter(const ray &r_in, const hit_record &rec,
                       vec3 &attenuation, ray &scattered) const {
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return true;
  };
  vec3 albedo;
};

#endif
