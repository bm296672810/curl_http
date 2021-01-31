cmake_minimum_required(VERSION 3.0.0)

set(pro_name curl_http)

project(${pro_name} C CXX)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

add_library(${pro_name} curl_http.cpp)
target_link_directories(${pro_name} PUBLIC "/usr/local/lib64" "/usr/local/lib")
target_link_libraries(${pro_name} PUBLIC curl)

set(unit_test http_unit_test)
add_executable(${unit_test} unit_test.cpp)
target_link_directories(${unit_test} PUBLIC "/usr/local/lib64" "/usr/local/lib")
target_link_libraries(${unit_test} PUBLIC curl curl_http)