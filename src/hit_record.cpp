#include <hit_record.hpp>
#include <ray.hpp>

namespace raytracing
{

const HitRecord& HitRecord::setFaceNormal(const Ray& ray, const Vector3& outward_normal)
{
  front_face = ray.direction().dot(outward_normal);
  normal = front_face ? outward_normal : - outward_normal;
  return *this;
}

} // namespace raytracing
