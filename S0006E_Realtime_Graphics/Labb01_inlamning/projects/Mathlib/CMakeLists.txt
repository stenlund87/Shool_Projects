#--------------------------------------------------------------------------
# Mathlib project
#--------------------------------------------------------------------------

PROJECT(Mathlib)
FILE(GLOB Mathlib_headers code/*.h)


SET(files_Mathlib ${Mathlib_headers} ${Mathlib_sources})
SOURCE_GROUP("Mathlib" FILES ${files_Mathlib})

ADD_EXECUTABLE(Mathlib ${files_Mathlib})
TARGET_LINK_LIBRARIES(Mathlib core render)
ADD_DEPENDENCIES(Mathlib core render)