#include <common.hpp>
#include <image.hpp>
#include <camera.hpp>

#include <shapes/shape.hpp>
#include <shapes/sphere.hpp>

#include <materials/lambertian.hpp>
#include <materials/dielectric.hpp>
#include <materials/metal.hpp>

#include <limits>
#include <memory>
#include <iostream>
#include <fmt/core.h>
#include <math.h>

using namespace raytracing; 



int main(){
    // Image (Semi-HD -> width = 1600 => random_scale = 0.5 => samples_per_pixel = 10)
    const auto aspect_ratio = 16./9.;
    const auto width = 1600;  
    const auto height = static_cast<int>(width / aspect_ratio);
    const auto samples_per_pixel = 50; //100;
    const auto max_depth = 50; //100;
    const auto random_scale = 1.;
    const auto lambertian_diffuse_scatter_type = Lambertian::DiffuseScatterType::RandomUnit;

    // Debug 
    const auto freq_info_print = 50;

    // Camera
    const auto vertical_fov = 20. * M_PI / 180.;
    const auto look_from = Point3{13., 2., 3.};
    const auto look_at = Point3{0., 0., 0.};
    const auto v_up = Point3{0., 1., 0.};
    const auto aperture = 0.1;
    const auto focus_dist = (look_from - Point3{0., 1., 0.}).norm();

    // Add user items to the world
    auto world = Hittables{};

    const auto ground_material = std::make_shared<Lambertian>(Color{0.5, 0.5, 0.5});
    world.add(std::make_unique<Sphere>(Point3(0,-1000,0), 1000, ground_material));

    const auto mat1 = std::make_shared<Dielectric>(1.5);
    const auto mat2 = std::make_shared<Lambertian>(Color{0.4, 0.2, 0.1});
    const auto mat3 = std::make_shared<Metal>(Color{0.7, 0.6, 0.5}, 0.);

    world.add(std::make_unique<Sphere>(Point3{0., 1., 0.}, 1., mat1));
    world.add(std::make_unique<Sphere>(Point3{-4., 1., 0.}, 1., mat2));
    world.add(std::make_unique<Sphere>(Point3{4., 1., 0.}, 1., mat3));

    for (int a = -2; a < 2; ++a)
    {
        for (int b = -2; b < 2; ++b)
        {
            const auto choose_mat = random_double();
            const auto center = Point3{a + 0.9 * random_double(), 0.2, b + 0.9 * random_double()};

            if ((center - Point3{4., 0.2, 0.}).norm() > 0.9)
            {
                std::shared_ptr<Material> sphere_mat = nullptr;
                if (choose_mat < 0.8)
                {
                    const auto albedo = Color::random() * Color::random();
                    sphere_mat = std::make_shared<Lambertian>(albedo);
                } 
                else if (choose_mat < 0.95)
                {
                    const auto albedo = Color::random(0.5);
                    const auto fuzz = random_double(0., 0.5);
                    sphere_mat = std::make_shared<Metal>(albedo, fuzz);
                }
                else
                {
                    sphere_mat = std::make_shared<Dielectric>(1.5);
                }
                world.add(std::make_unique<Sphere>(center, 0.2, sphere_mat));
            }
        }
    }

    // Camera
    auto camera = Camera{look_from, look_at, v_up, vertical_fov, aspect_ratio, aperture, focus_dist};

    // Render
    auto image = Image{width, height, max_depth, samples_per_pixel, random_scale, true, freq_info_print};
    image.render(camera, world);

    // Write image
    image.writePNGImage("img.png");    
    // image.writePPMImage("img.ppm");    
    return 0;
}

