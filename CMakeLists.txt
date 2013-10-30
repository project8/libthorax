# CMakeLists for libthorax
# Author: N. Oblath

# Minimum cmake version 2.6 required by the scripts to get Git information
cmake_minimum_required (VERSION 2.6)

project (libthorax)
include (${PROJECT_SOURCE_DIR}/PackageBuilder.cmake)
pbuilder_prepare_project (0 1 0)


set (LIBTHORAX_HEADERFILES
    ${CMAKE_CURRENT_SOURCE_DIR}/thorax_digital.h
    ${CMAKE_CURRENT_SOURCE_DIR}/thorax_time.h
    ${CMAKE_CURRENT_SOURCE_DIR}/thorax_types.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp/thorax.hh
)

set (LIBTHORAX_SOURCEFILES
    ${CMAKE_CURRENT_SOURCE_DIR}/thorax_digital.c
)



add_library (thorax ${LIBTHORAX_SOURCEFILES})
target_link_libraries (thorax ${EXTERNAL_LIBRARIES})

add_executable (thorax_test ${CMAKE_CURRENT_SOURCE_DIR}/thorax_test.c)
target_link_libraries (thorax_test thorax ${EXTERNAL_LIBRARIES})

pbuilder_install_headers (${LIBTHORAX_HEADERFILES})
pbuilder_install_libraries (thorax)
pbuilder_install_executables (thorax_test)
