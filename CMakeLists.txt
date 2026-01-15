cmake_minimum_required(VERSION 4.0)
project(aurora_db)

set(CMAKE_CXX_STANDARD 20)

add_executable(aurora_db main.cpp
        src/core/db_services.cpp
        src/commands/command_directory.cpp
        src/core/cli.cpp
)

target_include_directories(aurora_db PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
