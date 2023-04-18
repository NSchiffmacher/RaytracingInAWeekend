include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        b796f7d44681514f58a683a3a71ff17c94edb0c1 # release-1.10.0
)
FetchContent_MakeAvailable(googletest)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(test_color test_color.cpp ../src/color.cpp)
target_link_libraries(test_color gtest_main)
add_test(NAME test_color COMMAND test_color)

add_executable(test_ray test_ray.cpp)
target_link_libraries(test_ray gtest_main)
add_test(NAME test_ray COMMAND test_ray)

add_executable(test_vec3 test_vec3.cpp ../src/vec3.cpp)
target_link_libraries(test_vec3 gtest_main)
add_test(NAME test_vec3 COMMAND test_vec3)

