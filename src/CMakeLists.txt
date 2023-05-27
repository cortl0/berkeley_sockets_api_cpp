#
#   berkeley_sockets
#   created by Ilya Shishkin
#   cortl@8iter.ru
#   https://github.com/cortl0/berkeley_sockets_api_cpp
#   licensed by GPL v3.0
#

cmake_minimum_required(VERSION 2.8)

project(berkeley_sockets)

include(CTest)
enable_testing()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE
	communicate/communicator.cpp
	communicate/tcp/client.cpp
	communicate/tcp/server.cpp
	communicate/udp/client.cpp
	communicate/udp/server.cpp
)

add_library(${CMAKE_PROJECT_NAME} ${SOURCE})

target_link_libraries(${CMAKE_PROJECT_NAME} pthread)

add_subdirectory(unit_tests)
