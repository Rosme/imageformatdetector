SET(IMG_SRC
	${SRC}/image.cpp
	${SRC}/main.cpp
	${SRC}/detector.cpp
	)

SET(IMG_INC
	${HEADER}/format.hpp
	${HEADER}/image.hpp
	${HEADER}/detector.hpp
	)

ADD_EXECUTABLE(${PROJECT_NAME} ${IMG_SRC} ${IMG_INC})