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

#ifndef VECTOR3_H
#define VECTOR3_H

#include "Matrix.h"

namespace SML {

/// \brief Vector in 3D space
///
/// A vector is a Matrix with 1 column and 4 rows. The first three elements
/// define the X, Y and Z coordinates. The fourth element is always 0.
class Vector3 : public Matrix
{
public:
  /// Constructor
  Vector3()
    : Matrix(4, 1)
  {
  }

  /// Constructor
  ///
  /// \param[in] x X coordinate
  /// \param[in] y Y coordinate
  /// \param[in] z Z coordinate
  Vector3(double x, double y, double z)
    : Matrix(4, 1)
  {
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
  }

  /// Constructor
  ///
  /// \param[in] xyz Array with X, Y and Z coordinates
  Vector3(double xyz[])
    : Matrix(4, 1)
  {
    m_data[0] = xyz[0];
    m_data[1] = xyz[1];
    m_data[2] = xyz[2];
  }

  /// Copy constructor
  Vector3(const Vector3 &other) // Needed?
    : Matrix(other)
  {
  }

  /// Copy constructor
  ///
  /// \param[in] other Other matrix
  /// \exception std::out_of_range Matrix dimensions out of range
  Vector3(const Matrix &other)
    : Matrix(4, 1)
  {
    if (other.rows() != 4
        || other.cols() != 1)
    {
      throw std::out_of_range("Matrix dimensions do not match vector dimensions");
    }

    m_data[0] = other(0,0);
    m_data[1] = other(1,0);
    m_data[2] = other(2,0);
  }

  /// Assignment operator
  Vector3& operator=(Vector3 other)
  {
    Matrix::operator=(other);
    return *this;
  }

  /// Desctructor
  virtual ~Vector3() override
  {
  }

  void x(double val) { m_data[0] = val; }
  double x() const   { return m_data[0]; }
  void y(double val) { m_data[1] = val; }
  double y() const   { return m_data[1]; }
  void z(double val) { m_data[2] = val; }
  double z() const   { return m_data[2]; }

  /// Get coordinates as array.
  ///
  /// \return Coordinates
  double* array() { return m_data.data(); }

  /// Subtract matrix from vector.
  ///
  /// \param[in] other Matrix to subtract
  /// \exception std::out_of_range Matrix dimensions out of range
  /// \return Subtracted vector
  Vector3 operator-(const Matrix &other) const
  {
    if (other.rows() != 4
        || other.cols() != 1)
    {
      throw std::out_of_range("Matrix dimensions do not match vector dimensions");
    }

    Vector3 result;
    result.x(x() - other(0,0));
    result.y(y() - other(1,0));
    result.z(z() - other(2,0));
    return result;
  }

  /// Add matrix to vector.
  ///
  /// \param[in] other Matrix to add
  /// \exception std::out_of_range Matrix dimensions out of range
  /// \return Added vector
  Vector3 operator+(const Matrix &other) const
  {
    if (other.rows() != 4
        || other.cols() != 1)
    {
      throw std::out_of_range("Matrix dimensions do not match vector dimensions");
    }

    Vector3 result;
    result.x(x() + other(0,0));
    result.y(y() + other(1,0));
    result.z(z() + other(2,0));
    return result;
  }

  /// Multiply vector by scalar.
  ///
  /// \param[in] scalar
  /// \return Multiplied vector
  Vector3 operator*(double scalar) const
  {
    Vector3 result;
    result.x(x() * scalar);
    result.y(y() * scalar);
    result.z(z() * scalar);
    return result;
  }

  /// Calculate length of vector.
  ///
  /// \return Length
  double length() const
  {
    return sqrt( (x() * x()) + (y() * y()) + (z() * z()) );
  }

  /// Normalize the vector.
  /// A normalized vector has length = 1.
  void normalize()
  {
    double l = length();
    x(x() / l);
    y(y() / l);
    z(z() / l);
  }

  /// Get normalized copy of vector.
  /// A normalized vector has length = 1.
  ///
  /// \return Normalized vector
  Vector3 normalized() const
  {
    double l = length();

    Vector3 result;
    result.x(x() / l);
    result.y(y() / l);
    result.z(z() / l);
    return result;
  }

  /// Calculate dot product with vector.
  /// Dot product = 0: vectors are orthogonal (perpendicular).
  /// Dot product = 1: vectors are parallel.
  ///
  /// \param[in] other Other vector
  /// \return Dot product
  double dot(const Vector3 &other) const
  {
    return x() * other.x() + y() * other.y() + z() * other.z();
  }

  /// Calculate angle with vector.
  ///
  /// \param[in] other Other vector
  /// \return Angle in radians
  double angle(const Vector3 &other) const
  {
    return acos((this->dot(other)) / (this->length() * other.length()));
  }

  /// Calculate cross product with vector.
  /// The cross product is perpendicular to the two input vectors.
  ///
  /// \param[in] other Other vector
  /// \return Cross product
  Vector3 cross(const Vector3 &other) const
  {
    Vector3 result;
    result.x(y() * other.z() - z() * other.y());
    result.y(z() * other.x() - x() * other.z());
    result.z(x() * other.y() - y() * other.x());
    return result;
  }

  /// Project vector onto vector.
  ///
  /// \param[in] other Vector to project
  /// \return Projected vector
  Vector3 project(const Vector3 &other) const
  {
    return other.normalized() * (this->dot(other) / other.length());
  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const Vector3 &vector)
  {
    os << "Vector3 (";
    os << vector.x() << ", ";
    os << vector.y() << ", ";
    os << vector.z() << ", 0)\n";
    return os;
  }
};

} // namespace SML

#endif // VECTOR3_H
