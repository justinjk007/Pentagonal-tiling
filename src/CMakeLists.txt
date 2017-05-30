cmake_minimum_required (VERSION 3.5)
project (PentagonalTiling)

# The version number.
set (Tutorial_VERSION_MAJOR 0)
set (Tutorial_VERSION_MINOR 5)

# configure a header file to pass some of the CMake settings
# to the source code
# configure_file (
#   "${PROJECT_SOURCE_DIR}/Config.h.in"
#   "${PROJECT_BINARY_DIR}/Config.h"
#   )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

SET(BOOST_ROOT "C:\\local\\boost_1_64_0")
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREADED ON)

FIND_PACKAGE( Boost 1.60 COMPONENTS unit_test_framework REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

ADD_LIBRARY(CalculateGap CalculateGap.cpp)
ADD_LIBRARY(PrimitiveTile Primitivetile.cpp)

ADD_EXECUTABLE(main main.cpp)
TARGET_LINK_LIBRARIES (main CalculateGap PrimitiveTile ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
