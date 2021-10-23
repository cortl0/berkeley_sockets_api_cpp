#include "udp_client.h"

namespace communicate
{

udp_client::~udp_client()
{

}

udp_client::udp_client(uint server_addres, ushort server_port) : communicator(PF_INET, SOCK_DGRAM, IPPROTO_UDP)
{
    address.sin_addr.s_addr = htonl(server_addres);
    address.sin_port = htons(server_port);
}

void udp_client::start(bool &stop)
{
    while (!stop)
    {
        std::string str;

        std::getline(std::cin, str);

        send(file_descriptor, str, address);

        std::cout << receive(file_descriptor, sender_address) << std::endl;
    }
}

}
