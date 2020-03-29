#pragma once

#include "Math/Ray.h"

struct HitRecord {
  Vec3 p;
  Vec3 normal;
  double t = 0.0;
  bool frontFace = 0;

  inline void setFaceNormal(const Ray& r, const Vec3& outwardNormal) {
    frontFace = dot(r.direction(), outwardNormal) < 0;
    normal = frontFace ? outwardNormal : -outwardNormal;
  }
};

class Hittable {
  public:
    virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const = 0;
};