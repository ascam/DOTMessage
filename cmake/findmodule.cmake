#Function to load external modules
function(findModule MODULE_BASE_PATH MODULE_NAME)
    unset(BASE_PATH CACHE)
    unset(MODULE_BASE_PATH CACHE)
    find_path(BASE_PATH ${MODULE_NAME}
        PATHS "${CMAKE_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}"
        NO_CACHE
        NO_CMAKE_FIND_ROOT_PATH
        NO_SYSTEM_ENVIRONMENT_PATH
    )
    message("#1 find_path returns ${BASE_PATH}")
    if (NOT BASE_PATH)
        unset(BASE_PATH CACHE)
        message("- Missing ${MODULE_NAME} dir we will download from repositories:")
        FetchContent_Populate(${MODULE_NAME})
        find_path(BASE_PATH ${MODULE_NAME}
            PATHS "${CMAKE_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}"
            NO_CACHE
            NO_CMAKE_FIND_ROOT_PATH
            NO_SYSTEM_ENVIRONMENT_PATH
        )
        message("#2 find_path returns ${BASE_PATH}")
        if (NOT BASE_PATH)
            message( FATAL_ERROR "** Missing ${MODULE_NAME} directory")
        endif()
    endif(NOT BASE_PATH)

    if (BASE_PATH)
        set(MODULE_BASE_PATH ${BASE_PATH} PARENT_SCOPE)
    endif(BASE_PATH)
endfunction()