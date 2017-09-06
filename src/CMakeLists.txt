CMAKE_MINIMUM_REQUIRED (VERSION 3.5)
PROJECT (PentagonalTiling)

SET (CMAKE_CXX_STANDARD 11)

# The version number.
SET (Tutorial_VERSION_MAJOR 1)
SET (Tutorial_VERSION_MINOR 2)

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")

# Boost config
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE( Boost 1.58 COMPONENTS unit_test_framework REQUIRED )
MESSAGE("-- Boost Library was found")
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

# CGAL config
# For linux CGAL to work also install package- libcgal-qt5-dev
FIND_PACKAGE(CGAL REQUIRED)
MESSAGE("-- CGAL Library was found")
INCLUDE( ${CGAL_USE_FILE} )
INCLUDE( CGAL_CreateSingleSourceCGALProgram )
INCLUDE_DIRECTORIES ("${CGAL_ROOT}/include/CGAL")
INCLUDE_DIRECTORIES (BEFORE "../../include")

ADD_LIBRARY(boundaryDetection boundaryDetection.cpp)
ADD_LIBRARY(CalculateGap CalculateGap.cpp)
ADD_LIBRARY(PrimitiveTile PrimitiveTile.cpp)
ADD_LIBRARY(myGeometry myGeometry.cpp)
MESSAGE("-- All files linked")

ADD_EXECUTABLE(main main.cpp)
ADD_EXECUTABLE(run_tests run_tests.cpp)
MESSAGE("-- All executables added")

TARGET_LINK_LIBRARIES (main CalculateGap PrimitiveTile myGeometry boundaryDetection)
TARGET_LINK_LIBRARIES (run_tests CalculateGap PrimitiveTile myGeometry boundaryDetection ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
MESSAGE("-- All libraries connected")
