cmake_minimum_required(VERSION 3.10)
project(MINAMO CXX)

add_library(minamo SHARED src/count_log.cpp
                          src/draw_count.cpp
                          src/drawer.cpp
                          src/kernel.cpp
                          src/rgba_color.cpp
                          src/shader.cpp
                          src/rect/rect.cpp
                          src/rect/region.cpp
                          src/rect/color_drawer.cpp)
target_compile_features(minamo PUBLIC cxx_std_17)
target_compile_options(minamo PRIVATE -Wall)
target_include_directories(minamo PUBLIC include)

add_executable(test test2.cpp)
target_link_libraries(test minamo GL GLEW glfw)

install(TARGETS minamo LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
install(TARGETS test DESTINATION bin)
