#include "models/camera.h"
#include "models/dielectric.h"
#include "models/hitable.h"
#include "models/hitable_list.h"
#include "models/lambertian.h"
#include "models/light_source.h"
#include "models/material.h"
#include "models/metal.h"
#include "models/parallel_light.h"
#include "models/ray.h"
#include "models/sphere.h"
#include "models/spot_light.h"
#include "models/vec3.h"
#include <bits/stdc++.h>
#include <cassert>
#include <cstdlib>
#define rep(i, n) for (int i = 0; i < n; i++)
using namespace std;

hitable *random_scene() {
  int n = 500;
  vector<hitable *> list;
  list.push_back(new sphere(point3(0, -1000, 0), 1000,
                            new lambertian(color(0.5, 0.5, 0.5))));
  int i = 1;
  for (int a = -3; a < 3; a++) {
    for (int b = -3; b < 3; b++) {
      double choose_mat = drand48();
      point3 center(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
      if ((center - point3(4, 0.2, 0)).length() > 0.9) {
        if (choose_mat < 0.8) { // difuse
          list.push_back(new sphere(
              center, 0.2,
              new lambertian(color(drand48() * drand48(), drand48() * drand48(),
                                   drand48() * drand48()))));
        } else if (choose_mat < 0.95) { // metal
          list.push_back(new sphere(
              center, 0.2,
              new metal(color(0.5 * (1 + drand48()), 0.5 * (1 + drand48()),
                              0.5 * (1 + drand48())),
                        0.5 * (1 + drand48()))));
        } else {
          list.push_back(new sphere(center, 0.2, new dielectric(1.5)));
        }
      }
    }
  }
  list.push_back(new sphere(point3(0, 1, 0), 1.0, new dielectric(1.5)));
  list.push_back(
      new sphere(point3(-4, 1, 0), 1.0, new lambertian(color(0.4, 0.2, 0.1))));
  list.push_back(
      new sphere(point3(4, 1, 0), 1.0, new metal(color(0.7, 0.6, 0.5), 0.0)));

  vector<light_source *> lights;
  lights.push_back(
      new spot_light(point3(3.0, 100.0, -25.0), color(1.0, 1.0, 1.0), 2.0));
  lights.push_back(
      new spot_light(point3(-2.0, 10.0, 1.0), color(1.0, 1.0, 1.0), 2.0));
  lights.push_back(
      new spot_light(point3(2.0, 21.0, 8.0), color(1.0, 1.0, 1.0), 2.0));
  lights.push_back(
      new spot_light(point3(-2.0, 10.0, -9.0), color(1.0, 1.0, 1.0), 2.0));
  lights.push_back(
      new parallel_light(vec3(10.0, 5.0, 0.0), color(1.0, 1.0, 1.0), 2.0));
  return new hitable_list(list, list.size(), lights);
}

inline color blinn_color(const color &ambient, const hit_record &rec,
                         const ray &r, const hitable_list *world) {
  vector<light_source *> lights = world->lights;
  assert(lights.size());
  color col;
  for (const light_source *light : lights) {
    // TODO: shoot ray towards light and if it's blocked intensity is zero
    point3 hit_point = r.at(rec.t);
    ray light_ray = light->get_ray(hit_point, rec);
    vec3 light_vec = unit_vector(light->get_ray(hit_point, rec).direction());
    vec3 view_vec = -unit_vector(r.direction());
    vec3 half = (view_vec + light_vec) / 2.0;
    vec3 normal = unit_vector(rec.normal);
    double light_intensity = fmax(0.0, dot(normal, light_vec));
    hit_record light_rec;
    if (world->hit(light_ray, 0.001, 1e9,
                   light_rec)) { // something in middle of light and hit point
      // compare t and dist to the light
      double dist_light = light->get_dist(hit_point);
      double dist_obj = dist(hit_point, light_ray.at(light_rec.t));
      if (dist_light > dist_obj) {
        // if something is in the middle, drop the
        light_intensity = 0.0;
      }
    }
    double blinn = fmax(0.0, dot(normal, half));
    double shininess = 6.5;
    double spec_amount = pow(blinn, shininess);
    color specular = light->col * spec_amount;
    color diffuse = ambient * light->col * light_intensity;
    col += (specular * 0.8 + diffuse * 0.8 + ambient * 0.4) * light->intensity;
  }
  double total_intensity = world->light_sum;
  col /= total_intensity;
  col[0] = fmin(1.0, col[0]);
  col[1] = fmin(1.0, col[1]);
  col[2] = fmin(1.0, col[2]);
  return col;
}

color getColor(const ray &r, hitable *world, int depth = 0) {
  hit_record rec;
  if (world->hit(r, 0.001, 1e9, rec)) {
    ray scattered;
    vec3 attenuation;
    color ambient = attenuation;
    hitable_list *_world = (hitable_list *)world;
    if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
      color ambient = attenuation;
      point3 hit_point = r.at(rec.t);
      double light_sum = _world->get_total_light(hit_point);
      assert(light_sum <= _world->light_sum);
      double light_ratio = 0.0;
      if (_world->lights.size()) {
        light_ratio = light_sum / _world->light_sum;
      }
      color col = getColor(scattered, world, depth + 1);
      ambient = ambient * col;
      return blinn_color(ambient, rec, r, _world);
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
  int nx = 300;
  int ny = 200;
  int ns = 30;
  cout << "P3" << endl << nx << " " << ny << endl << 255 << endl;
  vec3 lookfrom(13.0, 2.0, 3.0);
  vec3 lookat(0.0, 0.0, 0.0);
  vec3 up_vector(0.0, 1.0, 0.0);
  double focal_length = (lookfrom - lookat).length();
  double aparture = 0.1;
  camera cam(lookfrom, lookat, up_vector, 20, double(nx) / double(ny), aparture,
             focal_length);

  hitable *world = random_scene();
  rep(i, ny) {
    rep(j, nx) {
      color col;
      rep(_, ns) {
        double u = double(j + drand48()) / double(nx);
        double v = double(i + drand48()) / double(ny);
        ray r = cam.get_ray(u, v);
        color now = getColor(r, world);

        col += now;
      }
      col /= (double)ns;
      color icol;
      rep(i, 3) icol[i] = int(255.99 * sqrt(col[i]));
      cout << icol << endl;
    }
  }
  return 0;
}
