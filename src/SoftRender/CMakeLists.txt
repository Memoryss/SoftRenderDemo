file(GLOB srcs
	"*.h"
	"*.cpp"
)


add_library(SoftRender STATIC
	${srcs}
)