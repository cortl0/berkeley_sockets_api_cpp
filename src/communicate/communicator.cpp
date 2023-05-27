/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
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

bool communicator::initialize(int type, int protocol)
{
    if(-1 == (file_descriptor = socket(PF_INET, type, protocol)))
    {
        log(ERROR_STRING_BY_ERRNO);
        return false;
    }

    return true;
}

ssize_t communicator::receive(buffer& b) const
{
    return receive(file_descriptor, b);
}

ssize_t communicator::receive(buffer& b, address& a) const
{
    return receive(file_descriptor, b, a);
}

ssize_t communicator::receive(int file_descriptor, buffer& b) const
{
    ssize_t number_of_bytes = recv(file_descriptor, b.data, buffer_size, 0);

    if(-1 == number_of_bytes)
    {
        log(ERROR_STRING_BY_ERRNO);
        b.size = 0;
    }
    else
    {
        b.size = number_of_bytes;
    }

    return number_of_bytes;
}

ssize_t communicator::receive(int file_descriptor, buffer& b, address& a) const
{
    ssize_t number_of_bytes = recvfrom(file_descriptor, b.data, buffer_size, 0, &a.address_.sockaddr_, &a.length);

    if(-1 == number_of_bytes)
    {
        log(ERROR_STRING_BY_ERRNO);
        b.size = 0;
    }
    else
    {
        b.size = number_of_bytes;
    }

    return number_of_bytes;
}

ssize_t communicator::send(const buffer& b) const
{
    return send(file_descriptor, b);
}

ssize_t communicator::send(const buffer& b, const address& a) const
{
    return send(file_descriptor, b, a);
}

ssize_t communicator::send(int file_descriptor, const buffer& b) const
{
    ssize_t number_of_bytes = ::send(file_descriptor, b.data, (size_t)b.size, 0);

    if(-1 == number_of_bytes)
        log(ERROR_STRING_BY_ERRNO);

    return number_of_bytes;
}

ssize_t communicator::send(int file_descriptor, const buffer& b, const address& a) const
{
    ssize_t number_of_bytes = sendto(file_descriptor, b.data, b.size, 0, &a.address_.sockaddr_, a.length);

    if(-1 == number_of_bytes)
        log(ERROR_STRING_BY_ERRNO);

    return number_of_bytes;
}

} // namespace communicate
