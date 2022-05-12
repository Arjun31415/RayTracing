# add_library(include Player.cpp)
add_subdirectory(debug)
target_sources(ray_tracer PUBLIC Player.hpp Player.cpp)
target_include_directories(ray_tracer PUBLIC ${CMAKE_CURRENT_LIST_DIR})

