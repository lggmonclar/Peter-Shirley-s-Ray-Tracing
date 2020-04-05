#pragma once
#include "Material.h"

class Dielectric : public Material {
  public:
  Dielectric(double refractionIndex) : m_refractionIndex(refractionIndex) {}

  virtual bool scatter(const Ray& rIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const;
  double schlick(double cosine, double refIdx) const;

  private:
  double m_refractionIndex;
};