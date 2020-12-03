#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera {
public:
  camera() {
    upper_left = point3(-2.0, 1.0, -1.0);
    origin = point3(0.0, 0.0, 0.0);
    vert = vec3(0.0, 2.0, 0.0);
    hori = vec3(4.0, 0.0, 0.0);
  }

  ray get_ray(double u, double v) {
    return ray(origin, upper_left + u * hori - v * vert);
  }

  point3 upper_left;
  point3 origin;
  vec3 vert;
  vec3 hori;
};

#endif
