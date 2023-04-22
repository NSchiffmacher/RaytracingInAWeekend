#include <common.hpp>
#include <image.hpp>
#include <camera.hpp>

#include <shapes/shape.hpp>
#include <shapes/sphere.hpp>

#include <materials/lambertian.hpp>
#include <materials/diaelectric.hpp>
#include <materials/metal.hpp>

#include <limits>
#include <chrono>
#include <memory>
#include <iostream>
#include <fmt/core.h>

using namespace raytracing; 


Color rayColor(const Ray& ray, const Hittables& world, int depth)
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

int main(){
    // Image (Semi-HD -> width = 1600 => random_scale = 0.5 => samples_per_pixel = 10)
    const auto aspect_ratio = 16./9.;
    const auto width = 400;  
    const auto height = static_cast<int>(width / aspect_ratio);
    const auto samples_per_pixel = 100; //100;
    const auto max_depth = 100; //100;
    const auto random_scale = 1.;
    const auto lambertian_diffuse_scatter_type = Lambertian::DiffuseScatterType::RandomUnit;
    // Debug 
    const auto freq_info_print = 50;

    // Create the materials
    auto material_ground = std::make_unique<Lambertian>(Color{0.8, 0.8, 0.}, lambertian_diffuse_scatter_type);
    auto material_center = std::make_unique<Lambertian>(Color{0.1, 0.2, 0.5});
    auto material_left = std::make_unique<Diaelectric>(2.5);
    auto material_right = std::make_unique<Metal>(Color{0.8, 0.6, 0.2}, 0.);

    // Add items to the world
    auto world = Hittables{};
    world.add(std::make_unique<Sphere>(Point3{0, 0, -1}, 0.5, material_center.get()));
    world.add(std::make_unique<Sphere>(Point3{1, 0, -1}, 0.5, material_right.get()));
    world.add(std::make_unique<Sphere>(Point3{-1, 0, -1}, 0.5, material_left.get()));
    world.add(std::make_unique<Sphere>(Point3{-1, 0, -1}, 0.4, material_left.get()));
    world.add(std::make_unique<Sphere>(Point3{0, -100.5, -1}, 100, material_ground.get())); // "ground" as a sphere

    // Camera
    const auto viewport_height = 2.;
    const auto focal_length = 1.;
    auto camera = Camera{viewport_height * aspect_ratio, viewport_height, focal_length};

    // Render
    auto render_start = std::chrono::high_resolution_clock::now();
    std::cout << write_header(width, height) << "\n";
    std::cerr << "Start rending..." << std::endl;
    for (int j = height-1; j >= 0; --j)
    {
        if (j % freq_info_print == 0) fmt::print(stderr, "[{:.2f}%] Rendering line {}/{}\n", (1-static_cast<double>(j)/(height-1)) * 100., height-j, height);
        for (int i = 0; i < width; ++i)
        {
            auto pixel_color = ColorAccumulator(samples_per_pixel);
            for (int s = 0; s < samples_per_pixel; s++)
            {
                auto u = (static_cast<double>(i) + random_double() * random_scale) / (width-1);
                auto v = (static_cast<double>(j) + random_double() * random_scale) / (height-1);

                auto ray = camera.getRay(u, v);
                pixel_color += rayColor(ray, world, max_depth);
            }
            std::cout << pixel_color << "\n";
        }
    } 
    std::cout << std::flush;
    auto render_end = std::chrono::high_resolution_clock::now();
    std::cerr << "Done rending !" << std::endl;
    fmt::print(stderr, "Render took {:.3f} seconds.\n", std::chrono::duration_cast<std::chrono::milliseconds>(render_end - render_start).count() / 1000.);
    return 0;
}

