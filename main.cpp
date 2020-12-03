#include "ray.h"
#include <bits/stdc++.h>
#include <cassert>

#define rep(i, n) for (int i = 0; i < n; i++)
using namespace std;

color lerp(ray r, color c1, color c2) {
  vec3 normal = unit_vector(r.direction());
  double t = (double)(normal.y() + 1) / 2.0;
  // cout << r.direction() << endl;
  // cout << normal << endl;
  // cout << t << endl << endl;
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
  for (int i = ny - 1; i >= 0; i--) {
    for (int j = 0; j < nx; j++) {
      double u = double(j) / double(nx);
      double v = double(i) / double(ny);
      ray r(origin, upper_left + u * hori - v * vert);
      color c1(1.0, 1.0, 1.0);
      color c2(0.5, 0.7, 1.0);
      color col = lerp(r, c1, c2);
      color icol;
      rep(i, 3) icol[i] = int(255.99 * col[i]);
      cout << icol << endl;
    }
  }

  return 0;
}
