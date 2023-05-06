/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "communicator.h"

namespace communicate
{

class tcp_client final : public communicator
{
public:
    ~tcp_client() final;
    explicit tcp_client(uint server_addres, ushort server_port);
    void start(bool& stop) final;
};

}

#endif // TCP_CLIENT_H
