#####################################
#    DOM message rippers headers    #
#####################################

if (BACKEND_QT)
    add_subdirectory(qt)
endif()

if(BACKEND_SDL2)
	add_subdirectory(sdl)
endif()

set(SOURCES ${SOURCES}
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/ripper.hpp
	PARENT_SCOPE
    )
