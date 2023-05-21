/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include "udp_server.h"

namespace communicate
{

udp_server::~udp_server()
{

}

bool udp_server::initialize(ushort port)
{
    if(!communicator_.initialize(PF_INET, SOCK_DGRAM, IPPROTO_UDP))
        return false;

    communicator_.address.sin_addr.s_addr = htonl(INADDR_ANY);
    communicator_.address.sin_port = htons(port);

    if(-1 == bind(communicator_.file_descriptor, reinterpret_cast<struct sockaddr*>(&communicator_.address), sizeof(struct sockaddr)))
        return false;

    return true;
}

void udp_server::start(bool& stop)
{
    struct sockaddr_in address;
    ssize_t number_of_bytes = 0;
    buffer b;

    do
    {
        number_of_bytes = communicator_.receive(communicator_.file_descriptor, b, address);

        if(-1 == number_of_bytes)
            continue;

        std::cout << "count of bytes received: " << b.size << std::endl;

        number_of_bytes = communicator_.send(communicator_.file_descriptor, b, address);
    }
    while(number_of_bytes != -1);
}

} // namespace communicate
