#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include "communicator.h"

namespace communicate
{

class udp_client : public communicator
{
public:
    virtual ~udp_client();
    udp_client(uint server_addres, ushort server_port);
    virtual void start(bool& stop);
};

}

#endif // UDP_CLIENT_H
