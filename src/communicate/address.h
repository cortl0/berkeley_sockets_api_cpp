/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#ifndef COMMUNICATE_ADDRESS_H
#define COMMUNICATE_ADDRESS_H

#include <netinet/in.h>

#include <string>

namespace communicate
{

struct address
{
    enum lengths : socklen_t
    {
        sockaddr_len = sizeof(sockaddr),
        sockaddr_in_len = sizeof(sockaddr_in),
        sockaddr_in6_len = sizeof(sockaddr_in6),
    };

    union
    {
        sockaddr sockaddr_;
        sockaddr_in sockaddr_in_;
        sockaddr_in6 sockaddr_in6_;
    } address_;

    socklen_t length{lengths::sockaddr_in_len};

    address();
    address(const address& a);
    void set_ip(const std::string& ip);
    void set_port(uint16_t port);
    std::string to_string() const;
};

} // namespace communicate

#endif // COMMUNICATE_ADDRESS_H
