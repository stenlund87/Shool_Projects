#--------------------------------------------------------------------------
# Solution project
#--------------------------------------------------------------------------

PROJECT(Solution)
FILE(GLOB Solution_headers code/*.h)
FILE(GLOB Solution_sources code/*.cc)

SET(files_Solution ${Solution_headers} ${Solution_sources})
SOURCE_GROUP("Solution" FILES ${files_Solution})

ADD_EXECUTABLE(Solution ${files_Solution})
TARGET_LINK_LIBRARIES(Solution core render)
ADD_DEPENDENCIES(Solution core render)