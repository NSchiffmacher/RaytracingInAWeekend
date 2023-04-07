#include <image.hpp>

namespace raytracing
{

std::ostream& operator<<(std::ostream& out, write_header header)
{
  return out << "P3" << std::endl << header.width << " " << header.height << std::endl << 255;
}

std::ostream& write_color(std::ostream& out, Color pixel_color)
{
  return out << static_cast<int>(pixel_color.r() * 255) << " " << static_cast<int>(pixel_color.g() * 255) << " " << static_cast<int>(pixel_color.b() * 255);
}
std::ostream& operator<<(std::ostream& out, Color pixel_color)
{
  return write_color(out, pixel_color);
}

}
