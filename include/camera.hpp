#pragma once

#include <common.hpp>

namespace raytracing
{

class Camera
{
public:
  Camera();
  Camera(double viewport_width, double viewport_height, double focal_length);

  Ray getRay(double u, double v) const;

private:
  Point3 m_origin;
  Point3 m_lower_left_corner;
  Vector3 m_horizontal;
  Vector3 m_vertical;
};

} // namespace raytracing
