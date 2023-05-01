#pragma once

#include <ray.hpp>
#include <shapes/shape.hpp>
#include <camera.hpp>
#include <color.hpp>

#include <iostream>
#include <string>
#include <chrono>
#include <optional>

namespace raytracing
{

class Image
{
public:
  Image(int width, int height, int depth, int samples_per_pixel, double random_scale, bool debug_print, int freq_info_print);
  Image(const Image&) = delete;

  Color rayColor(const Ray& ray, const Hittables& world, int depth);
  void render(const Camera& camera, const Hittables& world);

  void coutPPMImage();
  void writePPMImage(const std::string& filename);
  void writePNGImage(const std::string& filename);
private:
  std::vector<ColorAccumulator> m_pixel_data; // row by row ie. pixel (x, y) is [y * m_width + x]

  int m_width;
  int m_height;
  int m_depth;
  int m_samples_per_pixel;
  double m_random_scale;
  bool m_debug_print;
  int m_freq_info_print;
};

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
// std::ostream& write_color(std::ostream& out, Color pixel_color, int samples_per_pixel);

}
