#pragma once
#include "Material.h"

class Metal : public Material {
  public:
    Metal(const Vec3& a, double fuzz) : m_albedo(a), m_fuzz(fuzz < 1 ? fuzz : 1) {}

    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const;

  private:
    Vec3 m_albedo;
    double m_fuzz;
};