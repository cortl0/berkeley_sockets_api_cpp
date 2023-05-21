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

int main()
{
    const auto s = std::string("12345");
    communicate::buffer b;
    b.buffer_set(b, s);

    communicate::udp::server server;
    ASSERT_TRUE(server.initialize(server_port));

    bool stop{false};
    std::thread([&]()
    {
        server.start(stop);
    }).detach();

    communicate::udp::client client;
    ASSERT_TRUE(client.initialize(localhost_address, server_port));
    client.send(b);

    return EXIT_SUCCESS;
}
