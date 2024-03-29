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
const std::string localhost{"127.0.0.1"};
const std::string server_ip{localhost};
const std::string client_ip{localhost};

int tcp_test()
{
    bool stop{false};

    communicate::address server_local_address;
#ifdef FULL_ADDRESS_TEST
    server_local_address.set_ip(server_ip);
#endif
    server_local_address.set_port(server_port);

    communicate::address client_local_address;
#ifdef FULL_ADDRESS_TEST
    client_local_address.set_ip(client_ip);
    client_local_address.set_port(client_port);
#endif

    communicate::address client_remote_address;
    client_remote_address.set_ip(server_ip);
    client_remote_address.set_port(server_port);

    communicate::tcp::server server;
    ASSERT_TRUE(server.initialize(server_local_address));
    std::thread([&](){ EXPECT_TRUE(server.start(stop)); }).detach();

    communicate::tcp::client client;
    ASSERT_TRUE(client.initialize(&client_local_address, client_remote_address));

    const auto etalon = std::string("123abc");
    communicate::buffer first_buffer;
    communicate::buffer second_buffer;
    first_buffer.from_string(etalon);

    ASSERT_TRUE(client.send(first_buffer) > 0);
    ASSERT_TRUE(client.receive(second_buffer) > 0);
    ASSERT_EQ(etalon, second_buffer.to_string());

    return EXIT_SUCCESS;
}

int main()
{
    int result{EXIT_SUCCESS};
    result += tcp_test();
    return result;
}
