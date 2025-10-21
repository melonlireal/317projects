cmake_minimum_required(VERSION 3.20)
project(boundaryvolumehierarchy)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# ---- libigl via FetchContent ----
include(FetchContent)

### libigl options: choose between header only and compiled static library
option(LIBIGL_USE_STATIC_LIBRARY      "Use libigl as static library" OFF)
option(LIBIGL_OPENGL                  "Use OpenGL"         ON)
option(LIBIGL_GLFW                    "Use GLFW"           ON)

FetchContent_Declare(
  libigl
  GIT_REPOSITORY https://github.com/libigl/libigl.git
  GIT_TAG        v2.6.0
)
FetchContent_MakeAvailable(libigl)

# Use Solution or Src files
option(USE_SOLUTION "Use solution files" OFF)
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
if(USE_SOLUTION)
  set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/solution")
endif()
file(GLOB SRCFILES CONFIGURE_DEPENDS "${SRC_DIR}/*.cpp")

# core library
add_library(core STATIC ${SRCFILES})
target_include_directories(core
  PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Add OpenGL/GLFW pieces only if enabled;
target_link_libraries(core PUBLIC igl::core)
if(LIBIGL_OPENGL)
  target_link_libraries(core PUBLIC igl::opengl)
endif()

if(LIBIGL_GLFW)
  target_link_libraries(core PUBLIC igl::glfw)
endif()

# Link executables to core library
add_executable(rays "rays.cpp")
target_link_libraries(rays PRIVATE core)

add_executable(distances "distances.cpp")
target_link_libraries(distances PRIVATE core)

add_executable(intersections "intersections.cpp")
target_link_libraries(intersections PRIVATE core)

# Warnings (nice for students)
if(MSVC)
  target_compile_options(core PRIVATE /W4 /permissive-)
else()
  target_compile_options(core PRIVATE -Wall -Wextra -Wpedantic)
endif()
