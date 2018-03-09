/*
 * Program: Spatial Math Library
 *
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#ifndef UTIL_H
#define UTIL_H

#include <cmath>  // std::atan

namespace SML {

/// Pi constant
const double PI = std::atan(1)*4;

/// Convert radians to degrees.
///
/// \param[in] radians Radians
/// \return Degrees
inline double rad2deg(double radians)
{
    return radians * (180 / PI);
}

/// Convert degrees to radians.
///
/// \param[in] degrees Degrees
/// \return Radians
inline double deg2rad(double degrees)
{
    return degrees * (PI / 180);
}

/// Solve a quadratic equation: ax^2 + bx + c =0
///
/// \param[in] a First coefficient
/// \param[in] b Second coefficient
/// \param[in] c Third coefficient
/// \param[out] x1 First solution (if exists). Lowest value
/// \param[out] x2 Second solution (if exists). Highest value
/// \return Number of unique solutions 0, 1 or 2
inline int solveQuadratic(double a, double b, double c, double &x1, double &x2)
{
  // Compute discriminant
  double D = (b * b) - (4 * a * c);
  if (D < 0)
  {
    return 0;
  }

  // Calculate x's
  x1 = (-b - sqrt(D)) / (2 * a);
  x2 = (-b + sqrt(D)) / (2 * a);

  // Swap if necessary
  if (x1 > x2)
  {
    std::swap(x1, x2);
  }

  // Return number of solutions
  if (D > 0)
  {
    return 2;
  }
  else // D == 0
  {
    return 1;
  }
}

} // namespace SML

#endif // UTIL_H
