cmake_minimum_required(VERSION 3.15)
project(visual_sort CXX)

set(CMAKE_CXX_STANDARD 20)


# To configure whether enable kerbal::sort library support
find_package(Boost)
message(STATUS "Boost_FOUND: ${Boost_FOUND}")
set(VISUAL_SORT_ENABLE_BOOST_SORT_SUPPORT ${Boost_FOUND})
message(STATUS "VISUAL_SORT_ENABLE_BOOST_SORT_SUPPORT: ${VISUAL_SORT_ENABLE_BOOST_SORT_SUPPORT}")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/Zc:__cplusplus)
endif ()


# To configure whether enable gfx::timsort library support
if (EXISTS "./cpp-TimSort/include/gfx/")
    set(GFX_TIMSORT_FOUND TRUE)
else ()
    set(GFX_TIMSORT_FOUND FALSE)
endif ()
message(STATUS "GFX_TIMSORT_FOUND: ${GFX_TIMSORT_FOUND}")
set(VISUAL_SORT_ENABLE_GFX_TIMSORT_SUPPORT ${GFX_TIMSORT_FOUND})
message(STATUS "VISUAL_SORT_ENABLE_GFX_TIMSORT_SUPPORT: ${VISUAL_SORT_ENABLE_GFX_TIMSORT_SUPPORT}")

include_directories(./cpp-TimSort/include)

include_directories(~/git/Kerbal/include)


add_subdirectory(./include)
add_subdirectory(./src)


message("compiler: ${CMAKE_CXX_COMPILER_ID}")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_link_libraries(visual_sort nana)
    target_link_libraries(visual_sort Xcursor)
    target_link_libraries(visual_sort pthread)
    target_link_libraries(visual_sort omp)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    include_directories(C:/Users/Peter/include)
    include_directories(C:/Users/Peter/git/Kerbal/include)
    link_directories(C:/Users/Peter/lib_vs)
    target_link_libraries(visual_sort C:/Users/Peter/lib_vs/nana_v142_Release_x64.lib)
endif ()