/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#include <thread>

#include "communicate/tcp/client.h"
#include "communicate/tcp/server.h"
#include "unit_tests/common.h"

constexpr uint16_t server_port{60001};
constexpr uint16_t client_port{60002};

int tcp_test()
{
    communicate::tcp::server server;
    bool stop{false};

    {
        communicate::address server_local_address;
        server_local_address.set_port(server_port);
        ASSERT_TRUE(server.initialize(server_local_address));
        std::thread([&](){ server.start(stop); }).detach();
    }

    {
        const auto etalon = std::string("12345");
        communicate::buffer first;
        communicate::buffer second;
        communicate::tcp::client client;
        communicate::address client_remote_address;
        communicate::address client_local_address;
        client_remote_address.set_ip("127.0.0.1");
        client_remote_address.set_port(server_port);
        ASSERT_TRUE(client.initialize(client_local_address, client_remote_address));
        first.buffer_set(first, etalon);

        ASSERT_TRUE(client.communicator_.send(first) > 0);
        ASSERT_TRUE(client.communicator_.receive(second) > 0);
        ASSERT_EQ(etalon, second.buffer_get(second));
    }

    return EXIT_SUCCESS;
}

int main()
{
    int result{EXIT_SUCCESS};
    result += tcp_test();
    return result;
}
