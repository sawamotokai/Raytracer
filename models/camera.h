#ifndef CAMERAH
#define CAMERAH

#include "ray.h"
#include "vec3.h"

class camera {
public:
  camera(vec3 &lookfrom, vec3 &lookat, vec3 &up_vector, double fov,
         double aspect, double aparture, double focal_length) {
    lens_radius = aparture / 2.0;
    double theta = fov * M_PI / 180;
    double half_h = tan(theta / 2.0);
    double half_w = half_h * aspect;
    origin = lookfrom;
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(up_vector, w));
    v = cross(w, u);
    upper_left = origin - focal_length * u * half_w +
                 focal_length * v * half_h - focal_length * w;
    hori = 2.0 * focal_length * half_w * u;
    vert = 2.0 * focal_length * half_h * v;
  }

  ray get_ray(double s, double t) {
    vec3 rd = lens_radius * random_in_unit_disk();
    vec3 offset = rd.x() * u + rd.y() * v;
    return ray(origin + offset,
               upper_left + s * hori - t * vert - (origin + offset));
  }

  point3 upper_left;
  point3 origin;
  vec3 vert;
  vec3 hori;
  vec3 u, v, w;
  double lens_radius;
};

#endif
