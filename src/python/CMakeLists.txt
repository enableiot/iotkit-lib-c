FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  ${PYTHON_INCLUDE_DIRS}
)

set_source_files_properties (python-iotkit.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties (python-iotkit.i PROPERTIES SWIG_FLAGS "-I${CMAKE_BINARY_DIR}/src")
swig_add_module (python-iotkit python python-iotkit.i ${iotkit_LIB_SRCS})
swig_link_libraries (python-iotkit ${PYTHON_LIBRARIES})
swig_link_libraries (python-iotkit curl)

if (DOXYGEN_FOUND)
  foreach (_file ${DOCCLASSES})
    add_dependencies (${SWIG_MODULE_python-iotkit_REAL_NAME} ${_file}class_doc_i)
  endforeach ()
  add_dependencies (${SWIG_MODULE_python-iotkit_REAL_NAME} common_hpp_doc_i)

  add_custom_target (pydoc
    pydoc -w ${CMAKE_CURRENT_BINARY_DIR}/iotkit.py ${CMAKE_CURRENT_BINARY_DIR}/
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with pydoc" VERBATIM
  )
endif ()

set_target_properties (${SWIG_MODULE_python-iotkit_REAL_NAME} PROPERTIES
  OUTPUT_NAME _iotkit
  COMPILE_FLAGS "${CMAKE_C_FLAGS} -DSWIGPYTHON=${SWIG_FOUND}"
)

# Essentially do seperate_arguments but with "." instead of " "
string (REPLACE "." ";" PYTHON_VERSION_LIST ${PYTHONLIBS_VERSION_STRING})
list (GET PYTHON_VERSION_LIST 0 PYTHON_VERSION_MAJOR)
list (GET PYTHON_VERSION_LIST 1 PYTHON_VERSION_MINOR)

install (FILES ${CMAKE_CURRENT_BINARY_DIR}/_iotkit.so
         ${CMAKE_CURRENT_BINARY_DIR}/iotkit.py
         DESTINATION lib/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/dist-packages/)

#add_subdirectory (docs)
