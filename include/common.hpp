#pragma once

#include <ray.hpp>
#include <vec3.hpp>
#include <color.hpp>

inline double random_double() 
{
  return rand() / (RAND_MAX + 1.);
}

inline double random_double(double min, double max)
{
  return random_double() * (max - min) + min;
}

// #include <random>
// inline double random_double() {
//     static std::uniform_real_distribution<double> distribution(0.0, 1.0);
//     static std::mt19937 generator;
//     return distribution(generator);
// }
