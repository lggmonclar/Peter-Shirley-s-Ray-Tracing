#include "InOneWeekend.h"

#include "World/HittableList.h"
#include "World/Geometry/Sphere.h"
#include "World/Camera.h"

#include "Rendering/Materials/Lambertian.h"
#include "Rendering/Materials/Metal.h"
#include "Rendering/Materials/Dielectric.h"

#include <iostream>

HittableList randomScene() {
  HittableList world;

  world.add(make_shared<Sphere>(
    Vec3(0, -1000, 0), 1000, make_shared<Lambertian>(Vec3(0.5, 0.5, 0.5))));

  int i = 1;
  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = randomDouble();
      Vec3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());
      if ((center - Vec3(4, 0.2, 0)).length() > 0.9) {
        if (choose_mat < 0.8) {
          // diffuse
          auto albedo = random() * random();
          world.add(
            make_shared<Sphere>(center, 0.2, make_shared<Lambertian>(albedo)));
        }
        else if (choose_mat < 0.95) {
          // Metal
          auto albedo = random(.5, 1);
          auto fuzz = randomDouble(0, .5);
          world.add(
            make_shared<Sphere>(center, 0.2, make_shared<Metal>(albedo, fuzz)));
        }
        else {
          // glass
          world.add(make_shared<Sphere>(center, 0.2, make_shared<Dielectric>(1.5)));
        }
      }
    }
  }

  world.add(make_shared<Sphere>(Vec3(0, 1, 0), 1.0, make_shared<Dielectric>(1.5)));

  world.add(
    make_shared<Sphere>(Vec3(-4, 1, 0), 1.0, make_shared<Lambertian>(Vec3(0.4, 0.2, 0.1))));

  world.add(
    make_shared<Sphere>(Vec3(4, 1, 0), 1.0, make_shared<Metal>(Vec3(0.7, 0.6, 0.5), 0.0)));

  return world;
}

Vec3 calculateRayColor(const Ray& r, const Hittable& world, int depth) {
  HitRecord rec;
  if (depth == 0)
    return Vec3();

  if (world.hit(r, 0.001, infinity, rec)) {
    Ray scattered;
    Vec3 attenuation;
    if (rec.material->scatter(r, rec, attenuation, scattered)) {
      return attenuation * calculateRayColor(scattered, world, depth - 1);
    }
    return Vec3();
  }

  Vec3 unitDirection = unitVector(r.direction());
  double t = 0.5 * (unitDirection.y() + 1.0);
  return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

int main() {
  const int imageWidth = 800;
  const int imageHeight = 600;
  const int samplesPerPixel = 100;
  const int maxDepth = 50;
  const double aspectRatio = double(imageWidth) / imageHeight;
  Vec3 cameraPosition(13, 2, 3);
  Vec3 cameraTarget(0, 0, 0);
  Vec3 up(0, 1, 0);
  double distToFocus = (cameraPosition - cameraTarget).length();
  double aperture = 0.1;

  std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
  HittableList world = randomScene();

  Camera camera(cameraPosition, cameraTarget, Vec3(0, 1, 0), 30, double(imageWidth) / imageHeight, aperture, distToFocus);

  for (int j = imageHeight - 1; j >= 0; j--) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < imageWidth; i++) {
      Vec3 color;
      for (int s = 0; s < samplesPerPixel; s++) {
        double u = (i + randomDouble()) / imageWidth;
        double v = (j + randomDouble()) / imageHeight;
        Ray r = camera.getRay(u, v);
        color += calculateRayColor(r, world, maxDepth);
      }
      color.writeColor(std::cout, samplesPerPixel);
    }
  }

  std::cerr << "\nDone.\n";
}