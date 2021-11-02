/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

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

    stopped = false;

    struct sockaddr_in sender_address;

    try
    {
        while (!stop)
        {
            std::string str;

            std::getline(std::cin, str);

            if(str == "stop")
            {
                stop = true;
                break;
            }

            send(file_descriptor, str, address);

            std::cout << receive(file_descriptor, sender_address) << std::endl;
        }

        if (-1 == shutdown(file_descriptor, SHUT_RDWR))
            throw std::runtime_error(ERROR_STRING_BY_ERRNO);

        stopped = true;
    }
    catch (...)
    {
        stopped = true;
        throw ;
    }
}

}
