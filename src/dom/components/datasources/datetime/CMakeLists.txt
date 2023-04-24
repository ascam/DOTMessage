############################
#     Datetime headers     #
############################

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/datetimesourcefactory.cpp
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/datetimesourcefactory.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/seconddatetimesource.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/daydatetimesource.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/yeardatetimesource.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/hourdatetimesource.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/minutedatetimesource.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/monthdatetimesource.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/juliandatetimesource.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/perioddatetimesource.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/weekdatetimesource.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/fixedtextdatetimesource.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/datecodedatetimesource.hpp
	# Not implemented
	${CMAKE_CURRENT_SOURCE_DIR}/eradatetimesource.hpp
	# Not implemented
	${CMAKE_CURRENT_SOURCE_DIR}/timezonedatetimesource.hpp
	# Not implemented
	${CMAKE_CURRENT_SOURCE_DIR}/timeoffsetdatetimesource.hpp
	# Not implemented
	${CMAKE_CURRENT_SOURCE_DIR}/secondmultiplesdatetimesource.hpp
	PARENT_SCOPE
	)
