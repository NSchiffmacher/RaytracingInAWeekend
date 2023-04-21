#pragma once

#include <materials/material.hpp>
#include <color.hpp>

namespace raytracing
{

class Lambertian: public Material
{
public:
  enum class DiffuseScatterType { RandomHemisphere, RandomUnit, RandomSphere };

  inline Lambertian(const Color& albedo, DiffuseScatterType scatter_type = DiffuseScatterType::RandomUnit): m_albedo{albedo}, m_scatter_type{scatter_type} {}
  
  // returns Ray scattered_ray, Color attenuation
  inline std::optional<std::pair<Ray, Color>> scatter(const Ray& incident_ray, const HitRecord& hit_record) const
  {
    auto scatter_direction = Vector3{hit_record.normal + 
      (m_scatter_type == DiffuseScatterType::RandomUnit ? random_unit_vector() :
       m_scatter_type == DiffuseScatterType::RandomSphere ? random_in_unit_sphere() : 
       /* m_scatter_type == DiffuseScatterType::RandomHemisphere ? */ random_in_hemisphere(hit_record.normal))};
    if (near_zero(scatter_direction)) // if the direction is near zero, set it back to the normal (might lead to NaN or Inf later otherwise)
      scatter_direction = hit_record.normal;
    return std::make_pair(Ray{hit_record.point, scatter_direction}, m_albedo);
  }
private:
  Color m_albedo;
  DiffuseScatterType m_scatter_type;
};

} // namespace raytracing
