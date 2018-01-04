CMAKE_MINIMUM_REQUIRED (VERSION 3.5)
PROJECT (PentagonalTiling)

set(CMAKE_CXX_STANDARD 11)

# The version number.
set(VERSION_MAJOR 2)
set(VERSION_MINOR 0)

# Project Configuration Settings
file(
  WRITE ${PROJECT_BINARY_DIR}/Config.h.in
  "#define VERSION_MAJOR @VERSION_MAJOR@\n"
  "#define VERSION_MINOR @VERSION_MINOR@"
  )
configure_file (
  "${PROJECT_BINARY_DIR}/Config.h.in"
  "${PROJECT_BINARY_DIR}/Config.h"
  )
include_directories("${PROJECT_BINARY_DIR}") # This is done to include Config.h

# Move resource files to directories where the executable can find it
# This is the python script that was used for visual debugging in the
# earlier versions of the program this being kept until the C++ gui is
# usable
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/plot_lines.py
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/plot_lines.py
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
message("-- Copied python script for plotting")

# This is the icon file used to represent the program temporary way to
# make things pretty before resources can be managed correctly
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../img/favicon.ico
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../img/favicon.ico
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
message("-- Copied ICON file")

# Set compiler specific options
# if (MSVC)
#   add_compile_options(/MP /Gm-)
#   # else()
#   #   add_compile_options(-Wall -Wextra -Wpedantic)
# endif()

# Boost config
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package( Boost 1.54 COMPONENTS unit_test_framework REQUIRED )
message("-- Boost Library was found")
include_directories( ${Boost_INCLUDE_DIR} )

# CGAL config
find_package(CGAL REQUIRED)
message("-- CGAL Library was found")

# Qt config
find_package(Qt5 COMPONENTS Widgets Charts REQUIRED) # Rest of the modules will be automatically added
message("-- Qt5 Library was found")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_BINARY_DIR ON)

# Add files into one variable, seperate them into frontend and backend...cause
set(BACKEND CalculateGap.cpp PrimitiveTile.cpp myGeometry.cpp boundaryDetection.cpp)
set(FRONTEND mainwindow.cpp pentagonGen.cpp tilingGen.cpp)
set(DE lshade.cc search_algorithm.cc)

add_executable(main main.cpp ${BACKEND})
add_executable(run_tests run_tests.cpp ${BACKEND})
add_executable(run_de run_de.cpp ${BACKEND} ${DE})
add_executable(run_gui run_gui.cpp ${BACKEND} ${DE} ${FRONTEND})
message("-- All executables added")

target_link_libraries(main Qt5::Widgets Qt5::Charts CGAL::CGAL)
target_link_libraries(run_tests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} Qt5::Widgets Qt5::Charts CGAL::CGAL)
target_link_libraries(run_de Qt5::Widgets Qt5::Charts CGAL::CGAL)
target_link_libraries(run_gui Qt5::Widgets Qt5::Charts CGAL::CGAL)
message("-- All libraries connected")
