cmake_minimum_required (VERSION 3.5)
project (PentagonalTiling)

# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")

# Boost config
SET(BOOST_ROOT "C:\\local\\boost_1_64_0")
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE( Boost 1.58 COMPONENTS unit_test_framework REQUIRED )
message("Boost Library was found successfully")
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

# CGAL config
find_package(CGAL REQUIRED)
message("CGAL Library was found")
include( ${CGAL_USE_FILE} )
include( CGAL_CreateSingleSourceCGALProgram )
include_directories ("${CGAL_ROOT}/include/CGAL")
include_directories (BEFORE "../../include")

ADD_LIBRARY(concaveHull concaveHull.cpp)
ADD_LIBRARY(CalculateGap CalculateGap.cpp)
ADD_LIBRARY(PrimitiveTile Primitivetile.cpp)
ADD_LIBRARY(myGeometry myGeometry.cpp)
message("All files successfully linked")

ADD_EXECUTABLE(main main.cpp)
ADD_EXECUTABLE(run_tests run_tests.cpp)
message("All executables successfully added")

TARGET_LINK_LIBRARIES (main CalculateGap PrimitiveTile myGeometry concaveHull)
TARGET_LINK_LIBRARIES (run_tests CalculateGap PrimitiveTile myGeometry concaveHull ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
message("All libraries successfully connected")
