#pragma once

#include <vec3.hpp>
#include <hit_record.hpp>
#include <optional>

namespace raytracing
{

class Ray;

class Shape
{
public:
  virtual std::optional<HitRecord> hit(const Ray& ray, double t_min, double t_max) const = 0;
  virtual ~Shape() = default;
};

} // namespace raytracing
