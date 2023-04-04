#include <iostream>
#include <fmt/core.h>

#include <color.hpp>
// #include <vec3.hpp>

using namespace raytracing;

int main(){
    const int width = 256;  
    const int height = 256;

    std::cout << "P3\n" << width << " " << height << "\n255\n";

    std::cerr << "Starting..." << std::endl;
    for (int y = height - 1; y >= 0; --y){
        for (int x = 0; x < width; ++x) {
            const auto c = Color{
                static_cast<double>(x) / (width),
                static_cast<double>(y) / (height),
                0.25
            };
            
            std::cout << 256. * c << std::endl;
        }
    }  
    std::cerr << fmt::format("Wrote {} pixels", width*height) << std::endl;
}
