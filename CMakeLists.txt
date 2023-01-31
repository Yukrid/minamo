cmake_minimum_required(VERSION 3.10)
project(MINAMO CXX)

#add_compile_definitions(MINAMO_CALLED_GL_FUNC_INFO)


add_library(minamo SHARED src/count_log.cpp
                          src/draw_count.cpp
                          src/kernel.cpp
                          src/shader.cpp
                          src/typewriter.cpp
                          src/system/scene.cpp)

target_compile_features(minamo PUBLIC cxx_std_17)
target_compile_options(minamo PUBLIC -Wall)
target_include_directories(minamo PUBLIC include)
target_link_libraries(minamo GL GLEW glfw freetype)

add_executable(text_sample text_sample.cpp)
target_link_libraries(text_sample minamo GL GLEW glfw freetype)

add_executable(scene_test scene_test.cpp)
target_link_libraries(scene_test minamo)

install(TARGETS minamo RUNTIME DESTINATION bin LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
#install(TARGETS text_sample DESTINATION bin)
