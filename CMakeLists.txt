cmake_minimum_required(VERSION 3.12)
project(brakeza)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${brakeza_SOURCE_DIR}/cmake-build-debug")

set(SDL2_dir /Library/Frameworks/SDL2.framework/Headers)
set(SDL2_image_dir /Library/Frameworks/SDL2_image.framework/Headers)
set(SDL2_ttf_dir /Library/Frameworks/SDL2_ttf.framework/Headers)
set(OpenGL_dir /Library/Frameworks/OpenGL.framework/Headers/)

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${SDL2_dir} ${SDL2_image_dir} ${SDL2_ttf_dir} ${OPENGL_INCLUDE_DIRS})

add_executable(brakeza main.cpp suzanne_vertices.h)

target_link_libraries(brakeza ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${SDLTTF_LIBRARY} ${OPENGL_LIBRARIES})