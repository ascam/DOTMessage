##################################
#	Qt backend generator sources #
##################################

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/qtgenerator.cpp
	#objects
	${CMAKE_CURRENT_SOURCE_DIR}/qtbarcode.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/qtdiamond.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/qtellipse.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/qtimage.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/qtline.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/qtobject.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/qtprimitive.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/qtrectangle.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/qttext.cpp
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/qtgenerator.hpp
	#objects
	${CMAKE_CURRENT_SOURCE_DIR}/qtbarcode.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/qtdiamond.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/qtellipse.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/qtimage.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/qtline.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/qtobject.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/qtprimitive.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/qtrectangle.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/qttext.hpp
	PARENT_SCOPE
	)
	
set(INCLUDES ${INCLUDES}
	${CMAKE_CURRENT_SOURCE_DIR}
	PARENT_SCOPE
)	
