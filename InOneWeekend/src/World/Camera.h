#pragma once

#include "InOneWeekend.h"

class Camera {
  public:
    Camera() : lowerLeftCorner(-2.0, -1.5, -1.0), horizontal(4.0, 0.0, 0.0), vertical(0.0, 3.0, 0.0) {}

    Ray getRay(double u, double v) {
      return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
    }

  private:
    Vec3 origin;
    Vec3 lowerLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;
};