#include <image.hpp>
#include <cmath>

namespace raytracing
{

std::ostream& operator<<(std::ostream& out, write_header header)
{
  return out << "P3" << std::endl << header.width << " " << header.height << std::endl << 255;
}

std::ostream& operator<<(std::ostream& out, Color pixel_color)
{
  return write_color(out, pixel_color);
}

std::ostream& operator<<(std::ostream& out, ColorAccumulator pixel_color)
{
  return write_color(out, pixel_color / pixel_color.numSamples());
}


std::ostream& write_color(std::ostream& out, Color pixel_color)
{
  // using gamma correction of 1/2
  return out << static_cast<int>(std::sqrt(pixel_color.r()) * 255.) << " " 
             << static_cast<int>(std::sqrt(pixel_color.g()) * 255.) << " "
             << static_cast<int>(std::sqrt(pixel_color.b()) * 255.);
}

// std::ostream& write_color(std::ostream& out, Color pixel_color, int samples_per_pixel)
// {
//   auto scale = 255. / samples_per_pixel;
//   return out << static_cast<int>(pixel_color.r() * scale) << " " << static_cast<int>(pixel_color.g() * scale) << " " << static_cast<int>(pixel_color.b() * scale);
// }
}
