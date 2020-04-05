#include "Sphere.h"

bool Sphere::hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const {
  Vec3 oc = r.origin() - m_center; // The origin of the sphere

  double a = r.direction().lengthSquared(); // 'a' term of the quadratic equation representing the ray intersection with the sphere
  double halfB = dot(oc, r.direction()); // 'b' term can be halved to simplify the equation
  double c = oc.lengthSquared() - m_radius * m_radius; // 'c' term
  double discriminant = halfB * halfB - a * c;

  // If the discriminant is positive, the quadratic equation has two solutions.
  // This means there is an intersection between the ray and the sphere.
  if (discriminant > 0) {
    double root = sqrt(discriminant);
    double t = (-halfB - root) / a;
    if (t < tMax && t > tMin) {
      rec.t = t;
      rec.p = r.at(rec.t);
      Vec3 outwardNormal = (rec.p - m_center) / m_radius;
      rec.setFaceNormal(r, outwardNormal);
      rec.material = m_material;

      return true;
    }

    t = (-halfB + root) / a;
    if (t < tMax && t > tMin) {
      rec.t = t;
      rec.p = r.at(rec.t);
      Vec3 outwardNormal = (rec.p - m_center) / m_radius;
      rec.setFaceNormal(r, outwardNormal);
      rec.material = m_material;

      return true;
    }
  }

  return false;
}
