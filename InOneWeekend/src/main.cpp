#include "InOneWeekend.h"

#include "World/HittableList.h"
#include "World/Geometry/Sphere.h"
#include "World/Camera.h"

#include <iostream>

Vec3 calculateRayColor(const Ray& r, const Hittable &world) {
  HitRecord rec;
  if (world.hit(r, 0, infinity, rec)) {
    return 0.5 * (rec.normal + Vec3(1.0, 1.0, 1.0));
  }

  Vec3 unitDirection = unitVector(r.direction());
  double t = 0.5 * (unitDirection.y() + 1.0);
  return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

int main() {
  const int imageWidth = 800;
  const int imageHeight = 600;
  const int samplesPerPixel = 100;

  std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
  HittableList world;
  world.add(make_shared<Sphere>(Vec3(0.0, 0.0, -1.0), 0.5));
  world.add(make_shared<Sphere>(Vec3(-1.0, -1.0, -1.0), 0.5));
  world.add(make_shared<Sphere>(Vec3(-1.0, 1.0, -1.0), 0.5));
  world.add(make_shared<Sphere>(Vec3(1.0, 1.0, -1.0), 0.5));
  world.add(make_shared<Sphere>(Vec3(1.0, 1.0, -1.0), 0.5));

  world.add(make_shared<Sphere>(Vec3(0.0, -100.5, -1.0), 100));

  Camera camera;

  for (int j = imageHeight - 1; j >= 0; j--) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < imageWidth; i++) {
      Vec3 color;
      for (int s = 0; s < samplesPerPixel; s++) {
        double u = (i + randomDouble()) / imageWidth;
        double v = (j + randomDouble()) / imageHeight;
        Ray r = camera.getRay(u, v);
        color += calculateRayColor(r, world);
      }
      color.writeColor(std::cout, samplesPerPixel);
    }
  }

  std::cerr << "\nDone.\n";
}