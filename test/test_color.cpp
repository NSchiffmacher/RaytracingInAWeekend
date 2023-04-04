#include <color.hpp>

#include <gtest/gtest.h>
#include <cmath>
#include <iostream>

namespace raytracing
{

TEST(ColorTest, Constructors) {
    auto c = Color{}; 
    EXPECT_EQ(c.r(), 0./255.);
    EXPECT_EQ(c.g(), 0./255.);
    EXPECT_EQ(c.b(), 0./255.);
    EXPECT_EQ(c.a(), 0./255.);

    c = Color{100./255., 125./255., 150./255., 250./255.};
    EXPECT_EQ(c.r(), 100./255.);
    EXPECT_EQ(c.g(), 125./255.);
    EXPECT_EQ(c.b(), 150./255.);
    EXPECT_EQ(c.a(), 250./255.);

    c = Color{100./255., 125./255., 150./255.};
    EXPECT_EQ(c.r(), 100./255.);
    EXPECT_EQ(c.g(), 125./255.);
    EXPECT_EQ(c.b(), 150./255.);
    EXPECT_EQ(c.a(), 0./255.);

    c = Color{25./255.};
    EXPECT_EQ(c.r(), 25./255.);
    EXPECT_EQ(c.g(), 25./255.);
    EXPECT_EQ(c.b(), 25./255.);
    EXPECT_EQ(c.a(), 0./255.);
}

TEST(ColorTest, ClampValuesInConstructor)
{
    auto c = Color{-25./255., 15./255., 278./255., 1999999999./255.};
    EXPECT_EQ(c.r(), 0./255.);
    EXPECT_EQ(c.g(), 15./255.);
    EXPECT_EQ(c.b(), 255./255.);
    EXPECT_EQ(c.a(), 255./255.);
}

TEST(ColorTest, MultiplyConstant)
{
    auto color = Color{25./255., 50./255., 90./255.};
    color *= 4.;
    EXPECT_EQ(color.r(), 100./255.);
    EXPECT_EQ(color.g(), 200./255.);
    EXPECT_EQ(color.b(), 255./255.);
    EXPECT_EQ(color.a(), 0./255.);

    color = Color{25./255., 50./255., 90./255.};
    auto new_color = color * 4.;
    EXPECT_EQ(new_color.r(), 100./255.);
    EXPECT_EQ(new_color.g(), 200./255.);
    EXPECT_EQ(new_color.b(), 255./255.);
    EXPECT_EQ(new_color.a(), 0./255.);
    EXPECT_EQ(color.r(), 25./255.);
    EXPECT_EQ(color.g(), 50./255.);
    EXPECT_EQ(color.b(), 90./255.);
    EXPECT_EQ(color.a(), 0./255.);

    color = Color{25./255., 50./255., 90./255.};
    new_color = 4. * color;
    EXPECT_EQ(new_color.r(), 100./255.);
    EXPECT_EQ(new_color.g(), 200./255.);
    EXPECT_EQ(new_color.b(), 255./255.);
    EXPECT_EQ(new_color.a(), 0./255.);
    EXPECT_EQ(color.r(), 25./255.);
    EXPECT_EQ(color.g(), 50./255.);
    EXPECT_EQ(color.b(), 90./255.);
    EXPECT_EQ(color.a(), 0./255.);
}



} // namespace raytracing
