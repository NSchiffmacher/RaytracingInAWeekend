#pragma once

#include <Eigen/Dense>

namespace raytracing
{

using Vector3 = Eigen::Matrix<double, 3, 1>;
using Point3 = Eigen::Matrix<double, 3, 1>;

inline bool near_zero(const Vector3& vector)
{
  const auto s = 1e-8;
  return std::fabs(vector.x()) < s && std::fabs(vector.y()) < s && std::fabs(vector.z()) < s;
}

inline Vector3 reflect(const Vector3& vector, const Vector3& normal)
{
  return Vector3{vector - 2 * vector.dot(normal) * normal};
}
// provides : .norm()
// .squaredNorm()

}
