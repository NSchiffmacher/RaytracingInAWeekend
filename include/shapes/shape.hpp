#pragma once

#include <vec3.hpp>
#include <hit_record.hpp>
#include <optional>
#include <memory>
#include <vector>

namespace raytracing
{

class Ray;

class Shape
{
public:
  virtual std::optional<HitRecord> hit(const Ray& ray, double t_min, double t_max) const = 0;
  virtual ~Shape() = default;
};

class Hittables
{
public:
  inline Hittables(): m_objects{} {}
  inline Hittables(std::unique_ptr<Shape>&& shape): m_objects{} { add(std::move(shape)); }

  inline void add(std::unique_ptr<Shape>&& shape) { m_objects.push_back(std::move(shape)); }
  std::optional<HitRecord> hit(const Ray& ray, double t_min, double t_max) const;
  

private:
  std::vector<std::unique_ptr<Shape>> m_objects;
};

} // namespace raytracing
