/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include "communicate/udp/server.h"

namespace communicate::udp
{

server::~server()
{

}

bool server::initialize(address local, address remote)
{
    printf("server:\n");

    if(!communicator_.initialize(SOCK_DGRAM, IPPROTO_UDP, local, remote))
        return false;

    return true;
}

void server::start(bool& stop)
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

} // namespace communicate::udp
