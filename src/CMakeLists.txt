 cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
 set(CMAKE_C_COMPILER    "/usr/bin/gcc")
 set(CMAKE_CXX_COMPILER  "/usr/bin/g++")
 project(ray_tracer)
 set (CMAKE_CXX_STANDARD 20)
 set(CMAKE_CXX_STANDARD_REQUIRED ON)
 set(SFML_USE_STATIC_STD_LIBS TRUE)
 set (SOURCE_FILES main.cpp)

 macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()
# Add SFML
 find_package(SFML 2.5.1 COMPONENTS system graphics audio network window REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable (ray_tracer ${SOURCE_FILES})
# My libraries
add_subdirectory(include)
target_link_libraries(ray_tracer sfml-graphics sfml-audio sfml-window includes)
