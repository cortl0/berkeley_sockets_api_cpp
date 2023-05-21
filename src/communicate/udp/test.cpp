/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include <thread>

#include "unit_tests/common.h"
#include "config.h"
#include "communicate/buffer.h"

#include "communicate/udp/client.h"
#include "communicate/udp/server.h"

int main()
{
    const auto s = std::string("12345");

    communicate::buffer b;
    b.buffer_set(b, s);
    bool stop{false};
    communicate::udp_server udp_server;
    communicate::udp_client udp_client;
    ASSERT_TRUE(udp_server.initialize(config.udp_server_port));

    std::thread([&]()
    {
        udp_server.start(stop);
    }).detach();

    ASSERT_TRUE(udp_client.initialize(LOCALHOST_ADDRESS, config.udp_server_port));
    udp_client.send(b);

    return EXIT_SUCCESS;
}
