#pragma once

#include "InOneWeekend.h"

class Camera {
  public:
    Camera(Vec3 position, Vec3 target, Vec3 up, double verticalFov, double aspect, double aperture, double focusDistance) {
      m_origin = position;
      m_lensRadius = aperture / 2;

      double theta = degToRad(verticalFov);
      double halfHeight = tan(theta / 2);
      double halfWidth = aspect * halfHeight;

      w = unitVector(position - target);
      u = unitVector(cross(up, w));
      v = cross(w, u);


      m_lowerLeftCorner = m_origin 
                          - focusDistance * halfWidth * u
                          - focusDistance * halfHeight * v
                          - focusDistance * w;

      m_horizontal = 2 * halfWidth * focusDistance * u;
      m_vertical = 2 * halfHeight * focusDistance * v;
    }

    Ray getRay(double s, double t) {
      Vec3 rd = m_lensRadius * randomInUnitDisk();
      Vec3 offset = u * rd.x() + v * rd.y();

      return Ray(m_origin + offset, m_lowerLeftCorner + s * m_horizontal + t * m_vertical - m_origin - offset);
    }

  private:
    Vec3 m_origin;
    Vec3 m_lowerLeftCorner;
    Vec3 m_horizontal;
    Vec3 m_vertical;
    Vec3 u, v, w;
    double m_lensRadius;
};