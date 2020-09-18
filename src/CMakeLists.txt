include_directories(../include)
add_executable(visual_sort
        ./main.cpp
        ./animation_base.cpp
        template_instantiation/sequence_generator.inst.cpp
        template_instantiation/sorting_algorithm.inst.cpp
        template_instantiation/vector.inst.cpp
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fopenmp")
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto")
    endif()
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")
endif()

message(STATUS "CXX flags: ${CMAKE_CXX_FLAGS}")
