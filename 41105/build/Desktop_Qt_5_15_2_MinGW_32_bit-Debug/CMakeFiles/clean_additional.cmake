# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "41105_autogen"
  "CMakeFiles\\41105_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\41105_autogen.dir\\ParseCache.txt"
  )
endif()
