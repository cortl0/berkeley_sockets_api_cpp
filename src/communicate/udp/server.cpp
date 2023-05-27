/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#include "communicate/udp/server.h"

#include <iostream>

namespace communicate::udp
{

server::~server()
{
}

bool server::initialize(address local, address remote)
{
    communicator_.log = [](const std::string& s){ std::cout << s << std::endl; };

    if(!communicator_.initialize(SOCK_DGRAM, IPPROTO_UDP))
        return false;

    if(-1 == bind(communicator_.file_descriptor, &local.address_.sockaddr_, local.length))
        return false;

    return true;
}

void server::start(bool& stop)
{
    address a;
    ssize_t number_of_bytes = 0;
    buffer b;

    do
    {
        number_of_bytes = communicator_.receive(b, a);

        if(-1 == number_of_bytes)
            continue;

        communicator_.log("bytes received: [" + std::to_string(b.size) + "] [" + std::string(b.data) + "]");

        number_of_bytes = communicator_.send(b, a);
    }
    while(number_of_bytes != -1);
}

} // namespace communicate::udp
