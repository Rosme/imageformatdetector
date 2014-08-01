SET(IMG_SRC
	${SRC}/image.cpp
	${SRC}/main.cpp
	)

SET(IMG_INC
	${HEADER}/format.hpp
	${HEADER}/image.hpp
	)

ADD_EXECUTABLE(${PROJECT_NAME} ${IMG_SRC} ${IMG_INC})