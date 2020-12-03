#include "ray.h"
#include <bits/stdc++.h>
#include <cassert>

#define rep(i, n) for (int i = 0; i < n; i++)
using namespace std;

bool hit_sphere(point3 center, double radius, ray r) {
  double a = dot(r.direction(), r.direction());
  double b = 2.0 * dot(r.direction(), r.origin() - center);
  double c = dot(r.origin() - center, r.origin() - center) - radius * radius;
  double d = b * b - 4 * a * c;
  return d >= 0;
}

color getColor(ray r) {
  if (hit_sphere(vec3(0.0, 0.0, -1.0), 0.5, r))
    return color(1.0, 0.0, 0.0);
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
  point3 upper_left(-2.0, 1.0, -1.0);
  point3 origin(0.0, 0.0, 0.0);
  vec3 vert(0.0, 2.0, 0.0);
  vec3 hori(4.0, 0.0, 0.0);

  //   rep(i, ny) {
  //     rep(j, nx) {
  rep(i, ny) {
    rep(j, nx) {
      double u = double(j) / double(nx);
      double v = double(i) / double(ny);
      ray r(origin, upper_left + u * hori - v * vert);
      color col = getColor(r);
      color icol;
      rep(i, 3) icol[i] = int(255.99 * col[i]);
      cout << icol << endl;
    }
  }

  return 0;
}
