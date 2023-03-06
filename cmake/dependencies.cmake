##################  LOADING EXTERNAL SOURCES  ###########################
include(FetchContent)
include(${PROJECT_SOURCE_DIR}/cmake/findmodule.cmake)

## Utils repository
FetchContent_Declare(utils
  GIT_REPOSITORY git@github.com:ascam/utils.git
  GIT_TAG development
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/utils
)

# Loading utils repository
findModule(UTILS_DIR "utils")
set(UTILS_DIR ${MODULE_BASE_PATH}/utils)
message("-- UTILS_DIR:  ${UTILS_DIR}")
if (UTILS_DIR)
        include(${UTILS_DIR}/cmake/macsa.cmake)  #configuration for macsa tij projects
        include(${UTILS_DIR}/cmake/test.cmake)  #configuration test enabled and GTest requiered configuration
endif()
