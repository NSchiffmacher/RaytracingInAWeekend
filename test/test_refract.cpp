#include <ray.hpp>
#include <vec3.hpp>
#include <ray.hpp>
#include <materials/lambertian.hpp>
#include <shapes/sphere.hpp>

#include <gtest/gtest.h>
#include <cmath>
#include <iostream>

namespace raytracing
{

void compare(const Point3& lhs, const Point3& rhs, double margin=1e-10)
{
    EXPECT_NEAR(lhs.x(), rhs.x(), margin);
    EXPECT_NEAR(lhs.y(), rhs.y(), margin);
    EXPECT_NEAR(lhs.z(), rhs.z(), margin);
}

TEST(NormalTest, OutsideSphere) {
    auto lambertian_mat = std::make_unique<Lambertian>(Color{1., 1., 1.}, Lambertian::DiffuseScatterType::NoRandom);
    auto world = Hittables{};
    world.add(std::make_unique<Sphere>(Point3{0., 0., -2.}, 1., lambertian_mat.get()));

    auto ray = Ray{Point3{0., 0., 0.}, Vector3{0., 0., -2}};
    compare(ray.direction(), Vector3{0., 0., -1.0});

    auto hit = world.hit(ray, 0.001, std::numeric_limits<double>::infinity());
    if (!hit.has_value()) std::cout << "No hit" << std::endl;
    else {
        std::cout << "t             = " << hit->t << std::endl;
        std::cout << "point         = " << hit->point << std::endl;
        std::cout << "normal        = " << hit->normal << std::endl;
        std::cout << "front_face    = " << hit->front_face << std::endl;
    }

    EXPECT_EQ(hit.has_value(), true);
    EXPECT_EQ(hit->t, 1.);
    compare(hit->point, Vector3{0., 0., -1.}, 1e-10);
    compare(hit->normal, Vector3{0., 0., 1.}, 1e-10);
    EXPECT_EQ(hit->front_face, true); // outside the sphere
}

TEST(NormalTest, OutsideSphere2) {
    auto lambertian_mat = std::make_unique<Lambertian>(Color{1., 1., 1.}, Lambertian::DiffuseScatterType::NoRandom);
    auto world = Hittables{};
    world.add(std::make_unique<Sphere>(Point3{0., 0., -2.}, 1., lambertian_mat.get()));

    auto ray = Ray{Point3{0., 1., 0.}, Vector3{0., 0., -2}};
    compare(ray.direction(), Vector3{0., 0., -1.0}, 1e-10);

    auto hit = world.hit(ray, 0.001, std::numeric_limits<double>::infinity());
    if (!hit.has_value()) std::cout << "No hit" << std::endl;
    else {
        std::cout << "t             = " << hit->t << std::endl;
        std::cout << "point         = " << hit->point << std::endl;
        std::cout << "normal        = " << hit->normal << std::endl;
        std::cout << "front_face    = " << hit->front_face << std::endl;
    }

    EXPECT_EQ(hit.has_value(), true);
    EXPECT_EQ(hit->t, 2.);
    compare(hit->point, Vector3{0., 1., -2.}, 1e-10);
    compare(hit->normal, Vector3{0., 1., 0.}, 1e-10);
    EXPECT_EQ(hit->front_face, true); // outside the sphere
}

TEST(NormalTest, InsideSphere) {
    auto lambertian_mat = std::make_unique<Lambertian>(Color{1., 1., 1.}, Lambertian::DiffuseScatterType::NoRandom);
    auto world = Hittables{};
    world.add(std::make_unique<Sphere>(Point3{0., 0., 0.}, 1., lambertian_mat.get()));

    auto ray = Ray{Point3{0., 0., 0.}, Vector3{0., 0., -2}};
    compare(ray.direction(), Vector3{0., 0., -1.0}, 1e-10);

    auto hit = world.hit(ray, 0.001, std::numeric_limits<double>::infinity());
    if (!hit.has_value()) std::cout << "No hit" << std::endl;
    else {
        std::cout << "t             = " << hit->t << std::endl;
        std::cout << "point         = " << hit->point << std::endl;
        std::cout << "normal        = " << hit->normal << std::endl;
        std::cout << "front_face    = " << hit->front_face << std::endl;
    }

    EXPECT_EQ(hit.has_value(), true);
    EXPECT_EQ(hit->t, 1.);
    compare(hit->point, Vector3{0., 0., -1.}, 1e-10);
    compare(hit->normal, Vector3{0., 0., 1.}, 1e-10);
    EXPECT_EQ(hit->front_face, false); // inside the sphere
}


} // namespace raytracing
