# CMake settings

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)

# About this project
PROJECT(IOTKIT-C-Library)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -fno-omit-frame-pointer")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

MESSAGE("Building the root source C Folder")

find_package (SWIG)
if (SWIG_FOUND)
  include (${SWIG_USE_FILE})
endif ()

set (CMAKE_SWIG_FLAGS "")

find_path (SYSTEM_USR_DIR "stdlib.h")
include_directories (${SYSTEM_USR_DIR})

option (BUILDDOC "Build all doc." OFF)
option (BUILDSWIG "Build swig modules." ON)
option (BUILDSWIGPYTHON "Build swig python modules." ON)
option (BUILDSWIGNODE "Build swig node modules." ON)

if (BUILDDOC)
  # add a target to generate API documentation with Doxygen
  find_package (Doxygen)
  if (DOXYGEN_FOUND)
    configure_file (${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target (doc
      ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
  endif (DOXYGEN_FOUND)
endif()

# add the sub-directories
ADD_SUBDIRECTORY(src)
