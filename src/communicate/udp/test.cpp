/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#include <iostream>
#include <thread>

#include "communicate/udp/client.h"
#include "communicate/udp/server.h"
#include "unit_tests/common.h"

constexpr uint16_t server_port{60002};

int tcp_test()
{
    communicate::address server_local_address;
    communicate::address server_remote_address;
    server_local_address.set_port(server_port);

    communicate::address client_local_address;
    communicate::address client_remote_address;
    //client_local_address.set_port(client_port);
    client_remote_address.set_ip("127.0.0.1");
    client_remote_address.set_port(server_port);

    communicate::udp::server server;
    communicate::udp::client client;
    ASSERT_TRUE(server.initialize(server_local_address, server_remote_address));
    ASSERT_TRUE(client.initialize(client_local_address, client_remote_address));

    const auto etalon = std::string("123abc");
    communicate::buffer first_buffer;
    communicate::buffer second_buffer;
    first_buffer.buffer_set(first_buffer, etalon);

    ASSERT_TRUE(client.communicator_.send(first_buffer, client_remote_address) > 0);
    ASSERT_TRUE(server.communicator_.receive(second_buffer) > 0);
    ASSERT_EQ(etalon, second_buffer.buffer_get(second_buffer));

    return EXIT_SUCCESS;
}

int main()
{
    int result{EXIT_SUCCESS};
    result += tcp_test();
    return result;
}
