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

std::string communicator::receive(const int &file_descriptor, sockaddr_in &address) const
{
    socklen_t address_length = 16;

    char buffer[COMMUNICATOR_BUFFER_SIZE];

    auto number_of_bytes_read = recvfrom(file_descriptor, reinterpret_cast<void*>(buffer), COMMUNICATOR_BUFFER_SIZE - 1, 0,
                                         reinterpret_cast<struct sockaddr*>(&address), &address_length);

    if (-1 == number_of_bytes_read)
        throw std::runtime_error(ERROR_STRING_BY_ERRNO);

    buffer[number_of_bytes_read] = '\0';

    return std::string(buffer);
}

void communicator::send(const int &file_descriptor, const std::string &str, sockaddr_in &address) const
{
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
