cmake_minimum_required(VERSION 3.18)

project(UnicodeOutputTest VERSION 0.1)

option(IS_WIDE "Use wide chars" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(TestEncoding test_encoding.cpp)
if(IS_WIDE)
  target_compile_definitions(TestEncoding PRIVATE -DWIDE=true)
else()
  target_compile_definitions(TestEncoding PRIVATE -DWIDE=false)
endif()
target_link_options(TestEncoding PRIVATE -mconsole)