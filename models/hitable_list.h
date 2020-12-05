#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"
#include "light_source.h"
#include <vector>

using namespace std;

class hitable_list : public hitable {
public:
  hitable_list(){};
  hitable_list(const vector<hitable *> list, int size,
               const vector<light_source *> lights)
      : list(list), list_size(size), lights(lights) {
    for (light_source *l : lights) {
      light_sum += l->intensity;
    }
  };
  double get_total_light(const point3 &hit_point) {
    double sum = 0.0;
    for (light_source *light : lights) {
      hit_record light_rec;
      ray light_ray = light->get_ray(hit_point);
      if (hit(light_ray, 0.001, 1e9, light_rec)) {
        // compare t and dist to the light
        double dist_light = light->get_dist(hit_point);
        double dist_obj = dist(hit_point, light_ray.at(light_rec.t));
        if (dist_light < dist_obj)
          sum += light->intensity;
      } else {
        // parallel light applys
        sum += light->intensity;
      }
    }
    return sum;
  };
  vector<hitable *> list;
  vector<light_source *> lights;
  double light_sum;
  int list_size;
  virtual bool hit(const ray &r, double tmin, double tmax,
                   hit_record &rec) const;
};

bool hitable_list::hit(const ray &r, double tmin, double tmax,
                       hit_record &rec) const {
  hit_record temp;
  bool hit_any = false;
  double closest = tmax;
  for (hitable *obj : list) {
    if (obj->hit(r, tmin, tmax, temp)) {
      if (closest >= temp.t) {
        hit_any = true;
        closest = temp.t;
        rec = temp;
      }
    }
  }
  return hit_any;
}

#endif
