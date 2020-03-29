#pragma once

#include <iostream>
#include "InOneWeekend.h"

class Vec3 {
  public:
    Vec3() : m_elements{ 0, 0, 0 } {};
    Vec3(double e0, double e1, double e2) : m_elements{ e0, e1, e2 } {}

    double x() const { return m_elements[0]; }
    double y() const { return m_elements[1]; }
    double z() const { return m_elements[2]; }

    Vec3 operator-() const { return Vec3(-m_elements[0], -m_elements[1], -m_elements[2]); }
    double operator[](int i) const { return m_elements[i]; }
    double& operator[](int i) { return m_elements[i]; }

    Vec3& operator+=(const Vec3& v) {
      m_elements[0] += v.m_elements[0];
      m_elements[1] += v.m_elements[1];
      m_elements[2] += v.m_elements[2];

      return *this;
    }

    Vec3& operator*=(const double t) {
      m_elements[0] *= t;
      m_elements[1] *= t;
      m_elements[2] *= t;
      return *this;
    }

    Vec3& operator/=(const double t) {
      return *this *= 1 / t;
    }

    double length() const {
      return sqrt(lengthSquared());
    }

    double lengthSquared() const {
      return m_elements[0] * m_elements[0] + m_elements[1] * m_elements[1] + m_elements[2] * m_elements[2];
    }

    void writeColor(std::ostream& out, int samplesPerPixel) {
      // Divide the color total by the number of samples
      double scale = 1.0 / samplesPerPixel;
      double r = scale * m_elements[0];
      double g = scale * m_elements[1];
      double b = scale * m_elements[2];

      // Write the translated [0, 255] value of each color component
      out << static_cast<int>(255.999 * clamp(r, 0.0, 0.999)) << ' '
          << static_cast<int>(255.999 * clamp(g, 0.0, 0.999)) << ' '
          << static_cast<int>(255.999 * clamp(b, 0.0, 0.999)) << '\n';
    }

    // vec3 utility functions

    friend inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
      return out << v.m_elements[0] << ' ' << v.m_elements[1] << ' ' << v.m_elements[2];
    }

    friend inline Vec3 operator+(const Vec3& u, const Vec3& v) {
      return Vec3(u.m_elements[0] + v.m_elements[0], u.m_elements[1] + v.m_elements[1], u.m_elements[2] + v.m_elements[2]);
    }

    friend inline Vec3 operator-(const Vec3& u, const Vec3& v) {
      return Vec3(u.m_elements[0] - v.m_elements[0], u.m_elements[1] - v.m_elements[1], u.m_elements[2] - v.m_elements[2]);
    }

    friend inline Vec3 operator*(const Vec3& u, const Vec3& v) {
      return Vec3(u.m_elements[0] * v.m_elements[0], u.m_elements[1] * v.m_elements[1], u.m_elements[2] * v.m_elements[2]);
    }

    friend inline Vec3 operator*(double t, const Vec3& v) {
      return Vec3(t * v.m_elements[0], t * v.m_elements[1], t * v.m_elements[2]);
    }

    friend inline Vec3 operator*(const Vec3& v, double t) {
      return t * v;
    }

    friend inline Vec3 operator/(Vec3 v, double t) {
      return (1 / t) * v;
    }

  private:
    double m_elements[3];
};


inline double dot(const Vec3& u, const Vec3& v) {
  return u.x() * v.x()
    + u.y() * v.y()
    + u.z() * v.z();
}

inline Vec3 cross(const Vec3& u, const Vec3& v) {
  return Vec3(u.y() * v.z() - u.z() * v.y(),
              u.z() * v.x() - u.x() * v.z(),
              u.x() * v.y() - u.y() * v.x());
}

inline Vec3 unitVector(Vec3 v) {
  return v / v.length();
}