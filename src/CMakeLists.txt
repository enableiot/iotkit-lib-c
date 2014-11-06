include_directories(
  ${PROJECT_SOURCE_DIR}/lib/cJSON
  ${PROJECT_SOURCE_DIR}/src
  ${STAGING_DIR_TARGET}/usr/include/c++/
)
include_directories (${STAGING_DIR_TARGET}/usr/include/c++/)

set (iotkit_LIB_SRCS
  ${PROJECT_SOURCE_DIR}/src/iotkit.c
  ${PROJECT_SOURCE_DIR}/src/rest.c
  ${PROJECT_SOURCE_DIR}/src/account_management.c
  ${PROJECT_SOURCE_DIR}/src/advanced_data_inquiry.c
  ${PROJECT_SOURCE_DIR}/src/aggregated_report_interface.c
  ${PROJECT_SOURCE_DIR}/src/alert_management.c
  ${PROJECT_SOURCE_DIR}/src/authorization.c
  ${PROJECT_SOURCE_DIR}/src/authorization_token.c
  ${PROJECT_SOURCE_DIR}/src/component_catalog.c
  ${PROJECT_SOURCE_DIR}/src/data_api.c
  ${PROJECT_SOURCE_DIR}/src/device_management.c
  ${PROJECT_SOURCE_DIR}/src/device_token.c
  ${PROJECT_SOURCE_DIR}/src/invitation_management.c
  ${PROJECT_SOURCE_DIR}/src/net_uuid.c
  ${PROJECT_SOURCE_DIR}/src/rule_management.c
  ${PROJECT_SOURCE_DIR}/src/user_management.c
  ${PROJECT_SOURCE_DIR}/lib/cJSON/cJSON.c
)

set (iotkit_LIB_GLOB_HEADERS
  ${PROJECT_SOURCE_DIR}/src/iotkit.h
  ${PROJECT_SOURCE_DIR}/src/account_management.h
  ${PROJECT_SOURCE_DIR}/src/advanced_data_inquiry.h
  ${PROJECT_SOURCE_DIR}/src/aggregated_report_interface.h
  ${PROJECT_SOURCE_DIR}/src/alert_management.h
  ${PROJECT_SOURCE_DIR}/src/authorization.h
  ${PROJECT_SOURCE_DIR}/src/component_catalog.h
  ${PROJECT_SOURCE_DIR}/src/data_api.h
  ${PROJECT_SOURCE_DIR}/src/device_management.h
  ${PROJECT_SOURCE_DIR}/src/invitation_management.h
  ${PROJECT_SOURCE_DIR}/src/rest.h
  ${PROJECT_SOURCE_DIR}/src/rule_management.h
  ${PROJECT_SOURCE_DIR}/src/user_management.h
  ${PROJECT_SOURCE_DIR}/src/util.h
  ${PROJECT_SOURCE_DIR}/lib/cJSON/cJSON.h
)

add_library (iotkit SHARED ${iotkit_LIB_SRCS})
target_link_libraries (iotkit ${CMAKE_THREAD_LIBS_INIT})

set_target_properties(
   iotkit
   PROPERTIES
   SOVERSION ${iotkit_VERSION_MAJOR}
   VERSION ${iotkit_VERSION_STRING}
)
install (FILES ${iotkit_LIB_GLOB_HEADERS} DESTINATION include/)
install (DIRECTORY ${PROJECT_SOURCE_DIR}/iotkit/ DESTINATION include/iotkit)

macro (iotkit_CREATE_INSTALL_PKGCONFIG generated_file install_location)
  configure_file (${generated_file}.cmake ${CMAKE_CURRENT_BINARY_DIR}/${generated_file} @ONLY)
  install (FILES ${CMAKE_CURRENT_BINARY_DIR}/${generated_file} DESTINATION ${install_location})
endmacro (iotkit_CREATE_INSTALL_PKGCONFIG)
iotkit_create_install_pkgconfig (iotkit.pc lib${LIB_SUFFIX}/pkgconfig)

install (TARGETS iotkit DESTINATION lib)

if (DOXYGEN_FOUND)
  set (CMAKE_SWIG_FLAGS -DDOXYGEN=${DOXYGEN_FOUND})
  # CPP class headers
  foreach (_file ${DOCCLASSES})
    add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_file}_class_doc.i
      COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/doxy2swig.py -n
        ${CMAKE_BINARY_DIR}/xml/classiotkit_1_1_${_file}.xml
        ${CMAKE_CURRENT_BINARY_DIR}/${_file}_class_doc.i
      DEPENDS ${CMAKE_BINARY_DIR}/xml/classiotkit_1_1_${_file}.xml
    )
    add_custom_target (${_file}class_doc_i DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${_file}_class_doc.i)
    add_dependencies (${_file}class_doc_i doc)
  endforeach ()
  # C header files
  set (DOCFILES common ${DOCCLASSES})
  foreach (_file ${DOCFILES})
    add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_file}_doc.i
      COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/doxy2swig.py -n
        ${CMAKE_BINARY_DIR}/xml/${_file}_8h.xml
        ${CMAKE_CURRENT_BINARY_DIR}/${_file}_doc.i
      DEPENDS ${CMAKE_BINARY_DIR}/xml/${_file}_8h.xml
    )
    add_custom_target (${_file}doc_i DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${_file}_doc.i)
    add_dependencies (${_file}doc_i doc)
  endforeach ()
  # CPP common header
  add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/common_hpp_doc.i
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/doxy2swig.py -n
      ${CMAKE_BINARY_DIR}/xml/common_8hpp.xml
      ${CMAKE_CURRENT_BINARY_DIR}//common_hpp_doc.i
    DEPENDS ${CMAKE_BINARY_DIR}/xml/common_8hpp.xml
  )
  add_custom_target (common_hpp_doc_i DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/common_hpp_doc.i)
  add_dependencies (common_hpp_doc_i doc)
endif ()

if (BUILDSWIG)
  find_package (SWIG)
  if (SWIG_FOUND)
    include (${SWIG_USE_FILE})
    set_source_files_properties (iotkit.i PROPERTIES SWIG_FLAGS "-I${CMAKE_BINARY_DIR}/src")

    if (BUILDSWIGPYTHON)
      add_subdirectory (python)
    endif ()
    if (BUILDSWIGNODE)
      add_subdirectory (javascript)
    endif ()
  endif ()
endif ()
