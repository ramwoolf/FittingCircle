message(STATUS "CMake version ${CMAKE_VERSION}")
cmake_minimum_required(VERSION 3.0)

set(PROJECT MLS)
project(${PROJECT})

add_definitions(-DMAJOR_VERSION_NUMBER=0)
add_definitions(-DMINOR_VERSION_NUMBER=1)

message("System:        ${CMAKE_SYSTEM_NAME}")
message("C compiller:   ${CMAKE_C_COMPILER}")
message("CXX compiller: ${CMAKE_CXX_COMPILER}")
message("Build type:    ${CMAKE_BUILD_TYPE}")

set(APP_DEFS "${APP_DEFS}")
set(CXX_FLAGS "${APP_DEFS} -std=c++17" )
set(CXX_FLAGS "${CXX_FLAGS} " )

set(C_FLAGS "${APP_DEFS} -std=c99")
set(C_FLAGS "${C_FLAGS} -fdata-sections -ffunction-sections")
set(WARN_FLAGS "-Wall -Wextra -pedantic -Wconversion -Wsign-conversion -Winit-self -Wunreachable-code")

set(FLAGS_RELEASE "-O2")
set(FLAGS_DEBUG   "-O0 -g")

set(CMAKE_C_FLAGS_RELEASE    "${C_FLAGS} ${FLAGS_RELEASE} ${WARN_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG      "${C_FLAGS} ${FLAGS_DEBUG} ${WARN_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE  "${CXX_FLAGS} ${FLAGS_RELEASE} ${WARN_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG    "${CXX_FLAGS} ${FLAGS_DEBUG} ${WARN_FLAGS}")

if(NOT DEFINED LIB_DIR OR LIB_DIR STREQUAL "")
    string(REPLACE "\\" "/" LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
endif()

set(INSTALL_NAME_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_subdirectory(src)