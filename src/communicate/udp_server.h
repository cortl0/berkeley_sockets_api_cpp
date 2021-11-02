/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include "communicator.h"

namespace communicate
{

class udp_server final : public communicator
{
public:
    virtual ~udp_server() override;
    udp_server(ushort port);
    bool get_stopped();
    virtual void start(bool &stop) final;
};

}

#endif // UDP_SERVER_H
