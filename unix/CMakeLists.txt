# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(serialize)
project(test)

# use c++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add dependencies include dir
set(SOURCEDIR ../pe\ disassembler/source/)
include_directories(../dependencies)
include_directories(${SOURCEDIR})

set(SERIALIZE_SRC
	serialize.cpp
	${SOURCEDIR}/pe/dos_header.cpp
	${SOURCEDIR}/pe/image_base_relocations.cpp
	${SOURCEDIR}/pe/image_export.cpp
	${SOURCEDIR}/pe/image_import.cpp
	${SOURCEDIR}/pe/nt_header.cpp
	${SOURCEDIR}/pe/pe.cpp
	${SOURCEDIR}/pe/section.cpp
)
add_executable(serialize ${SERIALIZE_SRC})
add_executable(test test.cpp)

