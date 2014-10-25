prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
libdir=${exec_prefix}/lib@LIB_SUFFIX@
includedir=${prefix}/include

Name: iotkit
Description: Low Level Skeleton Library for Communication
Version: @iotkit_VERSION_STRING@

Libs: -L${libdir} -liotkit
Cflags: -I${includedir}
