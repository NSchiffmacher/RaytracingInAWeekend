#include <common.hpp>
#include <image.hpp>

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

    // Add items to the world
    auto world = Hittables{};
    world.add(std::make_unique<Sphere>(Point3{0, 0, -1}, 0.5));
    world.add(std::make_unique<Sphere>(Point3{0, -100.5, -1}, 100)); // "ground" as a sphere

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * aspect_ratio;
    auto focal_length = 1.0;

    auto origin = Point3{0., 0., 0.};
    auto horizontal = Vector3{viewport_width, 0., 0.};
    auto vertical = Vector3{0., viewport_height, 0.};
    auto lower_left_corner = Vector3{origin - horizontal / 2 - vertical / 2 - Vector3{0., 0., focal_length}};

    // Render
    std::cout << write_header(width, height) << "\n";
    std::cerr << "Start rending..." << std::endl;
    for (int j = height-1; j >= 0; --j)
    {
        std::cerr << fmt::format("[{:.2f}%] Rendering line {}/{}", (1-static_cast<double>(j)/(height-1)) * 100., height-j, height) << std::endl;
        for (int i = 0; i < width; ++i)
        {
            auto u = static_cast<double>(i) / (width-1);
            auto v = static_cast<double>(j) / (height-1);

            auto ray = Ray{origin, Vector3{lower_left_corner + u * horizontal + v * vertical - origin}};
            auto pixel_color = rayColor(ray, world);
            std::cout << pixel_color << "\n";
        }
    } 
    std::cout << std::flush;
    std::cerr << "Done rending !" << std::endl;
    return 0;
}

