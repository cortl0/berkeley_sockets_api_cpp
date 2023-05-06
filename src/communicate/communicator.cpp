/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "communicator.h"

namespace communicate
{

communicator::~communicator()
{
    close(file_descriptor);
}

communicator::communicator(int domain, int type, int protocol)
    : file_descriptor(socket(domain, type, protocol))
{
    if(file_descriptor == -1)
        throw std::runtime_error(ERROR_STRING_BY_ERRNO);

    address.sin_family = PF_INET;
}

bool communicator::is_stopped()
{
    return stopped;
}

ssize_t communicator::receive(int file_descriptor, buffer& b, sockaddr_in& address) const
{
    socklen_t address_length = 16;

    ssize_t number_of_bytes_read = recvfrom(file_descriptor, b.data, b.size, 0,
                                            reinterpret_cast<struct sockaddr*>(&address), &address_length);

    if(-1 == number_of_bytes_read)
        std::cerr << ERROR_STRING_BY_ERRNO << std::endl;

    return number_of_bytes_read;
}

ssize_t communicator::send(int file_descriptor, const buffer& b, const sockaddr_in& address) const
{
    if(COMMUNICATOR_BUFFER_SIZE <= b.size)
        throw std::runtime_error(ERROR_STRING_BY_ERRNO);

    ssize_t number_of_bytes_sent = sendto(
                file_descriptor,
                b.data,
                b.size,
                0,
                reinterpret_cast<const struct sockaddr*>(&address),
                sizeof(struct sockaddr_in)
            );

    if(-1 == number_of_bytes_sent)
        std::cerr << ERROR_STRING_BY_ERRNO << std::endl;

    return number_of_bytes_sent;
}

} // namespace communicate
