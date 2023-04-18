#pragma once

#include <vec3.hpp>
#include <shapes/shape.hpp>
#include <hit_record.hpp>
#include <optional>
#include <limits>

namespace raytracing
{

class Ray
{
public:
    inline Ray(): m_origin{}, m_direction{} {};
    inline Ray(const Point3& origin, const Vector3& direction): m_origin{origin}, m_direction{direction.normalized()} {};

    inline const Point3& origin() const { return m_origin; };
    inline const Vector3& direction() const { return m_direction; };

    inline double x() const { return m_origin.x(); };
    inline double y() const { return m_origin.y(); };
    inline double z() const { return m_origin.z(); };
    inline double dx() const { return m_direction.x(); };
    inline double dy() const { return m_direction.y(); };
    inline double dz() const { return m_direction.z(); };

    inline std::optional<HitRecord> hit(const Shape& shape, double t_min, double t_max) const { return shape.hit(*this, t_min, t_max); }

    inline Point3 at(double t) const { 
        return Point3{m_origin + (t + std::numeric_limits<double>::epsilon() * 10) * m_direction}; // can't make it work without the epsilon ??
    }
    inline Point3 operator()(double t) const { return at(t); }

private:
    Point3 m_origin;
    Vector3 m_direction;
};


}
