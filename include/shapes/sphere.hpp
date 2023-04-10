#pragma once

#include <vec3.hpp>
#include <shapes/shape.hpp>
#include <ray.hpp>
#include <hit_record.hpp>

#include <optional>

namespace raytracing
{

class Sphere: public Shape
{
public:
  inline Sphere(const Point3& center, double radius): m_center{center}, m_radius{radius} {}
  std::optional<HitRecord> hit(const Ray& ray, double t_min, double t_max) const override;

private:
  Point3 m_center;
  double m_radius;
};

} // namespace raytracing
