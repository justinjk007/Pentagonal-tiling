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

# Boost config
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE( Boost 1.58 COMPONENTS unit_test_framework REQUIRED )
MESSAGE("-- Boost Library was found")
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

# CGAL config
# For linux CGAL to work also install package " libcgal-qt5-dev " as well
FIND_PACKAGE(CGAL REQUIRED)
MESSAGE("-- CGAL Library was found")
INCLUDE( ${CGAL_USE_FILE} )
INCLUDE( CGAL_CreateSingleSourceCGALProgram )
INCLUDE_DIRECTORIES ("${CGAL_ROOT}/include/CGAL")
INCLUDE_DIRECTORIES (BEFORE "../../include")

#Simple SVG library
ADD_LIBRARY(libSimpleSvg "")
INCLUDE(libSimpleSvg/CMakeLists.txt)
MESSAGE("-- Liniked svg library")

#DE config
ADD_LIBRARY(DE "")
INCLUDE(DE/CMakeLists.txt) # Include libs from subdir

ADD_EXECUTABLE(main main.cpp CalculateGap.cpp PrimitiveTile.cpp myGeometry.cpp boundaryDetection.cpp)
ADD_EXECUTABLE(run_tests run_tests.cpp CalculateGap.cpp PrimitiveTile.cpp myGeometry.cpp boundaryDetection.cpp)
ADD_EXECUTABLE(run_de run_de.cpp CalculateGap.cpp PrimitiveTile.cpp myGeometry.cpp boundaryDetection.cpp)
MESSAGE("-- All executables added")

TARGET_LINK_LIBRARIES (run_tests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
TARGET_LINK_LIBRARIES (run_de DE)
MESSAGE("-- All libraries connected")
