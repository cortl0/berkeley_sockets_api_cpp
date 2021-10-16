cmake_minimum_required(VERSION 2.8)

project(berkeley_sockets_cpp)

set(SOURCE
	main.cpp
	application.cpp
	communicate/communicator.cpp
	communicate/tcp_client.cpp
	communicate/tcp_server.cpp
	communicate/udp_client.cpp
	communicate/udp_server.cpp
	business_logic/business_logic.cpp
	business_logic/string_extensions.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE})

target_link_libraries(${CMAKE_PROJECT_NAME} pthread)
