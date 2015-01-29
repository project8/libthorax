# CMakeLists for libthorax
# Author: N. Oblath

# Minimum cmake version 2.6 required by the scripts to get Git information
cmake_minimum_required (VERSION 2.6)
cmake_policy (SET CMP0011 NEW)

project (libthorax)
include (${PROJECT_SOURCE_DIR}/PackageBuilder.cmake)
pbuilder_prepare_project (0 1 3)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	pbuilder_add_ext_libraries (m)
    pbuilder_add_ext_libraries (rt)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

include_directories (BEFORE ${PROJECT_SOURCE_DIR})

set (LIBTHORAX_HEADERFILES
    ${CMAKE_CURRENT_SOURCE_DIR}/thorax_digital.h
    ${CMAKE_CURRENT_SOURCE_DIR}/thorax_time.h
    ${CMAKE_CURRENT_SOURCE_DIR}/thorax_types.h
    ${CMAKE_CURRENT_SOURCE_DIR}/thorax_nmr_coordinates.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp/thorax.hh
)

set (LIBTHORAX_SOURCEFILES
    ${CMAKE_CURRENT_SOURCE_DIR}/thorax_nmr_coordinates.c
    ${CMAKE_CURRENT_SOURCE_DIR}/thorax_digital.c
    ${CMAKE_CURRENT_SOURCE_DIR}/thorax_time.c
)


add_library (thorax ${LIBTHORAX_SOURCEFILES})
target_link_libraries (thorax ${EXTERNAL_LIBRARIES})

add_executable (thorax_test ${CMAKE_CURRENT_SOURCE_DIR}/thorax_test.c)
target_link_libraries (thorax_test thorax ${EXTERNAL_LIBRARIES})

add_executable (thorax_cpp_test ${CMAKE_CURRENT_SOURCE_DIR}/cpp/thorax_cpp_test.cc)
target_link_libraries (thorax_cpp_test thorax ${EXTERNAL_LIBRARIES})

pbuilder_install_headers (${LIBTHORAX_HEADERFILES})
pbuilder_install_libraries (thorax)
pbuilder_install_executables (thorax_test thorax_cpp_test)

pbuilder_variables_for_parent()
