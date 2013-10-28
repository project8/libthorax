# CMakeLists for libthorax
# Author: N. Oblath

# Minimum cmake version 2.6 required by the scripts to get Git information
cmake_minimum_required (VERSION 2.6)

project (libthorax)
include (${CMAKE_SOURCE_DIR}/PackageBuilder.cmake)
pbuilder_prepare_project (0 1 0)


set (LIBTHORAX_HEADERFILES
    ${CMAKE_CURRENT_SOURCE_DIR}/digital.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp/thorax.hh
)

set (LIBTHORAX_SOURCEFILES
    ${CMAKE_CURRENT_SOURCE_DIR}/digital.c
)

add_library (thorax ${LIBTHORAX_SOURCEFILES})
target_link_libraries (thorax ${EXTERNAL_LIBRARIES})

pbuilder_install_headers( ${LIBTHORAX_HEADERFILES} )
pbuilder_install_libraries( thorax )
