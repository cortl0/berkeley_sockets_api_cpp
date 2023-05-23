/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include "communicate/tcp/client.h"

namespace communicate::tcp
{

client::~client()
{

}

bool client::initialize(address local, address remote)
{
    printf("client:\n");

    if(!communicator_.initialize(SOCK_STREAM, IPPROTO_TCP, local, remote))
        return false;

    if(-1 == connect(communicator_.file_descriptor, &remote.address_.sockaddr_, remote.length))
        return false;

    return true;
}

void client::send(buffer& b)
{
    communicator_.stopped = false;
    struct sockaddr_in sender_address;
    communicator_.send(communicator_.file_descriptor, b, communicator_.address5);
    ssize_t number_of_bytes = communicator_.receive(communicator_.file_descriptor, b, sender_address);

    if(-1 == shutdown(communicator_.file_descriptor, SHUT_RDWR))
        std::cerr << ERROR_STRING_BY_ERRNO << std::endl;

    communicator_.stopped = true;
}

void client::send(buffer& b, address& a)
{
    communicator_.stopped = false;
    struct sockaddr_in sender_address;
    communicator_.send(communicator_.file_descriptor, b, a.address_.sockaddr_in_);
    ssize_t number_of_bytes = communicator_.receive(communicator_.file_descriptor, b, sender_address);

    if(-1 == shutdown(communicator_.file_descriptor, SHUT_RDWR))
        std::cerr << ERROR_STRING_BY_ERRNO << std::endl;

    communicator_.stopped = true;
}

} // namespace communicate::tcp
