#include <shapes/sphere.hpp>
#include <cmath>

namespace raytracing
{

std::optional<HitRecord> Sphere::hit(const Ray& ray, double t_min, double t_max) const 
{
  // t^2 * b⋅b + 2t b⋅(A−C) + (A−C)⋅(A−C) − r^2 = 0
  const auto ca = Vector3{ray.origin() - m_center};
  const auto b_2 = ray.direction().dot(ca);
  const auto delta_4 = std::pow(b_2, 2) - (ca.squaredNorm() - m_radius * m_radius);
  if (delta_4 < 0) return std::nullopt; // no intersection

  // const auto t = std::clamp(- b_2 - std::sqrt(delta_4), t_min, t_max);
  auto t = - b_2 - std::sqrt(delta_4);
  if (t < t_min || t_max < t)
  {
    t = - b_2 + std::sqrt(delta_4);
    if (t < t_min || t_max < t)
      return std::nullopt;
  }

  const auto p = ray(t);
  const auto n = Vector3{(p - m_center) / m_radius};
  return HitRecord{t, p, ray, n, m_material};
}

} // namespace raytracing
