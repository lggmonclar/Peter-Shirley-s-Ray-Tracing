#pragma once

#include "World/Geometry/Hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable {
  public:
    HittableList() = default;
    HittableList(shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<Hittable> object) { objects.push_back(object); }

    virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const;

  private:
    std::vector<shared_ptr<Hittable>> objects;
};