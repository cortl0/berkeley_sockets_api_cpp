/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "communicator.h"

namespace communicate
{

class tcp_server final : public communicator
{
public:
    ~tcp_server() final;
    explicit tcp_server(ushort port);
    bool get_stopped();
    void start(bool& stop) final;
};

}

#endif // TCP_SERVER_H
