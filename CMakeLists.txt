# runs with the following option:
# -DCMAKE_TOOLCHAIN_FILE "$CHEERP_PATH/share/cmake/Modules/CheerpToolchain.cmake"

cmake_minimum_required(VERSION 3.0)

project(twilidoc)
include_directories(/usr/local/include . lib)
link_directories(/usr/local/lib/genericjs /usr/lib/genericjs)

set(CMAKE_CXX_FLAGS "-target cheerp-genericjs -fexceptions -D__CHEERP_CLIENT__ -D__COMET_CLIENT__")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -pedantic")

if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}" -cheerp-sourcemap=application.js.map -cheerp-sourcemap-standalone)
endif()

file(GLOB_RECURSE app_src
  *.cpp *.cxx
  lib/*.cpp lib/*.cxx
)

add_executable(application ${app_src})

target_link_libraries(application
  crails-semantics
  comet
)
