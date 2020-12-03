#include "hitable.h"
#include "hitable_list.h"
#include "ray.h"

#include "camera.h"
#include "sphere.h"
#include "vec3.h"
#include <bits/stdc++.h>
#include <cassert>

#define rep(i, n) for (int i = 0; i < n; i++)
using namespace std;

color getColor(ray r, hitable *world) {
  hit_record rec;
  if (world->hit(r, 0.0, 1e9, rec)) {
    return 0.5 * (rec.normal + 1);
  }
  color c1(1.0, 1.0, 1.0);
  color c2(0.5, 0.7, 1.0);
  vec3 normal = unit_vector(r.direction());
  double t = (double)(normal.y() + 1) / 2.0;
  return (1 - t) * c1 + t * c2;
}

int main() {
  int nx = 200;
  int ny = 100;
  cout << "P3" << endl << nx << " " << ny << endl << 255 << endl;
  camera cam;

  vector<hitable *> list;
  list.push_back(new sphere(vec3(0.0, 0.0, -1.0), 0.5));
  list.push_back(new sphere(vec3(0.0, -100.5, -1.0), 100.0));
  hitable *world = new hitable_list(list, 2);

  rep(i, ny) {
    rep(j, nx) {
      double u = double(j) / double(nx);
      double v = double(i) / double(ny);
      ray r = cam.get_ray(u, v);
      color col = getColor(r, world);
      color icol;
      rep(i, 3) icol[i] = int(255.99 * col[i]);
      cout << icol << endl;
    }
  }

  return 0;
}
