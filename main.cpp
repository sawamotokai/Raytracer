#include "hitable.h"
#include "hitable_list.h"
#include "ray.h"

#include "camera.h"
#include "sphere.h"
#include "vec3.h"
#include <bits/stdc++.h>
#include <cassert>
#include <cstdlib>

#define rep(i, n) for (int i = 0; i < n; i++)
using namespace std;

color getColor(const ray &r, hitable *world) {
  hit_record rec;
  if (world->hit(r, 0.0001, 1e9, rec)) {
    vec3 rand_target = rec.p + rec.normal + random_in_unit_sphere();
    return 0.5 * getColor(ray(rec.p, rand_target - rec.p), world);
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
  int ns = 10;
  cout << "P3" << endl << nx << " " << ny << endl << 255 << endl;
  camera cam;

  vector<hitable *> list;
  list.push_back(new sphere(vec3(0.0, 0.0, -1.0), 0.5));
  list.push_back(new sphere(vec3(0.0, -100.5, -1.0), 100.0));
  hitable *world = new hitable_list(list, 2);

  rep(i, ny) {
    rep(j, nx) {
      color col;
      rep(_, ns) {
        double u = double(j + drand48()) / double(nx);
        double v = double(i + drand48()) / double(ny);
        ray r = cam.get_ray(u, v);
        col += getColor(r, world);
      }
      col /= (double)ns;
      color icol;
      rep(i, 3) icol[i] = int(255.99 * col[i]);
      cout << icol << endl;
    }
  }
  return 0;
}
