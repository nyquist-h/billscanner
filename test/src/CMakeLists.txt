cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(gnucache-bill-importer_test)

enable_testing()
find_package(GTest REQUIRED)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "-fexceptions -Wall -Wextra -Wno-long-long -Wno-variadic-macros -std=c++11")
include_directories(${GTEST_INCLUDE_DIRS})
include_directories("../../src/")
add_executable(gnucache-bill-importer_test 
                  gnucache-bill-importer_test.cpp
                  imageLoader_test.cpp
                  ../../src/gnucache-bill-importer.cpp
                  ../../src/imageLoader.cpp)

target_link_libraries(gnucache-bill-importer_test ${GTEST_BOTH_LIBRARIES})
target_link_libraries(gnucache-bill-importer_test ${OpenCV_LIBS} )
add_test(gnucache-bill-importer_test gnucache-bill-importer_test)

