#include <hit_record.hpp>
#include <ray.hpp>
#include <materials/material.hpp>

// #include <iostream>

namespace raytracing
{

HitRecord::HitRecord(double t, const Point3& point, const Ray& ray, const Vector3& normal, bool front_face, Material* mat): t{t}, point{point}, normal{normal}, front_face{front_face}, material{mat}
{
}

} // namespace raytracing
