cmake_minimum_required(VERSION 3.15)
project(visual_sort CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(./cpp-TimSort/include)

add_subdirectory(./include)
add_subdirectory(./src)


message("compiler: ${CMAKE_CXX_COMPILER_ID}")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_link_libraries(visual_sort -lnana)
    target_link_libraries(visual_sort -lXcursor)
    target_link_libraries(visual_sort -lpthread)
    target_link_libraries(visual_sort -lomp)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    include_directories(C:/Users/Peter/include)
    include_directories(C:/Users/Peter/git/Kerbal/include)
    link_directories(C:/Users/Peter/lib_vs)
    target_link_libraries(visual_sort nana_v142_Release_x64.lib)
endif()