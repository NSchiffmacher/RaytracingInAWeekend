#pragma once

#include <iostream>
// #include <vec3.hpp>
#include <Eigen/Dense>

namespace raytracing
{

class Color
{
public:
    inline Color(double r, double g, double b, double a): m_color{r, g, b, a} { clampValues(); };
    inline Color(double r, double g, double b): Color{r, g, b, 0.} {};
    inline Color(double c): Color{c, c, c, 0.} {};
    inline Color(): Color {0., 0., 0., 0.} {};
    inline Color(const Eigen::Matrix<double, 4, 1>& color): Color{color[0], color[1], color[2], color[3]} {};

    inline const Color& clampValues(){
        m_color = m_color.cwiseMin(1.).cwiseMax(0.);
        return *this;
    };

    inline Color operator+(const Color& other) const { return Color{m_color + other.m_color}; };
    inline Color& operator+=(const Color& other) { m_color += other.m_color; clampValues(); return *this; };
    inline Color operator*(double constant) const { return Color{m_color * constant}; };
    inline Color& operator*=(double constant) { m_color*= constant; clampValues(); return *this; };
    inline Color operator/(double constant) const { return *this * (1/constant); };
    inline Color& operator/=(double constant) { *this = *this / constant; return *this; };

    // getters and setters
    inline double& r() { return m_color[0]; };
    inline double& g() { return m_color[1]; };
    inline double& b() { return m_color[2]; };
    inline double& a() { return m_color[3]; };

    inline double r() const { return m_color[0]; };
    inline double g() const { return m_color[1]; };
    inline double b() const { return m_color[2]; };
    inline double a() const { return m_color[3]; };

    friend std::ostream& operator<<(std::ostream& out, Color pixel_color);
private:
    Eigen::Matrix<double, 4, 1> m_color;
};

inline Color operator*(double constant, const Color& color)
{
    return (color * constant).clampValues();
}
} // namespace raytracing
