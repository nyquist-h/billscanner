cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(gnucache-bill-importer_test)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(gnucache-bill-importer_test gnucache-bill-importer_test.cpp)
target_link_libraries(gnucache-bill-importer_test ${GTEST_BOTH_LIBRARIES})
add_test(gnucache-bill-importer_test gnucache-bill-importer_test)

