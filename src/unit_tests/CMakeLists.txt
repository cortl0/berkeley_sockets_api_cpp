#
#   berkeley_sockets
#   created by Ilya Shishkin
#   cortl@8iter.ru
#   https://github.com/cortl0/berkeley_sockets_api_cpp
#   licensed by GPL v3.0
#

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR})

set(UDP_TEST_BIN_NAME udp_test)
add_executable(${UDP_TEST_BIN_NAME} ${CMAKE_SOURCE_DIR}/communicate/udp/test.cpp)
target_link_libraries(${UDP_TEST_BIN_NAME} pthread berkeley_sockets)
add_test(NAME ${UDP_TEST_BIN_NAME} COMMAND ${UDP_TEST_BIN_NAME})

set(TCP_TEST_BIN_NAME tcp_test)
add_executable(${TCP_TEST_BIN_NAME} ${CMAKE_SOURCE_DIR}/communicate/tcp/test.cpp)
target_link_libraries(${TCP_TEST_BIN_NAME} pthread berkeley_sockets)
add_test(NAME ${TCP_TEST_BIN_NAME} COMMAND ${TCP_TEST_BIN_NAME})
