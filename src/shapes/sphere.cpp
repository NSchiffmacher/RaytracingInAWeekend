#include <shapes/sphere.hpp>

namespace raytracing
{

bool Sphere::intersectRay(const Ray& ray) const
{
  // t^2 * b⋅b + 2t b⋅(A−C) + (A−C)⋅(A−C) − r^2 = 0
  const auto ca = Vector3{ray.origin() - m_center};
  const auto delta_4 = std::pow(ray.direction().dot(ca), 2) - (ca.squaredNorm() - m_radius * m_radius);
  // if (delta_4 < 0) return false; // no intersection
  return delta_4 >= 0;
}

} // namespace raytracing
