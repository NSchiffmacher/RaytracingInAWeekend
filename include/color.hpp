#pragma once

#include <iostream>
// #include <vec3.hpp>
#include <Eigen/Dense>

namespace raytracing
{

class Color
{
public:
    inline Color(double r, double g, double b, double a): m_color{r, g, b, a}, m_min{0.}, m_max{1.} { clampValues(); };
    inline Color(double r, double g, double b): Color{r, g, b, 0.} {};
    inline Color(double c): Color{c, c, c, 0.} {};
    inline Color(): Color {0., 0., 0., 0.} {};
    inline Color(const Eigen::Matrix<double, 4, 1>& color): Color{color[0], color[1], color[2], color[3]} {};

    inline static Color CustomRangeColor(double min, double max)
    {
        auto c = Color{};
        c.m_min = min;
        c.m_max = max;
        return c;
    }
    inline static Color CustomRangeColor(double max) { return CustomRangeColor(0., max); }

    inline const Color& clampValues(){
        m_color = m_color.cwiseMin(m_max).cwiseMax(m_min);
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
protected:
    Eigen::Matrix<double, 4, 1> m_color;
    double m_min;
    double m_max;
};

class ColorAccumulator: public Color
{
public:
    inline ColorAccumulator(int num_samples): Color(), m_samples{num_samples} { m_min = 0.; m_max = static_cast<double>(m_samples); }

    inline int numSamples(){ return m_samples; }
private:
    int m_samples;
};

inline Color operator*(double constant, const Color& color)
{
    return (color * constant).clampValues();
}
} // namespace raytracing
