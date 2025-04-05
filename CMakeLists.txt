cmake_minimum_required(VERSION 2.10...3.10)
project(Laboratorio
        LANGUAGES C
        VERSION 1.0
        DESCRIPTION "Laboratorio de Sistemas Operativos"
)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(C_STRICT_FLAGS
        -ansi
        -pedantic-errors
        -Wall
        -Wextra
        -Werror
        -Wstrict-prototypes
        -Wold-style-definition
        -Wmissing-prototypes
        -Wmissing-declarations
        -Wno-unused-parameter
        -Wdeclaration-after-statement
        -Wbad-function-cast
        -Wcast-qual
        -Wcast-align
        -Wwrite-strings
)

string(JOIN " " CMAKE_C_FLAGS ${C_STRICT_FLAGS})

file(GLOB_RECURSE FRAMEWORK_SOURCES src/framework/*.c)
add_library(framework ${FRAMEWORK_SOURCES})

target_include_directories(framework PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(consumer src/consumer/main.c)
add_executable(producer src/producer/main.c)

target_link_libraries(consumer PRIVATE framework)
target_link_libraries(producer PRIVATE framework)
