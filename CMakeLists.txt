# CMake settings

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)

# About this project
PROJECT(IOTKIT-C-Library)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -fno-omit-frame-pointer")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

# Appends the cmake/modules path to MAKE_MODULE_PATH variable.
set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

# Make a version file containing the current version from git.
include (GetGitRevisionDescription)
git_describe (VERSION "--tags")
if ("x_${VERSION}" STREQUAL "x_GIT-NOTFOUND")
  message (WARNING " - Install git to compile a production libiotkit!")
  set (VERSION "v0.1.0-dirty")
endif ()

message (INFO " - IOTKIT Version ${VERSION}")

#parse the version information into pieces.
string (REGEX REPLACE "^v([0-9]+)\\..*" "\\1" VERSION_MAJOR "${VERSION}")
string (REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${VERSION}")
string (REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${VERSION}")
set (VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

if ("${VERSION_COMMIT}" MATCHES "^v.*")
  set (VERSION_COMMIT "")
endif()

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/version.c.in
                ${CMAKE_CURRENT_BINARY_DIR}/src/version.c)

# this is the library version, independant of git revision
set (iotkit_VERSION_MAJOR ${VERSION_MAJOR})
set (iotkit_VERSION_MINOR ${VERSION_MINOR})
set (iotkit_VERSION_PATCH ${VERSION_PATCH})
set (iotkit_VERSION_STRING ${iotkit_VERSION_MAJOR}.${iotkit_VERSION_MINOR}.${iotkit_VERSION_PATCH})

set (CMAKE_SWIG_FLAGS "")

set (CMAKE_CXX_FLAGS_COVERAGE "-g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage")
set (CMAKE_C_FLAGS_COVERAGE "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
set (CMAKE_EXE_LINKER_FLAGS_COVERAGE "-fprofile-arcs -ftest-coverage")


# support for adding tests, adds another build target 'test'
ENABLE_TESTING()

# Adds some testing specific build targets e.g. make Experimental
INCLUDE(CTest)

find_package (SWIG)
if (SWIG_FOUND)
  include (${SWIG_USE_FILE})
endif ()

find_path (SYSTEM_USR_DIR "stdlib.h")
include_directories (${SYSTEM_USR_DIR})

option (BUILDDOC "Build documentation." ON)
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
#ADD_SUBDIRECTORY(tests)

SET (CTEST_BINARY_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/output/bin" )
MESSAGE (STATUS "Ctest Binary Directory  set to: ${CTEST_BINARY_DIRECTORY}")
