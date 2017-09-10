CMAKE_MINIMUM_REQUIRED (VERSION 3.5)
PROJECT (PentagonalTiling)

SET (CMAKE_CXX_STANDARD 11)

# The version number.
SET (VERSION_MAJOR 2)
SET (VERSION_MINOR 0)

CONFIGURE_FILE (
  "${PROJECT_SOURCE_DIR}/Config.h.in"
  "${PROJECT_BINARY_DIR}/Config.h"
  )

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}") # This is done to include Config.h

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

#DE config
ADD_LIBRARY(DE "") # Include libs from subdir
INCLUDE(DE/CMakeLists.txt) # Include libs from subdir

ADD_LIBRARY(boundaryDetection boundaryDetection.cpp)
ADD_LIBRARY(CalculateGap CalculateGap.cpp)
ADD_LIBRARY(PrimitiveTile PrimitiveTile.cpp)
ADD_LIBRARY(myGeometry myGeometry.cpp)
MESSAGE("-- All files linked")

ADD_EXECUTABLE(main main.cpp)
ADD_EXECUTABLE(run_tests run_tests.cpp)
ADD_EXECUTABLE(run_de run_de.cpp)
MESSAGE("-- All executables added")

TARGET_LINK_LIBRARIES (run_tests CalculateGap PrimitiveTile myGeometry boundaryDetection ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
TARGET_LINK_LIBRARIES (main CalculateGap PrimitiveTile myGeometry boundaryDetection)
TARGET_LINK_LIBRARIES (run_de CalculateGap PrimitiveTile myGeometry boundaryDetection DE)
MESSAGE("-- All libraries connected")
