cmake_minimum_required(VERSION 4.0)
project(aurora_db)

set(CMAKE_CXX_STANDARD 20)

add_executable(aurora_db main.cpp
        src/core/db_services.cpp
        src/core/cli_handler.cpp
        src/utility/file_format.cpp
        src/commands/command_controller.cpp
        src/core/database_engine.cpp
)

target_include_directories(aurora_db PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
