CMAKE_MINIMUM_REQUIRED (VERSION 3.5)
PROJECT (PentagonalTiling)

set(CMAKE_CXX_STANDARD 11)

# The version number.
set(VER_MAJOR 3)
set(VER_MINOR 0)

set(CMAKE_BUILD_TYPE Debug) # Defualt built type
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Get compilation database if available

# Project Configuration Settings
file(
  WRITE ${PROJECT_BINARY_DIR}/Config.h.in
  "const int VER_MAJOR = @VER_MAJOR@;"
  " const int VER_MINOR = @VER_MINOR@;"
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
if (MSVC)
  file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/scripts/plot_lines.py
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
endif(MSVC)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/scripts/plot_lines.py
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
message("-- Copied python script for plotting")

# This is the icon file used to represent the program temporary way to
# make things pretty before resources can be managed correctly
if (MSVC)
  file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/img/favicon.ico
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
endif(MSVC)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/img/favicon.ico
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
message("-- Copied ICON file")

# Set compiler specific options
if (MSVC)
  add_compile_options(/MP /Gm- /W3)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif(MSVC)

# Boost config
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package( Boost COMPONENTS unit_test_framework REQUIRED )
message("-- Boost Library was found")
include_directories( ${Boost_INCLUDE_DIR} )

# CGAL config
find_package(CGAL REQUIRED)
message("-- CGAL Library was found")
include( ${CGAL_USE_FILE} )
include( CGAL_CreateSingleSourceCGALProgram )

# Qt config
find_package(Qt5 COMPONENTS Widgets Charts REQUIRED) # Rest of the modules will be automatically added
message("-- Qt5 Library was found")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_BINARY_DIR ON)

# Add files into one variable, seperate them into frontend and backend...cause
set(BACKEND src/CalculateGap.cpp src/PrimitiveTile.cpp src/myGeometry.cpp src/boundaryDetection.cpp)
set(FRONTEND src/mainwindow.cpp src/pentagonGen.cpp src/tilingGen.cpp src/Worker.cpp src/mainwindow.ui)
set(DE src/lshade.cc src/search_algorithm.cc)

add_executable(run_tests test/run_tests.cpp ${BACKEND})
add_executable(run_gui src/run_gui.cpp ${BACKEND} ${DE} ${FRONTEND})
message("-- All executables added")

target_link_libraries(run_tests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} Qt5::Widgets Qt5::Charts CGAL::CGAL)
target_link_libraries(run_gui Qt5::Widgets Qt5::Charts CGAL::CGAL)
message("-- All libraries connected")

# This is done so that the auto-generated header file by Qt's GUI
# system can find all the widget header files which exist in the
# directory i'm including.
target_include_directories(run_gui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(run_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
