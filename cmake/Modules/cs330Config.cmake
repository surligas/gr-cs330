INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_CS330 cs330)

FIND_PATH(
    CS330_INCLUDE_DIRS
    NAMES cs330/api.h
    HINTS $ENV{CS330_DIR}/include
        ${PC_CS330_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    CS330_LIBRARIES
    NAMES gnuradio-cs330
    HINTS $ENV{CS330_DIR}/lib
        ${PC_CS330_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CS330 DEFAULT_MSG CS330_LIBRARIES CS330_INCLUDE_DIRS)
MARK_AS_ADVANCED(CS330_LIBRARIES CS330_INCLUDE_DIRS)

