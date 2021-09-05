cmake_minimum_required(VERSION 3.10)

project(cspl CXX)

if(WIN32)
    add_subdirectory(lib/hunspell)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(hunspell REQUIRED IMPORTED_TARGET hunspell)
    add_library(hunspell INTERFACE)
    target_link_libraries(hunspell INTERFACE PkgConfig::hunspell)
endif()
add_subdirectory(lib/clipp)
add_subdirectory(src)

