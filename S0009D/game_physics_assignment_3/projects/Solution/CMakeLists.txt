#--------------------------------------------------------------------------
# example project
#--------------------------------------------------------------------------

PROJECT(Solution)
FILE(GLOB Solution_headers code/*.h)
FILE(GLOB Solution_sources code/*.cc)

SET(files_Solution ${Solution_headers} ${Solution_sources} code/Plane.cpp code/Plane.h code/Ray.cpp code/Ray.h code/MeshResource.h code/MeshResource.cc code/Collision.cpp code/Collision.h)
SOURCE_GROUP("Solution" FILES ${files_example})

ADD_EXECUTABLE(Solution ${files_Solution})
TARGET_LINK_LIBRARIES(Solution core render Mathlib)
ADD_DEPENDENCIES(Solution core render)