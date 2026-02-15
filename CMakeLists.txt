cmake_minimum_required(VERSION 3.11)
project(bitonic_sort LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sort src/main.cpp)

target_include_directories(sort
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app
        ${CMAKE_CURRENT_SOURCE_DIR}/src/domain
        ${CMAKE_CURRENT_SOURCE_DIR}/src/infra/cpu
)

find_package(OpenCL REQUIRED)
target_link_libraries(sort PRIVATE OpenCL::OpenCL)
