#pragma once

#include <common.hpp>

namespace raytracing
{

class Camera
{
public:
  Camera();

  // vertical_fox in radians
  Camera(Point3 look_from, Point3 look_at, Vector3 v_up, double vertical_fov, double aspect_ratio, double focal_length);

  Ray getRay(double s, double t) const;

private:
  Point3 m_origin;
  Point3 m_lower_left_corner;
  Vector3 m_horizontal;
  Vector3 m_vertical;
};

} // namespace raytracing
