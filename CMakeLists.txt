cmake_minimum_required(VERSION 3.15)
project(visual_sort)

set(CMAKE_CXX_STANDARD 17)

add_executable(visual_sort src/main.cpp)
target_link_libraries(visual_sort -lnana)
target_link_libraries(visual_sort -lXcursor)
target_link_libraries(visual_sort -lpthread)