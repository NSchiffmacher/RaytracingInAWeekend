#include <ray.hpp>
#include <vec3.hpp>

#include <gtest/gtest.h>
#include <cmath>
#include <iostream>

namespace raytracing
{

void compare(const Point3& lhs, const Point3& rhs, double margin=1e-15)
{
    EXPECT_NEAR(lhs.x(), rhs.x(), margin);
    EXPECT_NEAR(lhs.y(), rhs.y(), margin);
    EXPECT_NEAR(lhs.z(), rhs.z(), margin);
}

TEST(RayTest, Constructors) {
    auto ray = Ray{}; 
    EXPECT_NEAR(ray.x(), 0., 1e-15);
    EXPECT_NEAR(ray.y(), 0., 1e-15);
    EXPECT_NEAR(ray.z(), 0., 1e-15);
    EXPECT_NEAR(ray.dx(), 0., 1e-15);
    EXPECT_NEAR(ray.dy(), 0., 1e-15);
    EXPECT_NEAR(ray.dz(), 0., 1e-15);
    compare(ray.origin(), {});
    compare(ray.direction(), {});

    ray = Ray{{1., 2., 3.}, {4., 5., 6.}}; 
    const auto norm = std::sqrt(4*4 + 5*5 + 6*6);
    EXPECT_NEAR(ray.x(), 1., 1e-15);
    EXPECT_NEAR(ray.y(), 2., 1e-15);
    EXPECT_NEAR(ray.z(), 3., 1e-15);
    EXPECT_NEAR(ray.dx(), 4. / norm, 1e-15);
    EXPECT_NEAR(ray.dy(), 5. / norm, 1e-15);
    EXPECT_NEAR(ray.dz(), 6. / norm, 1e-15);
    compare(ray.origin(), {1., 2., 3.});
    compare(ray.direction(), {4. / norm, 5. / norm, 6. / norm});
}

void test_at(double x, double y, double z, double dx, double dy, double dz, double t)
{
    auto ray = Ray{{x, y, z}, {dx, dy, dz}};
    const auto norm = std::sqrt(dx*dx + dy*dy + dz*dz);
    auto p = ray.at(t);
    compare(p, {
        x + t * dx / norm,
        y + t * dy / norm,
        z + t * dz / norm
    }, 1e-15);
    auto pp = ray(t);
    compare(pp, {
        x + t * dx / norm,
        y + t * dy / norm,
        z + t * dz / norm
    }, 1e-15);
}

TEST(RayTest, At)
{
    test_at(1., 2., 3., 4., 5., 6., 1.);
    test_at(1., 2., 3., 4., 5., 6., 4.);
    test_at(1., 2., 3., 4., 5., 6., 10.);
    test_at(-1., 2., 3., 4., 5., 6., 1.);
    test_at(1., 2., 3., -4., 5., -6., 4.);
    test_at(1., 2., -3., 4., 5., 6., 10.);
}




} // namespace raytracing
