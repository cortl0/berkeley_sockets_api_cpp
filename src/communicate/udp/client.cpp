/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include "communicate/udp/client.h"

namespace communicate::udp
{

client::~client()
{

}

bool client::initialize(address local, address remote)
{
    printf("client:\n");

    if(!communicator_.initialize(SOCK_DGRAM, IPPROTO_UDP, local, remote))
        return false;

    return true;
}

int client::send(buffer& b, address& a)
{
    ssize_t number_of_bytes = communicator_.send(communicator_.file_descriptor, b, a.address_.sockaddr_in_);

    if(-1 == number_of_bytes)
        std::cerr << ERROR_STRING_BY_ERRNO << std::endl;

    std::cout << "bytes sent: " << number_of_bytes << std::endl;

    return number_of_bytes;
}

} // namespace communicate::udp
