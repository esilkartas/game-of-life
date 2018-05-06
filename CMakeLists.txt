cmake_minimum_required(VERSION 3.10)
project(game_of_life)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(game_of_life main.cpp game_area.cpp game_area.h game_app.cpp game_app.h game_app_window.cpp game_app_window.h)

target_link_libraries(${CMAKE_PROJECT_NAME} ${GTKMM_LIBRARIES})