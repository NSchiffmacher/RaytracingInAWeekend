#pragma once

#include <vec3.hpp>

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

    inline Point3 at(double t) const { return m_origin + t * m_direction; };
    inline Point3 operator()(double t) const { return at(t); };

private:
    Point3 m_origin;
    Vector3 m_direction;
};


}
