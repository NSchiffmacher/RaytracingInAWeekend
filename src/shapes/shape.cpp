#include <shapes/shape.hpp>

namespace raytracing
{
  
std::optional<HitRecord> Hittables::hit(const Ray& ray, double t_min, double t_max) const
{
  auto record = std::optional<HitRecord>{std::nullopt};
  auto clothest_so_far = t_max;

  for(const auto& object: m_objects)
  {
    auto tmp_rec = object->hit(ray, t_min, clothest_so_far);
    if (tmp_rec.has_value())
    {
      record = tmp_rec;
      clothest_so_far = tmp_rec->t;
    }
  }

  return record;
}

} // namespace raytracing
