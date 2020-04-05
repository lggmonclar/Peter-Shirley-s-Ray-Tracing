#pragma once
#include "InOneWeekend.h"

struct HitRecord;

class Material {
  public:
    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const = 0;
};