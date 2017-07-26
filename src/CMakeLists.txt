cmake_minimum_required (VERSION 3.5)
project (PentagonalTiling)

# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")

SET(BOOST_ROOT "C:\\local\\boost_1_64_0")
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREADED ON)

FIND_PACKAGE( Boost 1.58 COMPONENTS unit_test_framework REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

ADD_LIBRARY(CalculateGap CalculateGap.cpp)
ADD_LIBRARY(PrimitiveTile Primitivetile.cpp)
ADD_LIBRARY(myGeometry myGeometry.cpp)
ADD_LIBRARY(hullfinder hullfinder.cpp)

ADD_EXECUTABLE(main main.cpp)
ADD_EXECUTABLE(run_tests run_tests.cpp)
TARGET_LINK_LIBRARIES (main CalculateGap PrimitiveTile myGeometry hullfinder)
TARGET_LINK_LIBRARIES (run_tests CalculateGap PrimitiveTile myGeometry hullfinder ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
