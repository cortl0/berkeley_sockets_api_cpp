/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include "communicator.h"

namespace communicate
{

class udp_client final : public communicator
{
public:
    ~udp_client() final;
    explicit udp_client(uint server_addres, ushort server_port);
    void start(bool& stop) final;
};

}

#endif // UDP_CLIENT_H
