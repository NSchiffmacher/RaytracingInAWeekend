#pragma once

#include <vec3.hpp>
// #include <hit_record.hpp>
#include <optional>

namespace raytracing
{

class Ray;
class Material;

struct HitRecord
{
  double t;
  Point3 point;
  Vector3 normal;
  bool front_face;
  Material* material;

  HitRecord(double t, const Point3& point, const Ray& ray, const Vector3& normal, bool front_face, Material* mat);
};

} // namespace raytracing
