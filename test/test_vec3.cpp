#include <vec3.hpp>

#include <gtest/gtest.h>
#include <cmath>
#include <iostream>

namespace raytracing
{

TEST(Vector3Test, EmptyConstructors) {
    Vector3 v{};
    EXPECT_EQ(v.x(), 0.);
    EXPECT_EQ(v.y(), 0.);
    EXPECT_EQ(v.z(), 0.);
}

TEST(Vector3Test, FullConstructor) {
    Vector3 v{1,2,3};
    EXPECT_EQ(v.x(), 1.);
    EXPECT_EQ(v.y(), 2.);
    EXPECT_EQ(v.z(), 3.);
    EXPECT_EQ(v[0], 1.);
    EXPECT_EQ(v[1], 2.);
    EXPECT_EQ(v[2], 3.);
}

TEST(Vector3Test, NegativeOperator) {
    Vector3 v = -Vector3{1,2,3};
    EXPECT_EQ(v.x(), -1.);
    EXPECT_EQ(v.y(), -2.);
    EXPECT_EQ(v.z(), -3.);
}

TEST(Vector3Test, AddOperator) {
    Vector3 a{1., 2., 3.};
    Vector3 b{4., 5., 6.};
    Vector3 c = a + b;

    EXPECT_EQ(c.x(), 5.);
    EXPECT_EQ(c.y(), 7.);
    EXPECT_EQ(c.z(), 9.);
}

TEST(Vector3Test, AddIPOperator) {
    Vector3 a{1., 2., 3.};
    Vector3 b{4., 5., 6.};
    
    a += b;

    EXPECT_EQ(a.x(), 5.);
    EXPECT_EQ(a.y(), 7.);
    EXPECT_EQ(a.z(), 9.);
}

TEST(Vector3Test, MultOperator) {
    Vector3 a{1., 2., 3.};
    Vector3 b{4., 5., 6.};
    Vector3 c = a * b;

    EXPECT_EQ(c.x(), 4.);
    EXPECT_EQ(c.y(), 10.);
    EXPECT_EQ(c.z(), 18.);
}

TEST(Vector3Test, MultOperatorConstant) {
    Vector3 a{1., 2., 3.};
    Vector3 b = a * 2.;

    EXPECT_EQ(b.x(), 2.);
    EXPECT_EQ(b.y(), 4.);
    EXPECT_EQ(b.z(), 6.);

    Vector3 c = 2. * a;
    EXPECT_EQ(c.x(), 2.);
    EXPECT_EQ(c.y(), 4.);
    EXPECT_EQ(c.z(), 6.);
}

TEST(Vector3Test, AddOperatorConstant) {
    Vector3 a{1., 2., 3.};
    Vector3 b = a + 2.;

    EXPECT_EQ(b.x(), 3.);
    EXPECT_EQ(b.y(), 4.);
    EXPECT_EQ(b.z(), 5.);

    Vector3 c = 2. + a;
    EXPECT_EQ(c.x(), 3.);
    EXPECT_EQ(c.y(), 4.);
    EXPECT_EQ(c.z(), 5.);
}

TEST(Vector3Test, DivOperatorConstant) {
    Vector3 a{1., 2., 3.};
    Vector3 b = 6. / a;

    EXPECT_EQ(b.x(), 6.);
    EXPECT_EQ(b.y(), 3.);
    EXPECT_EQ(b.z(), 2.);

    Vector3 c = a / 6.;
    EXPECT_EQ(c.x(), 1./6.);
    EXPECT_EQ(c.y(), 2./6.);
    EXPECT_EQ(c.z(), 3./6.);
}

TEST(Vector3Test, MultIPOperator) {
    Vector3 a{1., 2., 3.};
    Vector3 b{4., 5., 6.};
    
    a *= b;

    EXPECT_EQ(a.x(), 4.);
    EXPECT_EQ(a.y(), 10.);
    EXPECT_EQ(a.z(), 18.);
}

TEST(Vector3Test, TestLengthSqr) {
    Vector3 a{1,1,1};
    EXPECT_EQ(a.normSquared(), 3.);

    Vector3 b{2,2,2};
    EXPECT_EQ(b.normSquared(), 12.);
}

TEST(Vector3Test, TestLength) {
    Vector3 a{1,1,1};
    EXPECT_EQ(a.norm(), std::sqrt(3.));

    Vector3 b{2,2,2};
    EXPECT_EQ(b.norm(), std::sqrt(12.));
}

TEST(Vector3Test, Normalize) {
    Vector3 a{1,1,1};
    Vector3 b = a.normalize();
    EXPECT_EQ(b.norm(), 1.);
    EXPECT_EQ(b.z(), 1./std::sqrt(3));
    EXPECT_EQ(b.x(), 1./std::sqrt(3));
    EXPECT_EQ(b.y(), 1./std::sqrt(3));
}

} // namespace raytracing
