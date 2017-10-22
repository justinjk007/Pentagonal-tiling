TARGET_SOURCES(libSimpleSvg
  PRIVATE
  "${CMAKE_CURRENT_LIST_DIR}/drawSvg.cpp"
  PUBLIC
  "${CMAKE_CURRENT_LIST_DIR}/simple_svg_1.0.0.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/drawSvg.hpp"
  )

TARGET_INCLUDE_DIRECTORIES(libSimpleSvg PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

# Remove unwanted from MSVC for simple svg lib
if(MSVC)
  add_definitions(/D_CRT_SECURE_NO_WARNINGS)
  add_definitions(/D_SCL_SECURE_NO_WARNINGS)
  add_definitions(/DNOMINMAX)
endif(MSVC)
