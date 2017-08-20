cmake_minimum_required (VERSION 3.0)
project (pentagonlib)
set (CMAKE_BUILD_TYPE Debug)

#include *.h files under include folder and
#the project's output folder e.g. Debug
INCLUDE_DIRECTORIES (${PROJECT_BINARY_DIR})

#compile all *.cpp source files
file (GLOB SOURCES "*.cpp")

#output library export file *.lib and
#output macro definitions include file
INCLUDE (GenerateExportHeader)
ADD_LIBRARY(pentagonlib SHARED ${SOURCES})
GENERATE_EXPORT_HEADER (pentagonlib
  BASE_NAME pentagonlib
  EXPORT_MACRO_NAME pentagonlib_EXPORT
  EXPORT_FILE_NAME pentagonlib_Export.h
  STATIC_DEFINE pentagonlib_BUILT_AS_STATIC
  )
