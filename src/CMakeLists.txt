#
#   berkeley_sockets
#   created by Ilya Shishkin
#   cortl@8iter.ru
#   https://github.com/cortl0/berkeley_sockets_api_cpp
#   licensed by GPL v3.0
#

cmake_minimum_required(VERSION 3.0)

project(berkeley_sockets)

include(CTest)
enable_testing()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE
	communicate/address.cpp
	communicate/buffer.cpp
	communicate/communicator.cpp
	communicate/tcp/client.cpp
	communicate/tcp/server.cpp
	communicate/udp/peer.cpp
)

add_library(${CMAKE_PROJECT_NAME} ${SOURCE})

target_link_libraries(${CMAKE_PROJECT_NAME} pthread)

add_subdirectory(unit_tests)
