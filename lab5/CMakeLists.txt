cmake_minimum_required(VERSION 3.20)

project(Lab5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT WIN32)
    message(FATAL_ERROR " ")
endif()

add_executable(Lab5
    main.cpp
    functions.h
    security.h
    security.cpp
    storage.h
    storage.cpp
    logging.cpp
)

target_compile_definitions(Lab5 PRIVATE
    NOMINMAX
    WIN32_LEAN_AND_MEAN
)

target_link_libraries(Lab5 PRIVATE
    bcrypt
    crypt32
)

if(MSVC)
    target_compile_options(Lab5 PRIVATE /W4 /utf-8)
endif()