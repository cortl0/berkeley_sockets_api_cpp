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

bool client::initialize(uint server_addres, ushort server_port)
{
    if(!communicator_.initialize(PF_INET, SOCK_DGRAM, IPPROTO_UDP))
        return false;

    communicator_.address.sin_addr.s_addr = htonl(server_addres);
    communicator_.address.sin_port = htons(server_port);

    return true;
}

int client::send(/*sockaddr_in& address,*/ buffer& b)
{
    ssize_t number_of_bytes = communicator_.send(communicator_.file_descriptor, b, communicator_.address);

    if(-1 == number_of_bytes)
        std::cerr << ERROR_STRING_BY_ERRNO << std::endl;

    std::cout << "bytes sent: " << number_of_bytes << std::endl;

    return number_of_bytes;
}

} // namespace communicate::udp
