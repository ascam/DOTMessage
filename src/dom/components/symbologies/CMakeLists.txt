######################################################
#      DOT Messages barcode symbologies sources      #
######################################################

set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/symbology.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/barcodesymbology.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/barcodeapplications.cpp
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/symbology.hpp
    PARENT_SCOPE
    )

