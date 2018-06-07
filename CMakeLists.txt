cmake_minimum_required(VERSION 3.3)

project(SoftRenderDemo)

add_compile_options("/std:c++latest")
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/thirdlib)

add_subdirectory(src/SoftRender)
add_subdirectory(src/Test)

install(FILES ${CMAKE_SOURCE_DIR}/thirdlib/FreeImage.dll
	DESTINATION bin
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/media
	DESTINATION bin
)
