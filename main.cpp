#include "models/camera.h"
#include "models/dielectric.h"
#include "models/hitable.h"
#include "models/hitable_list.h"
#include "models/lambertian.h"
#include "models/material.h"
#include "models/metal.h"
#include "models/ray.h"
#include "models/sphere.h"
#include "models/vec3.h"
#include <bits/stdc++.h>
#include <cassert>
#include <cstdlib>
#define rep(i, n) for (int i = 0; i < n; i++)
using namespace std;

color getColor(const ray &r, hitable *world, int depth = 0) {
  hit_record rec;
  if (world->hit(r, 0.01, 1e9, rec)) {
    ray scattered;
    vec3 attenuation;
    if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
      return attenuation * getColor(scattered, world, depth + 1);
    } else {
      return color(0.0, 0.0, 0.0);
    }
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
  int ns = 100;
  cout << "P3" << endl << nx << " " << ny << endl << 255 << endl;
  camera cam;

  vector<hitable *> list;
  list.push_back(new sphere(vec3(0.0, 0.0, -1.0), 0.5,
                            new lambertian(vec3(0.8, 0.3, 0.3))));
  list.push_back(new sphere(vec3(0.0, -100.5, -1.0), 100.0,
                            new lambertian(vec3(0.8, 0.8, 0.0))));
  list.push_back(
      new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.3)));
  list.push_back(new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5)));
  list.push_back(new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5)));
  hitable *world = new hitable_list(list, list.size());

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
      rep(i, 3) icol[i] = int(255.99 * sqrt(col[i]));
      cout << icol << endl;
    }
  }
  return 0;
}
