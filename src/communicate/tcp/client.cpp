/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include "communicate/tcp/client.h"

namespace communicate
{

tcp_client::~tcp_client()
{

}

bool tcp_client::initialize(uint server_addres, ushort server_port)
{
    if(!communicator_.initialize(PF_INET, SOCK_STREAM, IPPROTO_TCP))
        return false;

    communicator_.address.sin_addr.s_addr = htonl(server_addres);
    communicator_.address.sin_port = htons(server_port);

    if(-1 == connect(communicator_.file_descriptor, reinterpret_cast<struct sockaddr*>(&communicator_.address), sizeof(struct sockaddr_in)))
        return false;

    return true;
}

void tcp_client::send(buffer& b)
{
    communicator_.stopped = false;
    struct sockaddr_in sender_address;
    communicator_.send(communicator_.file_descriptor, b, communicator_.address);
    ssize_t number_of_bytes = communicator_.receive(communicator_.file_descriptor, b, sender_address);

    if(-1 == shutdown(communicator_.file_descriptor, SHUT_RDWR))
        std::cerr << ERROR_STRING_BY_ERRNO << std::endl;

    communicator_.stopped = true;
}

} // namespace communicate
