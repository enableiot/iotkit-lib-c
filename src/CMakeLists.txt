# Set the shared library name
SET(IOTKIT_LIBRARY_NAME "iotkitlib")

# Create the shared library
ADD_LIBRARY(${IOTKIT_LIBRARY_NAME} SHARED iotkit.c rest.c)

SET_TARGET_PROPERTIES(${IOTKIT_LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE C)

# Link the shared library
#TARGET_LINK_LIBRARIES(${IOTKIT_LIBRARY_NAME} m)
