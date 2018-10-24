#--------------------------------------------------------------------------
# Solution project
#--------------------------------------------------------------------------

PROJECT(Solution)
FILE(GLOB Solution_headers code/*.h)
FILE(GLOB Solution_sources code/*.cc)

SET(files_Solution ${Solution_headers} ${Solution_sources} code/Skeleton.cpp code/Skeleton.h code/Animation.cpp code/Animation.h code/Skinning.cpp code/Skinning.h code/VertexComponent.cpp code/VertexComponent.h code/DDS_Types.h code/Shader.h)
SOURCE_GROUP("Solution" FILES ${files_Solution})

ADD_EXECUTABLE(Solution ${files_Solution})
TARGET_LINK_LIBRARIES(Solution core render Mathlib tinyxml2 glut)
ADD_DEPENDENCIES(Solution core render)