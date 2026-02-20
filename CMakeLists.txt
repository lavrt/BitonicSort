cmake_minimum_required(VERSION 3.11)
project(bitonic_sort LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCL REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options)

add_library(bitonic
    STATIC
        ${CMAKE_SOURCE_DIR}/src/app/parse_cli.cc
)

target_include_directories(bitonic
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src/app
        ${CMAKE_SOURCE_DIR}/src/domain
        ${CMAKE_SOURCE_DIR}/src/infra/cpu
        ${CMAKE_SOURCE_DIR}/src/infra/opencl
)

target_link_libraries(bitonic
    PRIVATE
        OpenCL::OpenCL
        Boost::program_options
)

add_executable(sort
    ${CMAKE_SOURCE_DIR}/src/main.cc
)

target_link_libraries(sort
    PRIVATE
        bitonic
)

add_custom_target(copy_kernels ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/src/infra/opencl/kernels
            $<TARGET_FILE_DIR:sort>/kernels
)
