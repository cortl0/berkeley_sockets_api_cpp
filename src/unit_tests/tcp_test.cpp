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

#include "communicate/tcp/client.h"
#include "communicate/tcp/server.h"

int main()
{
    const auto s = std::string("12345");

    communicate::buffer b;
    b.buffer_set(b, s);
    bool stop{false};

    communicate::tcp_server tcp_server;
    communicate::tcp_client tcp_client;
    ASSERT_TRUE(tcp_server.initialize(config.tcp_server_port));

    std::thread([&]()
    {
        tcp_server.start(stop);
    }).detach();

    ASSERT_TRUE(tcp_client.initialize(LOCALHOST_ADDRESS, config.tcp_server_port));
    tcp_client.send(b);

    std::string ss;
    std::cin >> ss;

    return EXIT_SUCCESS;
}
