#include "Dielectric.h"
#include "World/Geometry/HitRecord.h"

bool Dielectric::scatter(const Ray& rIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const {
  attenuation = Vec3(1.0, 1.0, 1.0);

  double etaOverEtaPrime = rec.frontFace ? 1.0 / m_refractionIndex : m_refractionIndex;

  Vec3 unitDirection = unitVector(rIn.direction());
  double cosTheta = ffmin(dot(-unitDirection, rec.normal), 1.0);
  double sinTheta = sqrt(1.0 - cosTheta * cosTheta);
  

  double reflectProbability = schlick(cosTheta, etaOverEtaPrime);
  if (etaOverEtaPrime * sinTheta > 1.0 || randomDouble() < reflectProbability) {
    // Must Reflect
    Vec3 reflected = reflect(unitDirection, rec.normal);
    scattered = Ray(rec.p, reflected);
    return true;
  }

  Vec3 refracted = refract(unitDirection, rec.normal, etaOverEtaPrime);
  scattered = Ray(rec.p, refracted);

  return true;
}

double Dielectric::schlick(double cosine, double refIdx) const {
  auto r0 = (1 - refIdx) / (1 + refIdx);
  r0 = r0 * r0;
  return r0 + (1 - r0) * pow((1 - cosine), 5);
}
