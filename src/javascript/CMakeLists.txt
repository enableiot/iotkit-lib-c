find_path (NODE_ROOT_DIR "node/node.h")

set (NODE_INCLUDE_DIRS
  ${NODE_ROOT_DIR}/src
  ${NODE_ROOT_DIR}/node
  ${NODE_ROOT_DIR}/deps/v8/include
  ${NODE_ROOT_DIR}/deps/uv/include
)

include_directories (
  ${NODE_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  ${STAGING_DIR_TARGET}/usr/include/c++/
)
include_directories (${STAGING_DIR_TARGET}/usr/include/c++/)

set (CMAKE_CXX_FLAGS -DBUILDING_NODE_EXTENSION)
# SWIG treats SWIG_FLAGS as a list and not a string so semicolon seperation is required
set_source_files_properties (iotkitjs.i PROPERTIES SWIG_FLAGS "-node;-I${CMAKE_BINARY_DIR}/src")
set_source_files_properties (iotkitjs.i PROPERTIES CPLUSPLUS ON)

swig_add_module (iotkitjs javascript iotkitjs.i ${iotkit_LIB_SRCS})
swig_link_libraries (iotkitjs ${NODE_LIBRARIES})
swig_link_libraries (iotkitjs curl)

if (DOXYGEN_FOUND)
  foreach (_file ${DOCFILES})
    add_dependencies (${SWIG_MODULE_iotkitjs_REAL_NAME} ${_file}doc_i)
  endforeach ()
endif ()

set_target_properties (iotkitjs PROPERTIES
  PREFIX ""
  OUTPUT_NAME iotkit
  SUFFIX ".node"
)

install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/package.json
         ${CMAKE_CURRENT_BINARY_DIR}/iotkit.node
         DESTINATION lib/node_modules/iotkit)
