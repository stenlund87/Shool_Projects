#--------------------------------------------------------------------------
# example project
#--------------------------------------------------------------------------

PROJECT(Solution)
FILE(GLOB Solution_headers code/*.h)
FILE(GLOB Solution_sources code/*.cc)

SET(files_Solution ${Solution_headers} ${Solution_sources} code/MeshResource.h code/MeshResource.cc code/Octree.cpp code/Octree.h)
SOURCE_GROUP("Solution" FILES ${files_example})

ADD_EXECUTABLE(Solution ${files_Solution})
TARGET_LINK_LIBRARIES(Solution core render Mathlib)
ADD_DEPENDENCIES(Solution core render)
