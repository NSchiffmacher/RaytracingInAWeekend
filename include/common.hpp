#pragma once

#include <math.h>
#include <vec3.hpp>
// #include <color.hpp>

inline double random_double() 
{
  return rand() / (RAND_MAX + 1.);
}

inline double random_double(double min, double max)
{
  return random_double() * (max - min) + min;
}

inline raytracing::Vector3 random_vec3()
{
  return raytracing::Vector3{random_double(), random_double(), random_double()};
}

inline raytracing::Vector3 random_vec3(double min, double max)
{
  return raytracing::Vector3{random_double(min, max), random_double(min, max), random_double(min, max)};
}

inline raytracing::Vector3 random_in_unit_sphere() // TODO change method obv
{
  while (true)
  {
    auto p = random_vec3();
    if (p.squaredNorm() >= 1) continue;
    return p;
  }
}

inline raytracing::Vector3 random_in_unit_disk() // TODO change method obv
{
  while (true)
  {
    auto p = raytracing::Vector3{random_double(-1., 1.), random_double(-1., 1.), 0.};
    if (p.squaredNorm() >= 1) continue;
    return p;
  }
}

inline raytracing::Vector3 random_unit_vector()
{
  return random_in_unit_sphere().normalized();
}

inline raytracing::Vector3 random_in_hemisphere(const raytracing::Vector3& normal)
{
  raytracing::Vector3 in_unit_sphere = random_in_unit_sphere();
  if (in_unit_sphere.dot(normal) > 0.)  
    return in_unit_sphere; 
  return - in_unit_sphere; 
}

// #include <random>
// inline double random_double() {
//     static std::uniform_real_distribution<double> distribution(0.0, 1.0);
//     static std::mt19937 generator;
//     return distribution(generator);
// }
