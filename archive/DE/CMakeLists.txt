TARGET_SOURCES(DE
  PRIVATE
  # "${CMAKE_CURRENT_LIST_DIR}/cec17_test_func.cc"
  "${CMAKE_CURRENT_LIST_DIR}/lshade.cc"
  "${CMAKE_CURRENT_LIST_DIR}/search_algorithm.cc"
  PUBLIC
  "${CMAKE_CURRENT_LIST_DIR}/de.h"
  )

TARGET_INCLUDE_DIRECTORIES(DE PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

MESSAGE("-- All DE files linked")
# https://crascit.com/2016/01/31/enhanced-source-file-handling-with-target_sources/
