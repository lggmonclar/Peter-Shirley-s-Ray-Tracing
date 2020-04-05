#pragma once

#include "Hittable.h"
#include "Math/Vec3.h"

class Sphere : public Hittable {
  public:
    Sphere() : m_radius(1.0) {};
    Sphere  (Vec3 center, double radius, shared_ptr<Material> material) : m_center(center), m_radius(radius), m_material(material) {}

    virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const;
  private:
    Vec3 m_center;
    double m_radius;
    shared_ptr<Material> m_material;
};