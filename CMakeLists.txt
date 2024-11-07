
cmake_minimum_required(VERSION 3.10)

project(HelloWorld)

find_package(Microsoft.GSL CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_executable(HelloWorld helloworld.cpp)

target_link_libraries(HelloWorld PRIVATE fmt::fmt)
target_link_libraries(HelloWorld PRIVATE Microsoft.GSL::GSL)
