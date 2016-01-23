set(luabrotli_src
	main.cpp
	objects/Compressor.cpp
	objects/Decompressor.cpp
	constants.cpp
)

set(luabrotli_h
	common.hpp
	objects/Compressor.hpp
	objects/Decompressor.hpp
	constants.hpp
	init_classes.hpp
)

set(luabrotli_sources
	${luabrotli_src} ${luabrotli_h} ${brotli_sources}
)

include_directories(./)

source_group("Header files" FILES ${luabrotli_h})
source_group("Brotli sources" FILES ${brotli_sources})

set(luabrotli_version_script luabrotli.version)

IF(UNIX)
    IF(CMAKE_COMPILER_IS_GNUCC)
         SET(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} ${CMAKE_CXX_COMPILE_OPTIONS_VISIBILITY}hidden -Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/${luabrotli_version_script}")
    ENDIF(CMAKE_COMPILER_IS_GNUCC)

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-declarations")
ENDIF(UNIX)

add_library(luabrotli SHARED
	${luabrotli_sources}
)

set_property(TARGET luabrotli PROPERTY CXX_STANDARD 11)
set_property(TARGET luabrotli PROPERTY CXX_STANDARD_REQUIRED ON)

set_target_properties(luabrotli
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_PROCESSOR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_PROCESSOR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_PROCESSOR}/bin"
)

target_link_libraries (luabrotli
	${LUA_LIBRARY} brotli
)

