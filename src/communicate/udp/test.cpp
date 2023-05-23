/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include <thread>

#include "communicate/udp/client.h"
#include "communicate/udp/server.h"
#include "unit_tests/common.h"

constexpr uint localhost_address{0x7F000001};
constexpr uint16_t server_port{60001};

int send_to_server()
{
    const auto s = std::string("12345");
    communicate::buffer b;
    b.buffer_set(b, s);

    communicate::address local;
    communicate::address remote;
    local.set_ip("127.0.0.1");
    local.set_port(server_port);

    communicate::udp::server server;
    ASSERT_TRUE(server.initialize(local, remote));

    bool stop{false};
    std::thread([&]()
    {
        server.start(stop);
    }).detach();

    {
        communicate::address local;
        communicate::address remote;
        //local.set_port(client_port);
        remote.set_ip("127.0.0.1");
        remote.set_port(server_port);

        communicate::udp::client client;
        ASSERT_TRUE(client.initialize(local, remote));
        client.send(b, remote);
    }

    return EXIT_SUCCESS;
}

int main()
{
    int result{EXIT_SUCCESS};
    result += send_to_server();
    return result;
}
