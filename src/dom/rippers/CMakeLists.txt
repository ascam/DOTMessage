#####################################
#    DOM message rippers sources    #
#####################################

if (BACKEND_QT)
    add_subdirectory(qt)
endif()

if(BACKEND_SDL2)
	add_subdirectory(sdl)
endif()

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/bitmapgenerator.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/ripper.cpp	
	PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
	PARENT_SCOPE
    )
