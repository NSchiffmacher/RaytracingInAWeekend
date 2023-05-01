#pragma once

#include <common.hpp>
#include <color.hpp>
#include <ray.hpp>

#include <optional>
#include <utility>

namespace raytracing
{

struct HitRecord;

class Material
{
public:
  // returns Ray scattered_ray, Color attenuation
  virtual std::optional<std::pair<Ray, Color>> scatter(const Ray& incident_ray, const HitRecord& hit_record) const = 0;
};

} // namespace raytracing
