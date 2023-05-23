/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include "communicator.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

namespace communicate
{

communicator::~communicator()
{
    close(file_descriptor);
}

bool communicator::initialize(int type, int protocol, address local, address remote)
{
    printf("local ");
    local.print();
    printf("remote ");
    remote.print();

    if(-1 == (file_descriptor = socket(local.address_.sockaddr_.sa_family, type, protocol)))
        return false;

    return true;
}

bool communicator::is_stopped()
{
    return stopped;
}

ssize_t communicator::receive(int file_descriptor, buffer& b, sockaddr_in& address) const
{
    socklen_t address_length = sizeof(struct sockaddr_in);

    ssize_t number_of_bytes = recvfrom(file_descriptor, b.data, buffer_size, 0,
        reinterpret_cast<struct sockaddr*>(&address), &address_length);

    if(-1 == number_of_bytes)
    {
        std::cerr << ERROR_STRING_BY_ERRNO << std::endl;
        b.size = 0;
    }
    else
    {
        b.size = number_of_bytes;
    }

    return number_of_bytes;
}

ssize_t communicator::send(int file_descriptor, const buffer& b, const sockaddr_in& address) const
{
    ssize_t number_of_bytes = sendto(file_descriptor, b.data, b.size, 0,
        reinterpret_cast<const struct sockaddr*>(&address), sizeof(struct sockaddr_in));

    if(-1 == number_of_bytes)
        std::cerr << ERROR_STRING_BY_ERRNO << std::endl;

    return number_of_bytes;
}

} // namespace communicate
