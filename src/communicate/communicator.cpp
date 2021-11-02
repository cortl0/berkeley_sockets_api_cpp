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
    if (file_descriptor == -1)
        throw std::runtime_error(ERROR_STRING_BY_ERRNO);

    address.sin_family = PF_INET;
}

bool communicator::is_stopped()
{
    return stopped;
}

std::string communicator::receive(const int &file_descriptor, sockaddr_in &address) const
{
    socklen_t address_length = 16;

    char buffer[COMMUNICATOR_BUFFER_SIZE];

    auto const number_of_bytes_read = recvfrom(file_descriptor, reinterpret_cast<void*>(buffer), COMMUNICATOR_BUFFER_SIZE - 1, 0,
                                               reinterpret_cast<struct sockaddr*>(&address), &address_length);

    if (1 > number_of_bytes_read)
        throw std::runtime_error(ERROR_STRING_BY_ERRNO);

    if (COMMUNICATOR_BUFFER_SIZE <= number_of_bytes_read)
        throw std::runtime_error(ERROR_STRING_BY_ERRNO);

    buffer[number_of_bytes_read] = '\0';

    return std::string(buffer);
}

void communicator::send(const int &file_descriptor, const std::string &str, sockaddr_in &address) const
{
    if (COMMUNICATOR_BUFFER_SIZE <= str.size())
        throw std::runtime_error(ERROR_STRING_BY_ERRNO);

    if (-1 == sendto(
                file_descriptor,
                str.c_str(),
                str.length() + 1,
                0,
                reinterpret_cast<struct sockaddr*>(&address),
                sizeof(struct sockaddr_in)
                ))
        throw std::runtime_error(ERROR_STRING_BY_ERRNO);
}

}
