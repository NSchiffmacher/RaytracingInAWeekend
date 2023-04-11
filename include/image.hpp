#pragma once

#include <iostream>
#include <color.hpp>

namespace raytracing
{

struct write_header
{
  int width;
  int height;

  write_header(int width, int height): width{width}, height{height} {};
};
std::ostream& operator<<(std::ostream& out, write_header header);
std::ostream& operator<<(std::ostream& out, Color pixel_color);
std::ostream& operator<<(std::ostream& out, ColorAccumulator pixel_color);
std::ostream& write_color(std::ostream& out, Color pixel_color);
std::ostream& write_color(std::ostream& out, Color pixel_color, int samples_per_pixel);

}
