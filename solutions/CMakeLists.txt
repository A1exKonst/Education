cmake_minimum_required(VERSION 3.25)
project(EducationSolutions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compile options:
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -Wall -Wextra -Wpedantic)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "StrictDebug")
    add_compile_options(
        -O1 -g
        -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
        -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion
        -Wfloat-equal -Wformat=2 -Wold-style-cast -Wuseless-cast
        -Wzero-as-null-pointer-constant -Wsuggest-override -Wnon-virtual-dtor
        -Wduplicated-branches -Wduplicated-cond -Wlogical-op -Wnull-dereference
        -Wextra-semi -Wcast-align=strict -Wmissing-declarations -Wctor-dtor-privacy
        -fanalyzer -fstack-protector-strong
        -fsanitize=address,undefined,float-divide-by-zero,float-cast-overflow,bounds-strict
    )
    add_link_options(-fsanitize=address,undefined,float-divide-by-zero,float-cast-overflow,bounds-strict)
endif()


# Automatically build targets:
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*/main.cpp")

foreach(source_file ${SOURCES})
    get_filename_component(dir_path ${source_file} DIRECTORY)
    if(NOT dir_path STREQUAL "build_debug" AND NOT dir_path STREQUAL "build_strict")
        set(target_name "task_${dir_path}")
        add_executable(${target_name} ${source_file})
    endif()
endforeach()
