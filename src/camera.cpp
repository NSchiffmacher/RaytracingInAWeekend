#include <camera.hpp>
#include <math.h>

namespace raytracing
{

Camera::Camera() : Camera({0., 0., 0.}, {0., 0., -1.}, {0., 1., 0.}, M_PI / 2., 16. / 9., 1.)
{
}
Camera::Camera(Point3 look_from, Point3 look_at, Vector3 v_up, double vertical_fov, double aspect_ratio, double focal_length)
{
  const auto h = tan(vertical_fov / 2.) * 1.;
  const auto viewport_height = 2 * h; 
  const auto viewport_width = aspect_ratio * viewport_height; 

  const auto w = Vector3{look_at - look_from}.normalized();
  const auto v = Vector3{v_up - v_up.dot(w) * w}.normalized();
  const auto u = Vector3{w.cross(v)};

  // std::cerr << "w: (" << w.x() << ", " << w.y() << ", " << w.z() << ")" << std::endl;
  // std::cerr << "v: (" << v.x() << ", " << v.y() << ", " << v.z() << ")" << std::endl;
  // std::cerr << "u: (" << u.x() << ", " << u.y() << ", " << u.z() << ")" << std::endl;

  m_origin = Point3{look_from};
  m_horizontal = Vector3{viewport_width * u};
  m_vertical = Vector3{viewport_height * v};
  m_lower_left_corner = Vector3{m_origin - m_horizontal / 2 - m_vertical / 2 + focal_length * w};

  // std::cerr << "m_origin: (" << m_origin.x() << ", " << m_origin.y() << ", " << m_origin.z() << ")" << std::endl;
  // std::cerr << "m_horizontal: (" << m_horizontal.x() << ", " << m_horizontal.y() << ", " << m_horizontal.z() << ")" << std::endl;
  // std::cerr << "m_vertical: (" << m_vertical.x() << ", " << m_vertical.y() << ", " << m_vertical.z() << ")" << std::endl;
  // std::cerr << "m_lower_left_corner: (" << m_lower_left_corner.x() << ", " << m_lower_left_corner.y() << ", " << m_lower_left_corner.z() << ")" << std::endl;
}

Ray Camera::getRay(double s, double t) const
{
  return Ray{m_origin, m_lower_left_corner + s * m_horizontal + t * m_vertical - m_origin};
}

} // namespace raytracing
