#include <hit_record.hpp>
#include <ray.hpp>

namespace raytracing
{

HitRecord::HitRecord(double t, const Point3& point, const Ray& ray, const Vector3& outward_normal): t{t}, point{point}
{
  front_face = ray.direction().dot(outward_normal);
  normal = front_face ? outward_normal : - outward_normal;
}

} // namespace raytracing
