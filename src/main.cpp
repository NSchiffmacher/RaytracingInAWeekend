#include <common.hpp>
#include <image.hpp>
#include <camera.hpp>

#include <shapes/shape.hpp>
#include <shapes/sphere.hpp>

#include <limits>
#include <iostream>
#include <fmt/core.h>

using namespace raytracing; 

Color rayColor(const Ray& ray, const Hittables& world)
{
    // check if intersect sphere
    const auto intersection_record = world.hit(ray, 0., std::numeric_limits<double>::infinity());
    if (intersection_record.has_value())
    {
        const auto n = intersection_record->normal;
        return Color{0.5 * (n.x() + 1), 0.5 * (n.y() + 1), 0.5 * (n.z() + 1)};
    }

    // background
    auto t = 0.5 * (ray.dy() + 1.0);
    return (1.-t) * Color{1., 1., 1.} + t * Color{0.5, 0.7, 1.};
}

int main(){
    // Image
    const auto aspect_ratio = 16./9.;
    const auto width = 400;  
    const auto height = static_cast<int>(width / aspect_ratio);
    const auto samples_per_pixel = 100;

    // Add items to the world
    auto world = Hittables{};
    world.add(std::make_unique<Sphere>(Point3{0, 0, -1}, 0.5));
    world.add(std::make_unique<Sphere>(Point3{0, -100.5, -1}, 100)); // "ground" as a sphere

    // Camera
    const auto viewport_height = 2.;
    const auto focal_length = 1.;
    auto camera = Camera{viewport_height * aspect_ratio, viewport_height, focal_length};

    // Render
    std::cout << write_header(width, height) << "\n";
    std::cerr << "Start rending..." << std::endl;
    for (int j = height-1; j >= 0; --j)
    {
        std::cerr << fmt::format("[{:.2f}%] Rendering line {}/{}", (1-static_cast<double>(j)/(height-1)) * 100., height-j, height) << std::endl;
        for (int i = 0; i < width; ++i)
        {
            auto pixel_color = ColorAccumulator(samples_per_pixel);
            for (int s = 0; s < samples_per_pixel; s++)
            {
                auto u = (static_cast<double>(i) + random_double()) / (width-1);
                auto v = (static_cast<double>(j) + random_double()) / (height-1);

                auto ray = camera.getRay(u, v);
                pixel_color += rayColor(ray, world);
            }
            std::cout << pixel_color << "\n";
        }
    } 
    std::cout << std::flush;
    std::cerr << "Done rending !" << std::endl;
    return 0;
}

