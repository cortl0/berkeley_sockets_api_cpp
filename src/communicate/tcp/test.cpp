/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include <thread>

#include "communicate/tcp/client.h"
#include "communicate/tcp/server.h"
#include "unit_tests/common.h"

constexpr uint localhost_address{0x7F000001};
constexpr uint16_t server_port{60001};
constexpr uint16_t client_port{60002};

int send_to_server()
{
    const auto s = std::string("12345");
    communicate::buffer b;
    b.buffer_set(b, s);

    communicate::tcp::server server;
    communicate::address local;
    communicate::address remote;
    local.set_ip("127.0.0.1");
    local.set_port(server_port);
    ASSERT_TRUE(server.initialize(local, remote));

    bool stop{false};
    std::thread([&]()
    {
        server.start(stop);
    }).detach();

    {
        communicate::tcp::client client;
        communicate::address local;
        communicate::address remote;
        //local.set_port(client_port);
        remote.set_ip("127.0.0.1");
        remote.set_port(server_port);
        ASSERT_TRUE(client.initialize(local, remote));
        client.send(b, remote);

        std::string stub("input anything");
        std::cout << stub << std::endl;
        std::cin >> stub;
    }

    return EXIT_SUCCESS;
}

int main()
{
    int result{EXIT_SUCCESS};
    result += send_to_server();
    return result;
}
