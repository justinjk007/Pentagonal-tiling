cmake_minimum_required (VERSION 3.5)
project (PentagonalTiling)

# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")

# Boost config
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE( Boost 1.58 COMPONENTS unit_test_framework REQUIRED )
MESSAGE("Boost Library was found")
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

# CGAL config
# For linux CGAL to work also install package- libcgal-qt5-dev
FIND_PACKAGE(CGAL REQUIRED)
MESSAGE("CGAL Library was found")
INCLUDE( ${CGAL_USE_FILE} )
INCLUDE( CGAL_CreateSingleSourceCGALProgram )
INCLUDE_DIRECTORIES ("${CGAL_ROOT}/include/CGAL")
INCLUDE_DIRECTORIES (BEFORE "../../include")

ADD_LIBRARY(concaveHull concaveHull.cpp)
ADD_LIBRARY(CalculateGap CalculateGap.cpp)
ADD_LIBRARY(PrimitiveTile PrimitiveTile.cpp)
ADD_LIBRARY(myGeometry myGeometry.cpp)
MESSAGE("All files linked")

ADD_EXECUTABLE(main main.cpp)
ADD_EXECUTABLE(run_tests run_tests.cpp)
MESSAGE("All executables added")

TARGET_LINK_LIBRARIES (main CalculateGap PrimitiveTile myGeometry concaveHull)
TARGET_LINK_LIBRARIES (run_tests CalculateGap PrimitiveTile myGeometry concaveHull ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
MESSAGE("All libraries connected")
