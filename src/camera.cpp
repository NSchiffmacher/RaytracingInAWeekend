#include <camera.hpp>

namespace raytracing
{

Camera::Camera() : Camera(16./9 * 2., 2., 1.)
{
}
Camera::Camera(double viewport_width, double viewport_height, double focal_length)
{
  m_origin = Point3{0., 0., 0.};
  m_horizontal = Vector3{viewport_width, 0., 0.};
  m_vertical = Vector3{0., viewport_height, 0.};
  m_lower_left_corner = Vector3{m_origin - m_horizontal / 2 - m_vertical / 2 - Vector3{0., 0., focal_length}};
}

Ray Camera::getRay(double u, double v) const
{
  return Ray{m_origin, m_lower_left_corner + u * m_horizontal + v * m_vertical - m_origin};
}

} // namespace raytracing
