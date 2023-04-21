#pragma once

#include <materials/material.hpp>
#include <color.hpp>

namespace raytracing
{

class Metal: public Material
{
public:
  inline Metal(const Color& albedo, double fuzz = 0.): m_albedo{albedo}, m_fuzz{fuzz} {}
  
  // returns Ray scattered_ray, Color attenuation
  inline std::optional<std::pair<Ray, Color>> scatter(const Ray& incident_ray, const HitRecord& hit_record) const
  {
    const auto reflected = reflect(incident_ray.direction(), hit_record.normal);
    if (reflected.dot(hit_record.normal) <= 0)
      return std::nullopt;
    return std::make_pair(Ray{hit_record.point, reflected + m_fuzz * random_in_unit_sphere()}, m_albedo);
  }
private:
  Color m_albedo;
  double m_fuzz;
};

} // namespace raytracing
