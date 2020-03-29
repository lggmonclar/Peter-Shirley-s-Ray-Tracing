#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Usings

using std::shared_ptr;
using std::make_shared;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degToRad(double degrees) {
  return degrees * pi / 180;
}

inline double ffmin(double a, double b) { return a <= b ? a : b; }
inline double ffmax(double a, double b) { return a >= b ? a : b; }

inline double randomDouble() {
  // Returns a random double in [0, 1)
  return rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max) {
  // Returns a random double in [min, max)
  return min + (max - min) * randomDouble();
}

inline double clamp(double x, double min, double max) {
  if (x < min) return min;
  if (x > max) return max;

  return x;
}

// Common Headers

#include "Math/Ray.h"
#include "Math/Vec3.h"