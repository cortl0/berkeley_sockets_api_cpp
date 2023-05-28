/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#include "address.h"

#include <arpa/inet.h>
#include <string.h>

namespace communicate
{

address::address()
{
    memset(&address_, 0, sizeof address_);
    address_.sockaddr_.sa_family = PF_INET;
}

address::address(const address& a)
{
    memset(&address_, 0, sizeof address_);
    address_.sockaddr_in_ = a.address_.sockaddr_in_;
}

void address::set_ip(const std::string& ip)
{
    int _ = inet_aton(ip.c_str(), &address_.sockaddr_in_.sin_addr);
}

void address::set_port(uint16_t port)
{
    address_.sockaddr_in_.sin_port = htons(port);
}

std::string address::to_string() const
{
    switch(length)
    {
    case lengths::sockaddr_in_len:
    {
        return std::string(inet_ntoa(address_.sockaddr_in_.sin_addr)) + ":" + std::to_string(htons(address_.sockaddr_in_.sin_port));
        break;
    }
    default:
        return "";
    }
}

} // namespace communicate
