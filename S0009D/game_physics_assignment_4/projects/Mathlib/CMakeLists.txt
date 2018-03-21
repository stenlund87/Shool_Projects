#--------------------------------------------------------------------------
# Mathlib project
#--------------------------------------------------------------------------

PROJECT(Mathlib)
FILE(GLOB Mathlib_headers code/*.h)


SET(files_Mathlib ${Mathlib_headers} ${Mathlib_sources})
SOURCE_GROUP("Mathlib" FILES ${files_Mathlib})

ADD_LIBRARY(Mathlib INTERFACE)
#ADD_EXECUTABLE(Mathlib ${files_Mathlib})
TARGET_INCLUDE_DIRECTORIES(Mathlib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/code)