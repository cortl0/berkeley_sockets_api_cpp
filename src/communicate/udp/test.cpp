/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#include <iostream>
#include <thread>

#include "communicate/udp/peer.h"
#include "unit_tests/common.h"

constexpr uint16_t receiver_port{60003};
constexpr uint16_t sender_port{60004};
const std::string localhost{"127.0.0.1"};
const std::string receiver_ip{localhost};
const std::string sender_ip{localhost};

int udp_test()
{
    communicate::address receiver_local_address;
#ifdef FULL_ADDRESS_TEST
    receiver_local_address.set_ip(receiver_ip);
#endif
    receiver_local_address.set_port(receiver_port);

    communicate::address sender_local_address;
#ifdef FULL_ADDRESS_TEST
    sender_local_address.set_ip(sender_ip);
    sender_local_address.set_port(sender_port);
#endif

    communicate::address sender_remote_address;
    sender_remote_address.set_ip(receiver_ip);
    sender_remote_address.set_port(receiver_port);

    communicate::udp::peer reciever;
    ASSERT_TRUE(reciever.initialize(&receiver_local_address));

    communicate::udp::peer sender;
    ASSERT_TRUE(sender.initialize(&sender_local_address));

    const auto etalon = std::string("123abc");
    communicate::buffer first_buffer;
    communicate::buffer second_buffer;
    first_buffer.from_string(etalon);

    ASSERT_TRUE(sender.send(first_buffer, sender_remote_address) > 0);
    ASSERT_TRUE(reciever.receive(second_buffer) > 0);
    ASSERT_EQ(etalon, second_buffer.to_string());

    return EXIT_SUCCESS;
}

int main()
{
    int result{EXIT_SUCCESS};
    result += udp_test();
    return result;
}
