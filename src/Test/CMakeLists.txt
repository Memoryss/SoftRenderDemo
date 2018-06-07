file(GLOB srcs
	"*.h"
	"*.cpp"
)


add_executable(SoftRenderTest WIN32
	${srcs}
)

target_link_libraries(SoftRenderTest SoftRender)

include_directories(${CMAKE_SOURCE_DIR}/src/SoftRender)

install(TARGETS SoftRenderTest
	RUNTIME DESTINATION bin
)