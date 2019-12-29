cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (Debug or Release)" FORCE)
endif()

project(SpaceThing CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Irrlicht REQUIRED FATAL_ERROR)

set(SPACE_THING_SRC
  src/main.cpp
  src/Game.cpp)

set(VIDEO_DRIVER "OPENGL" CACHE STRING
  "Irrlicht video driver to use without the irr::video::EDT_ prefix.")

configure_file(include/config.hpp.in include/config.hpp @ONLY)

add_executable(SpaceThing "")
set_property(TARGET SpaceThing PROPERTY CXX_STANDARD 17)
target_sources(SpaceThing PRIVATE ${SPACE_THING_SRC})
target_link_libraries(SpaceThing PRIVATE
  ${IRRLICHT_LIBRARY})
target_include_directories(SpaceThing PRIVATE
  include/
  ${CMAKE_CURRENT_BINARY_DIR}/include/
  ${IRRLICHT_INCLUDE_DIR})
