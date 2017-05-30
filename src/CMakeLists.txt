cmake_minimum_required (VERSION 3.5)
project (PentagonalTiling)

# The version number.
set (Tutorial_VERSION_MAJOR 0)
set (Tutorial_VERSION_MINOR 5)

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")

SET(BOOST_ROOT "C:\\local\\boost_1_64_0")
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREADED ON)

FIND_PACKAGE( Boost 1.60 COMPONENTS unit_test_framework REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

ADD_LIBRARY(CalculateGap CalculateGap.cpp)
ADD_LIBRARY(PrimitiveTile Primitivetile.cpp)

ADD_EXECUTABLE(main main.cpp)
TARGET_LINK_LIBRARIES (main CalculateGap PrimitiveTile ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
