#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"
#include <vector>

using namespace std;

class hitable_list : public hitable {
public:
  hitable_list(){};
  hitable_list(vector<hitable *> l, int size) : list(l), list_size(size){};
  vector<hitable *> list;
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
