#pragma once

#include "Hittable.h"
#include "Math/Vec3.h"

class Sphere : public Hittable {
  public:
    Sphere() : m_radius(1.0) {};
    Sphere  (Vec3 center, double radius) : m_center(center), m_radius(radius) {}

    virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const;
  private:
    Vec3 m_center;
    double m_radius;
};