# Native port (ADR 0010): CMake and Clang, separate from the matching build.
cmake_minimum_required(VERSION 3.20)
project(sotc_port LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT CMAKE_C_COMPILER_ID MATCHES "Clang")
  message(WARNING "The Native port is built with Clang (clang-cl on Windows); ${CMAKE_C_COMPILER_ID} is untested.")
endif()

option(SOTC_PORT_WERROR "Treat warnings as errors" OFF)
option(SOTC_PORT_SANITIZE "Build with AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

if(MSVC)
  set(SOTC_PORT_WARNINGS /W4)
  if(SOTC_PORT_WERROR)
    list(APPEND SOTC_PORT_WARNINGS /WX)
  endif()
  # clang-cl: the CRT's portable function names are fine here.
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
  set(SOTC_PORT_WARNINGS -Wall -Wextra -Wpedantic -Wshadow -Wstrict-prototypes)
  if(SOTC_PORT_WERROR)
    list(APPEND SOTC_PORT_WARNINGS -Werror)
  endif()
endif()

if(SOTC_PORT_SANITIZE)
  add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer -fno-sanitize-recover=all)
  add_link_options(-fsanitize=address,undefined)
endif()

# Disc image reader and NICO.DAT parser.
add_library(sotc_disc STATIC disc/disc_image.c disc/nicodat.c)
target_include_directories(sotc_disc PUBLIC disc)
target_compile_options(sotc_disc PRIVATE ${SOTC_PORT_WARNINGS})

# Prints the NICO.DAT table of contents of a Disc image.
add_executable(nicoinfo tools/nicoinfo.c)
target_link_libraries(nicoinfo PRIVATE sotc_disc)
target_compile_options(nicoinfo PRIVATE ${SOTC_PORT_WARNINGS})

include(CTest)
if(BUILD_TESTING)
  add_library(sotc_synthetic STATIC tests/synthetic.c)
  target_include_directories(sotc_synthetic PUBLIC tests)
  target_compile_options(sotc_synthetic PRIVATE ${SOTC_PORT_WARNINGS})

  foreach(test test_disc_image test_nicodat)
    add_executable(${test} tests/${test}.c)
    target_link_libraries(${test} PRIVATE sotc_disc sotc_synthetic)
    target_compile_options(${test} PRIVATE ${SOTC_PORT_WARNINGS})
    add_test(NAME ${test} COMMAND ${test} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  endforeach()
endif()
