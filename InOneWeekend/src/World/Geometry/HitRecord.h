#pragma once

#include "Math/Ray.h"

class Material;

struct HitRecord {
  Vec3 p;
  Vec3 normal;
  shared_ptr<Material> material;
  double t = 0.0;
  bool frontFace = 0;

  inline void setFaceNormal(const Ray& r, const Vec3& outwardNormal) {
    frontFace = dot(r.direction(), outwardNormal) < 0;
    normal = frontFace ? outwardNormal : -outwardNormal;
  }
};
