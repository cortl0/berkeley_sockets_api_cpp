#
#   berkeley_sockets
#   created by Ilya Shishkin
#   cortl@8iter.ru
#   https://github.com/cortl0/berkeley_sockets
#   licensed by GPL v3.0
#

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.. .)
include(CTest)
enable_testing()

set(BERKELEY_SOCKETS_TEST_BIN_NAME berkeley_sockets_test)

set(SOURCES
    ../main.cpp
    ../communicate/communicator.cpp
	../communicate/tcp_client.cpp
	../communicate/tcp_server.cpp
	../communicate/udp_client.cpp
	../communicate/udp_server.cpp
    )

add_executable(${BERKELEY_SOCKETS_TEST_BIN_NAME} ${SOURCES})
target_link_libraries(${BERKELEY_SOCKETS_TEST_BIN_NAME} pthread)
add_test(NAME ${BERKELEY_SOCKETS_TEST_BIN_NAME} COMMAND ${BERKELEY_SOCKETS_TEST_BIN_NAME})
