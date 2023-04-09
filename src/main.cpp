#include <iostream>
#include <fmt/core.h>

#include <color.hpp>
#include <ray.hpp>
#include <image.hpp>
#include <vec3.hpp>

#include <shapes/sphere.hpp>

using namespace raytracing;

Color rayColor(const Ray& ray, const Sphere& sphere)
{
    // check if intersect sphere
    if (sphere.intersectRay(ray))
        return Color{1, 0, 0};

    // background
    auto t = 0.5 * (ray.dy() + 1.0);
    return (1.-t) * Color{1., 1., 1.} + t * Color{0.5, 0.7, 1.};
}

int main(){
    // Image
    const auto aspect_ratio = 16./9.;
    const auto width = 400;  
    const auto height = static_cast<int>(width / aspect_ratio);

    const auto sphere = Sphere{Point3{0, 0, -1}, 0.5};

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
            auto pixel_color = rayColor(ray, sphere);
            std::cout << pixel_color << "\n";
        }
    } 
    std::cout << std::flush;
    std::cerr << "Done rending !" << std::endl;
}
