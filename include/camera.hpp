#pragma once

#include <ray.hpp>
#include <vec3.hpp>

namespace raytracing
{

class Camera
{
public:
  Camera();

  // vertical_fox in radians
  Camera(Point3 look_from, Point3 look_at, Vector3 v_up, double vertical_fov, double aspect_ratio, double aperture, double focus_dist);

  Ray getRay(double s, double t) const;

private:
  Point3 m_origin;
  Point3 m_lower_left_corner;
  Vector3 m_horizontal;
  Vector3 m_vertical;
  double m_lens_radius;
  Vector3 m_u, m_v, m_w;
};

} // namespace raytracing
