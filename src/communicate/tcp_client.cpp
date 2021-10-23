#include "tcp_client.h"

namespace communicate
{

tcp_client::~tcp_client()
{

}

tcp_client::tcp_client(uint server_addres, ushort server_port) : communicator(PF_INET, SOCK_STREAM, IPPROTO_TCP)
{
    address.sin_addr.s_addr = htonl(server_addres);
    address.sin_port = htons(server_port);
}

void tcp_client::start(bool &stop)
{
    if (-1 == connect(file_descriptor, reinterpret_cast<struct sockaddr*>(&address), sizeof(struct sockaddr_in)))
        throw std::runtime_error(ERROR_STRING_BY_ERRNO);

    while (!stop)
    {
        std::string str;

        std::getline(std::cin, str);

        send(file_descriptor, str, address);

        std::cout << receive(file_descriptor, sender_address) << std::endl;
    }
}

}
