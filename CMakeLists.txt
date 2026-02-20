cmake_minimum_required(VERSION 3.11)
project(bitonic_sort LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sort
    src/main.cc
    src/app/parse_cli.cc
)

target_include_directories(sort
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app
        ${CMAKE_CURRENT_SOURCE_DIR}/src/domain
        ${CMAKE_CURRENT_SOURCE_DIR}/src/infra/cpu
        ${CMAKE_CURRENT_SOURCE_DIR}/src/infra/opencl
)

add_custom_command(TARGET sort POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/src/infra/opencl/kernels
            $<TARGET_FILE_DIR:sort>/kernels
)

find_package(OpenCL REQUIRED)
target_link_libraries(sort PRIVATE OpenCL::OpenCL)

find_package(Boost REQUIRED COMPONENTS program_options)
target_link_libraries(sort PRIVATE Boost::program_options)