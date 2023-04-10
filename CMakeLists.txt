cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(Raycasting)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package(fmt REQUIRED)
link_libraries(fmt::fmt)
link_libraries(Eigen3::Eigen)

include_directories(include/)

add_subdirectory(src)
add_subdirectory(test)
