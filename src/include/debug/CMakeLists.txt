# target_sources(ray_tracer PUBLIC debug.hpp ProgressBar.cpp ProgressBar.hpp)
# target_include_directories(ray_tracer PUBLIC ${CMAKE_CURRENT_LIST_DIR})
set(debug_source_files debug.hpp debug.cpp ProgressBar.hpp ProgressBar.cpp)
add_library(MyDebug ${debug_source_files})