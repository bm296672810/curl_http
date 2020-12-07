cmake_minimum_required(VERSION 3.0.0)

set(pro_name curl_http)

project(${pro_name} C CXX)

add_library(${pro_name} curl_http.cpp)
target_link_libraries(${pro_name} PUBLIC curl)

set(unit_test http_unit_test)
add_executable(${unit_test} unit_test.cpp)
target_link_directories(${unit_test} PRIVATE "/usr/local/lib64")
target_link_libraries(${unit_test} PUBLIC curl curl_http)