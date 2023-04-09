#pragma once

#include <vec3.hpp>
#include <shapes/shape.hpp>
#include <ray.hpp>

namespace raytracing
{

class Sphere: public Shape
{
public:
  inline Sphere(const Point3& center, double radius): m_center{center}, m_radius{radius} {}
  bool intersectRay(const Ray& ray) const;

private:
  Point3 m_center;
  double m_radius;
};

} // namespace raytracing
