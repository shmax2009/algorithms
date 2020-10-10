cmake_minimum_required(VERSION 3.17)
project(algorithms)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(algorithms main.cpp)
target_link_libraries(algorithms sfml-graphics sfml-audio)
