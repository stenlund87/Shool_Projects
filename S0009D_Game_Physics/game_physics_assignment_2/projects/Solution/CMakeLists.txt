#--------------------------------------------------------------------------
# example project
#--------------------------------------------------------------------------

PROJECT(example)
FILE(GLOB example_headers code/*.h)
FILE(GLOB example_sources code/*.cc)

SET(files_example ${example_headers} ${example_sources} code/Plane.cpp code/Plane.h code/Ray.cpp code/Ray.h code/MeshResource.h code/MeshResource.cc)
SOURCE_GROUP("example" FILES ${files_example})

ADD_EXECUTABLE(example ${files_example})
TARGET_LINK_LIBRARIES(example core render Mathlib)
ADD_DEPENDENCIES(example core render)