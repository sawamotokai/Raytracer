#ifndef DIELECTRICH
#define DIELECTRICH

#include "hitable.h"
#include "material.h"
#include "ray.h"
#include "vec3.h"
#include <cstdlib>

class dielectric : public material {
public:
  dielectric(double ri) : ref_idx(ri) { name = "dielectric"; };
  virtual bool scatter(const ray &r_in, const hit_record &rec,
                       vec3 &attenuation, ray &scattered) const {
    vec3 outward_normal;
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    double ni_over_nt;
    attenuation = vec3(1.0, 1.0, 1.0);
    vec3 refracted;
    double cosine;
    double reflect_prob = 1.0;
    if (dot(r_in.direction(), rec.normal) > 0) {
      ni_over_nt = ref_idx;
      outward_normal = -rec.normal;
      cosine = ref_idx * dot(r_in.direction(), rec.normal) /
               r_in.direction().length();
    } else {
      ni_over_nt = 1 / ref_idx;
      outward_normal = rec.normal;
      cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }
    if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
      reflect_prob = schlick(cosine, ref_idx);
    }
    if (drand48() < reflect_prob) {
      scattered = ray(rec.p, reflected);
    } else {
      scattered = ray(rec.p, refracted);
    }
    return true;
  };
  double ref_idx;
};

#endif
