cmake_minimum_required(VERSION 3.22.1)
project(kebabengine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(kebabengine SHARED
    EngineJNI.cpp
    ../../../../../engine/Engine.cpp
    ../../../../../engine/Renderer.cpp
)

target_include_directories(kebabengine PRIVATE
    ../../../../../engine
)

find_library(log-lib log)
find_library(gles-lib GLESv3)

target_link_libraries(kebabengine
    ${log-lib}
    ${gles-lib}
)
