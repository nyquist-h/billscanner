cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "-fexceptions -Wall -Wextra -Wno-long-long -Wno-variadic-macros -std=c++14")
set(name gnucache-bill-importer)
set(cmake_export_compile_commands 1)

add_library(gnucache-bill-importer SHARED
                 gnucache-bill-importer.cpp
                 imageLoader.cpp)

target_link_libraries(gnucache-bill-importer ${OpenCV_LIBS} )
