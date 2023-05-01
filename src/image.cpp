#include <materials/material.hpp>
#include <image.hpp>

#include <cmath>
#include <fmt/core.h>
#include <fstream>

#include <lodepng.h>

namespace raytracing
{

Color Image::rayColor(const Ray& ray, const Hittables& world, int depth)
{
    const auto min_t = 0.001; // hits with a value of t being less than this value are ignored
    // if I understand it correctly, it helps get rid of ray colliding with the object they reflect out of
    if (depth <= 0) return Color{0., 0., 0.};
    // check if intersect sphere
    const auto intersection_record = world.hit(ray, min_t, std::numeric_limits<double>::infinity());
    if (intersection_record.has_value())
    {
        auto scatter_res = intersection_record->material->scatter(ray, intersection_record.value());
        if (scatter_res.has_value())
            return scatter_res->second * rayColor(scatter_res->first, world, depth - 1);
        else 
            return Color{0., 0., 0.}; // no light reflected        
    }

    // background
    auto t = 0.5 * (ray.dy() + 1.0);
    return (1.-t) * Color{1., 1., 1.} + t * Color{0.5, 0.7, 1.};
}

Image::Image(int width, int height, int depth, int samples_per_pixel, double random_scale, bool debug_print, int freq_info_print):
  m_pixel_data{},
  m_width{width}, m_height{height}, m_depth{depth}, m_samples_per_pixel{samples_per_pixel},
  m_random_scale{random_scale}, m_debug_print{debug_print}, m_freq_info_print{freq_info_print}
{
  m_pixel_data.reserve(m_width * m_height);
}
void Image::render(const Camera& camera, const Hittables& world)
{
  auto render_start = std::chrono::high_resolution_clock::now();
  // std::cout << write_header(m_width, m_height) << "\n";
  if (m_debug_print) std::cerr << "Start rending..." << std::endl;
  for (int j = 0; j < m_height; ++j)
  {
    if (m_debug_print && j % m_freq_info_print == 0) fmt::print(stderr, "[{:.2f}%] Rendering line {}/{}\n", (static_cast<double>(j)/(m_height-1)) * 100., j, m_height);
    for (int i = 0; i < m_width; ++i)
    {
      auto pixel_color = ColorAccumulator(m_samples_per_pixel);
      for (int s = 0; s < m_samples_per_pixel; s++)
      {
        auto u = (static_cast<double>(i) + random_double() * m_random_scale) / (m_width-1);
        auto v = (static_cast<double>(j) + random_double() * m_random_scale) / (m_height-1);

        auto ray = camera.getRay(u, v);
        pixel_color += rayColor(ray, world, m_depth);
      }
      m_pixel_data.push_back(pixel_color);
    }
  } 
  auto render_end = std::chrono::high_resolution_clock::now();
  if (m_debug_print) std::cerr << "Done rending !" << std::endl;
  if (m_debug_print) fmt::print(stderr, "Render took {:.3f} seconds.\n", std::chrono::duration_cast<std::chrono::milliseconds>(render_end - render_start).count() / 1000.);
}

void Image::coutPPMImage()
{
  if (m_debug_print) std::cerr << "Start writting PPM image to std::cout..." << std::endl;
  auto write_start = std::chrono::high_resolution_clock::now();
  
  std::cout << write_header(m_width, m_height) << "\n";
  for (int y = m_height - 1; y >= 0; --y)
  {
    for (int x = 0; x < m_width; ++x)
    {
      std::cout << m_pixel_data.at(y * m_width + x) << "\n";
    }
  }
  std::cout << std::flush;
  
  auto write_end = std::chrono::high_resolution_clock::now();
  if (m_debug_print) std::cerr << "Done writting to std::cout !" << std::endl;
  if (m_debug_print) fmt::print(stderr, "Writting PPM Image took {:.3f} seconds.\n", std::chrono::duration_cast<std::chrono::milliseconds>(write_end - write_start).count() / 1000.);
}

void Image::writePPMImage(const std::string& filename)
{
  if (m_debug_print) std::cerr << "Start writting PPM image to file..." << std::endl;
  auto write_start = std::chrono::high_resolution_clock::now();

  std::ofstream file;
  file.open(filename);
  
  file << write_header(m_width, m_height) << "\n";
  for (int y = m_height - 1; y >= 0; --y)
  {
    for (int x = 0; x < m_width; ++x)
    {
      file << m_pixel_data.at(y * m_width + x) << "\n";
    }
  }
  file << std::flush;
  file.close();
  
  auto write_end = std::chrono::high_resolution_clock::now();
  if (m_debug_print) fmt::print(stderr, "Done writting to {} !\n", filename);
  if (m_debug_print) fmt::print(stderr, "Writting PPM Image took {:.3f} seconds.\n", std::chrono::duration_cast<std::chrono::milliseconds>(write_end - write_start).count() / 1000.);
}

void Image::writePNGImage(const std::string& filename)
{
  if (m_debug_print) std::cerr << "Start writting PNG image to file..." << std::endl;
  auto write_start = std::chrono::high_resolution_clock::now();

  auto image = std::vector<unsigned char>{};
  image.reserve(m_width * m_height * 4);
  
  // file << write_header(m_width, m_height) << "\n";
  for (int y = m_height - 1; y >= 0; --y)
  {
    for (int x = 0; x < m_width; ++x)
    {
      auto color = m_pixel_data.at(y * m_width + x);
      color /= color.numSamples();
      image.push_back(static_cast<unsigned char>(std::sqrt(color.r()) * 255.));
      image.push_back(static_cast<unsigned char>(std::sqrt(color.g()) * 255.));
      image.push_back(static_cast<unsigned char>(std::sqrt(color.b()) * 255.));
      image.push_back(static_cast<unsigned char>(std::sqrt(color.a()) * 255.));
    }
  }
  if (m_debug_print) std::cerr << "Done writting intermedite matrix..." << std::endl;
  
  //Encode the image
  unsigned error = lodepng::encode(filename, image, m_width, m_height);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
  
  auto write_end = std::chrono::high_resolution_clock::now();
  if (m_debug_print) fmt::print(stderr, "Done writting to {} !\n", filename);
  if (m_debug_print) fmt::print(stderr, "Writting PNG Image took {:.3f} seconds.\n", std::chrono::duration_cast<std::chrono::milliseconds>(write_end - write_start).count() / 1000.);
}

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
