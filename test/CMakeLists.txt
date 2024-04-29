#############################
#  DOT Messages DOM Project #
#############################
## Project configuration
cmake_minimum_required(VERSION 3.10)
include_guard(GLOBAL)
cmake_policy(SET CMP0048 NEW)

project(DotMessageTester VERSION 0.0.0)

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(EXECUTABLE_DIR ${PROJECT_SOURCE_DIR}/test)
message("\n## Configuring ${PROJECT_NAME} v${PROJECT_VERSION}")

#####################  VERSION DEFINITION  #############################
add_definitions(-DDOM_TESTER_VERSION_MAJOR=${PROJECT_VERSION_MAJOR})
add_definitions(-DDOM_TESTER_VERSION_MINOR=${PROJECT_VERSION_MINOR})
add_definitions(-DDOM_TESTER_VERSION_BUILD=${PROJECT_VERSION_PATCH})
add_definitions(-DDOM_TESTER_VERSION="${PROJECT_VERSION}")

##################  LOADING MODULES  ###########################
include(${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/CMakeRC.cmake)

option(STANDALONE "Build as standalone executable" OFF)

####################  SOURCES AND HEADERS  #############################

## Add Macsa systems datamodel ##
add_subdirectory(${DOTSYSTEM_DIR}            ${PROJECT_BINARY_DIR}/dotsystem)
## Add Macsa utilities library
add_subdirectory(${UTILS_DIR}/libutils       ${PROJECT_BINARY_DIR}/libutils)

set(SOURCES)
set(HEADERS)

set(SOURCES ${SOURCES}
    ${EXECUTABLE_DIR}/main.cpp
    )

if (${ENABLE_TESTS})
        set(SRC_TEST)
	set(HDRS_TEST)
	add_subdirectory(unitests)
endif()

cmrc_add_resource_library(domTesterFiles
	NAMESPACE dot
	WHENCE rc
	PREFIX messages
	rc/CQ.nisx
	rc/MENSAJE3.NISX
	rc/MENSAJE5.NISX
	rc/TEST_BARCODES.nisx
	rc/TEST_III.nisx
	rc/TEST_II.nisx
	rc/TEST_I.nisx
	rc/TEST_IV.nisx
	rc/TEST.nisx
	rc/TEST_VI.nisx
	rc/TEST_V.nisx
	rc/testParserNisx.nisx
	rc/GALLO.nisx

	rc/linx/linxformatted.ciff
	rc/linx/msj_01_tto_formatted.ciff
	rc/linx/msj_jovi.ciff
	rc/linx/textofijo.ciff
	rc/linx/EFAPEL.ciff
	rc/linx/frankfurt.ciff
	rc/linx/NORTE_EUROCAO.ciff
	rc/linx/Pan_molde.ciff
	rc/linx/Pan_molde_4_dias.ciff
	rc/linx/tt3fira.ciff
	rc/linx/tt5nou.ciff
	rc/linx/tt10_HSPCK2015.ciff
	rc/linx/VARIABLE.ciff
	rc/linx/VARIABLE2.ciff
	rc/linx/Yogur_35_dias.ciff
	rc/linx/utf16/frankfurt.ciff
	rc/linx/Full_barcodes.ciff
	rc/linx/pedro.ciff
	rc/linx/barcodes_full.ciff
	rc/linx/datas_full.ciff
	)

####################  TARGETS  #############################
if(STANDALONE)
         ## Add windows OS support
	set(DEPENDENCIES
	        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libdotmessage.a
	        )
else()
        set(DEPENDENCIES
	        dotmessage
			dotsystem
	        )
endif()

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
        PUBLIC
	        ${PROJECT_SOURCE_DIR}/include
		${PROJECT_SOURCE_DIR}/src
		${DOTSYSTEM_INCLUDE_DIRECTORY}
		${UTILS_INCLUDE_DIRECTORY}
	)

#linking dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEPENDENCIES} PRIVATE domTesterFiles)
target_link_directories(${PROJECT_NAME} PUBLIC ${LIB_PREFIX}/lib ${CMAKE_BINARY_DIR}/lib)


if (${ENABLE_TESTS})
        message("Adding ${PROJECT_NAME} tests dir ${PROJECT_BINARY_DIR}" )
	set(PROJECT_TEST_NAME ${PROJECT_NAME}_UT)
	add_executable(${PROJECT_TEST_NAME} ${SRC_TEST} ${HDRS_TEST})
	target_include_directories(${PROJECT_TEST_NAME}
	        PUBLIC
		        ${PROJECT_SOURCE_DIR}/include
			${PROJECT_SOURCE_DIR}/src
			${DOTSYSTEM_INCLUDE_DIRECTORY}
			${UTILS_INCLUDE_DIRECTORY}
		)
	target_link_directories(${PROJECT_TEST_NAME} PUBLIC ${CMAKE_BINARY_DIR}/lib)
	target_link_libraries(${PROJECT_TEST_NAME} ${GTEST_LIBS} ${EXTERNAL_LIBS} ${DEPENDENCIES})
	add_test(${PROJECT_NAME} ${PROJECT_TEST_NAME})
endif()
