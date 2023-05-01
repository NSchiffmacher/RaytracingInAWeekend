#pragma once

#include <materials/material.hpp>
#include <color.hpp>
#include <cmath>

namespace raytracing
{

class Dielectric: public Material
{
public:
  inline Dielectric(double refraction_index): m_refraction_index{refraction_index} {}
  
  // returns Ray scattered_ray, Color attenuation
  inline std::optional<std::pair<Ray, Color>> scatter(const Ray& incident_ray, const HitRecord& hit_record) const
  {
    // if outside the sphere, we go from air to inside, else reversed
    auto refraction_ratio = hit_record.front_face ? (1./m_refraction_index) : m_refraction_index;
    
    auto cos_theta = fmin(-incident_ray.direction().dot(hit_record.normal), 1.0);
    auto sin_theta = sqrt(1. - cos_theta * cos_theta);
    auto direction = refraction_ratio * sin_theta > 1. || reflectance(cos_theta, refraction_ratio) > random_double() ? 
        reflect(incident_ray.direction(), hit_record.normal) : // must reflect
        refract(incident_ray.direction(), hit_record.normal, refraction_ratio); // can refract
        
    return std::make_pair(Ray{hit_record.point, direction}, Color{1.,1.,1.});
  }
private:
  double m_refraction_index;
  inline static double reflectance(double cosine, double ref_idx) {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
  }
};

} // namespace raytracing
