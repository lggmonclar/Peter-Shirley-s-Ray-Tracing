#include "HittableList.h"

bool HittableList::hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const {
  HitRecord tempHitRecord;
  bool hasHitAnything = false;
  double closest = tMax;

  for (const auto& object : objects) {
    if (object->hit(r, tMin, closest, tempHitRecord)) {
      hasHitAnything = true;
      closest = tempHitRecord.t;
      rec = tempHitRecord;
    }
  }

  return hasHitAnything;
}
