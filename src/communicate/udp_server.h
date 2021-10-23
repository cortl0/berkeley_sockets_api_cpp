#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include "communicator.h"

namespace communicate
{

class udp_server : public communicator
{
public:
    virtual ~udp_server();
    udp_server(ushort port);
    virtual void start(bool &stop);
};

}

#endif // UDP_SERVER_H
