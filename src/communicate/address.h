/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#ifndef COMMUNICATE_ADDRESS_H
#define COMMUNICATE_ADDRESS_H

#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#include <string>

namespace communicate
{

class address
{
public:
    address()
    {
        memset(&address_, 0, sizeof address_);
        address_.sockaddr_.sa_family = PF_INET;
    }

    address(const address& a)
    {
        memset(&address_, 0, sizeof address_);
        address_.sockaddr_in_ = a.address_.sockaddr_in_;
    }

    void set_ip(const std::string& ip)
    {
        int _ = inet_aton(ip.c_str(), &address_.sockaddr_in_.sin_addr);
    }

    void set_port(uint16_t port)
    {
        address_.sockaddr_in_.sin_port = htons(port);
    }

    std::string to_string() const
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

    union
    {
        sockaddr sockaddr_;
        sockaddr_in sockaddr_in_;
        sockaddr_in6 sockaddr_in6_;
    } address_;

    enum lengths : socklen_t
    {
        sockaddr_len = sizeof(sockaddr),
        sockaddr_in_len = sizeof(sockaddr_in),
        sockaddr_in6_len = sizeof(sockaddr_in6),
    };

    socklen_t length{lengths::sockaddr_in_len};
};

} // namespace communicate

#endif // COMMUNICATE_ADDRESS_H
