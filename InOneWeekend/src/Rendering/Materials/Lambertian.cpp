#include "Lambertian.h"

#include "World/Geometry/HitRecord.h"

bool Lambertian::scatter(const Ray& rIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const {
  Vec3 scatterDir = rec.normal + randomUnitVector();
  scattered = Ray(rec.p, scatterDir);
  attenuation = m_albedo;
  return true;
}
