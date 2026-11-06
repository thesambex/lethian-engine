cmake_minimum_required(VERSION 4.2.0)

project(Lethian LANGUAGES CXX C VERSION 2026.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/utf-8)
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(VENDOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor")

option(ENABLE_DLL "Enable Dll Build" ON)

add_subdirectory(studio)
add_subdirectory(vendor)
