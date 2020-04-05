#pragma once

#include "Math/Ray.h"
#include "HitRecord.h"

class Hittable {
  public:
    virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const = 0;
};