cmake_minimum_required(VERSION 3.12)
project(CppKata)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        CppKata/process.cpp
)

set(TEST_SOURCE_FILES
        GoogleTestProject/UnitTests.cpp
        GoogleTestProject/pch.cpp
        GoogleTestProject/pch.h
        GoogleTestProject/gtest.h
        GoogleTestProject/gtest-all.cc)

add_library(cppkata
        ${SOURCE_FILES}
        )

add_executable(google_tests
        ${TEST_SOURCE_FILES}
        GoogleTestProject/main.cpp)

target_link_library(google_tests PUBLIC cppkata)

# turn off pthread use in gtest as it's not available on all platforms and not needed for the project
target_compile_definitions(google_tests PUBLIC GTEST_HAS_PTHREAD=0)
