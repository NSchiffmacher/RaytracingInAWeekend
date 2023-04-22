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
inline Vector3 refract(const Vector3& uv, const Vector3& n, double etai_over_etat) {
  auto cos_theta = fmin(-uv.dot(n), 1.0);
  Vector3 r_out_perp =  Vector3{etai_over_etat * (uv + cos_theta*n)};
  Vector3 r_out_parallel = Vector3{-sqrt(fabs(1.0 - r_out_perp.squaredNorm())) * n};
  return r_out_perp + r_out_parallel;
}

// provides : .norm()
// .squaredNorm()

}
