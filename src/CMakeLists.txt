CMAKE_MINIMUM_REQUIRED (VERSION 3.5)
PROJECT (PentagonalTiling)

SET (CMAKE_CXX_STANDARD 11)

# The version number.
SET (VERSION_MAJOR 2)
SET (VERSION_MINOR 0)

# Project Configuration Settings
FILE(
  WRITE ${PROJECT_BINARY_DIR}/Config.h.in
  "#define VERSION_MAJOR @VERSION_MAJOR@\n"
  "#define VERSION_MINOR @VERSION_MINOR@"
  )
CONFIGURE_FILE (
  "${PROJECT_BINARY_DIR}/Config.h.in"
  "${PROJECT_BINARY_DIR}/Config.h"
  )

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}") # This is done to include Config.h

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/plot_lines.py
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/plot_lines.py
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
MESSAGE("-- Copied python script for plotting")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../img/favicon.ico
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../img/favicon.ico
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
MESSAGE("-- Copied ICON file")

# Boost config
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE( Boost 1.54 COMPONENTS unit_test_framework REQUIRED )
MESSAGE("-- Boost Library was found")
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

# CGAL config
# For linux CGAL to work also install package " libcgal-qt5-dev " as well
FIND_PACKAGE(CGAL REQUIRED)
MESSAGE("-- CGAL Library was found")
# INCLUDE( ${CGAL_USE_FILE} )
# INCLUDE( CGAL_CreateSingleSourceCGALProgram )
# INCLUDE_DIRECTORIES ("${CGAL_ROOT}/include/CGAL")
# INCLUDE_DIRECTORIES (BEFORE "../../include")

# Qt config
find_package(Qt5 COMPONENTS Widgets Charts REQUIRED) # Rest of the modules will be automatically added
MESSAGE("-- Qt5 Library was found")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_BINARY_DIR ON)

# Add files into one variable, seperate them into frontend and backend...cause
SET(BACKEND CalculateGap.cpp PrimitiveTile.cpp myGeometry.cpp boundaryDetection.cpp)
SET(FRONTEND mainwindow.cpp pentagonGen.cpp tilingGen.cpp)
SET(DE lshade.cc search_algorithm.cc)

ADD_EXECUTABLE(main main.cpp ${BACKEND})
ADD_EXECUTABLE(run_tests run_tests.cpp ${BACKEND})
ADD_EXECUTABLE(run_de run_de.cpp ${BACKEND} ${DE})
ADD_EXECUTABLE(run_gui run_gui.cpp ${BACKEND} ${DE} ${FRONTEND})
MESSAGE("-- All executables added")

TARGET_LINK_LIBRARIES (main Qt5::Widgets Qt5::Charts CGAL::CGAL)
TARGET_LINK_LIBRARIES (run_tests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} Qt5::Widgets Qt5::Charts CGAL::CGAL)
TARGET_LINK_LIBRARIES (run_de Qt5::Widgets Qt5::Charts CGAL::CGAL)
TARGET_LINK_LIBRARIES (run_gui Qt5::Widgets Qt5::Charts CGAL::CGAL)
MESSAGE("-- All libraries connected")
