cmake_minimum_required (VERSION 3.1.0)
project (luabrotli)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Include Lua 5.1

include(FindLua51)
include_directories(SYSTEM
	${LUA_INCLUDE_DIR}
	${LUA_INCLUDE_DIR}/lua5.1
)

include_directories(dependencies/lutok2/include)

# Include brotli

add_subdirectory(cmake/brotli)
include_directories(dependencies/brotli/dec)
include_directories(dependencies/brotli/enc)

add_subdirectory(src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
set_target_properties(luabrotli PROPERTIES PREFIX "")

