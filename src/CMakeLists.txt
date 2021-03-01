include_directories(../include)

add_executable(visual_sort
        ./main.cpp
        ./animation_base.cpp
        template_instantiation/sequence_generator.inst.cpp
        template_instantiation/sorting_algorithm.inst.cpp
        template_instantiation/vector.inst.cpp
)

if (VISUAL_SORT_ENABLE_BOOST_SORT_SUPPORT)
    target_compile_definitions(visual_sort PRIVATE BOOST_SORT_SUPPORT=1)
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    target_compile_options(visual_sort PRIVATE -fopenmp)
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        target_compile_options(visual_sort PRIVATE -flto)
    endif ()
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/fopenmp)
endif ()

