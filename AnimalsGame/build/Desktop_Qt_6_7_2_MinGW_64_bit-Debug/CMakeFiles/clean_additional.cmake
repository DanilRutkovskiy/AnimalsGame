# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "AnimalsGame_autogen"
  "CMakeFiles\\AnimalsGame_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\AnimalsGame_autogen.dir\\ParseCache.txt"
  )
endif()
