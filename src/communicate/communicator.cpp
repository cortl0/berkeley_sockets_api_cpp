/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#include "communicator.h"

#include <string.h>

namespace communicate
{

communicator::~communicator()
{
    close();
}

int communicator::accept(address* remote)
{
    int new_file_descriptor = ::accept(file_descriptor, nullptr, nullptr);

    if(socket_error == new_file_descriptor)
        log(ERROR_STRING_BY_ERRNO_WITH_PLACE);

    return new_file_descriptor;
}

bool communicator::bind(address local)
{
    if(socket_error == ::bind(file_descriptor, &local.address_.sockaddr_, local.length))
    {
        log(ERROR_STRING_BY_ERRNO_WITH_PLACE);
        return false;
    }

    return true;
}

bool communicator::close()
{
    return close(file_descriptor);
}

bool communicator::close(int file_descriptor)
{
    if(socket_error == ::close(file_descriptor))
    {
        log(ERROR_STRING_BY_ERRNO_WITH_PLACE);
        return false;
    }

    return true;
}

bool communicator::connect(address remote)
{
    if(socket_error == ::connect(file_descriptor, &remote.address_.sockaddr_, remote.length))
    {
        log(ERROR_STRING_BY_ERRNO_WITH_PLACE);
        return false;
    }

    return true;
}

bool communicator::shutdown(int file_descriptor)
{
    if(socket_error == ::shutdown(file_descriptor, SHUT_RDWR))
    {
        log(ERROR_STRING_BY_ERRNO_WITH_PLACE);
        return false;
    }

    return true;
}

bool communicator::listen()
{
    if(socket_error == ::listen(file_descriptor, 10))
    {
        log(ERROR_STRING_BY_ERRNO_WITH_PLACE);
        return false;
    }

    return true;
}

bool communicator::socket(int type, int protocol)
{
    if(socket_error == (file_descriptor = ::socket(PF_INET, type, protocol)))
    {
        log(ERROR_STRING_BY_ERRNO_WITH_PLACE);
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
    ssize_t number_of_bytes = ::recv(file_descriptor, b.data, buffer_size, 0);

    if(socket_error == number_of_bytes)
    {
        log(ERROR_STRING_BY_ERRNO_WITH_PLACE);
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
    ssize_t number_of_bytes = ::recvfrom(file_descriptor, b.data, buffer_size, 0, &a.address_.sockaddr_, &a.length);

    if(socket_error == number_of_bytes)
    {
        log(ERROR_STRING_BY_ERRNO_WITH_PLACE);
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

    if(socket_error == number_of_bytes)
        log(ERROR_STRING_BY_ERRNO_WITH_PLACE);

    return number_of_bytes;
}

ssize_t communicator::send(int file_descriptor, const buffer& b, const address& a) const
{
    ssize_t number_of_bytes = ::sendto(file_descriptor, b.data, b.size, 0, &a.address_.sockaddr_, a.length);

    if(socket_error == number_of_bytes)
        log(ERROR_STRING_BY_ERRNO_WITH_PLACE);

    return number_of_bytes;
}

} // namespace communicate
