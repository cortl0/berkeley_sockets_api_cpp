#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "communicator.h"

namespace communicate
{

class tcp_server : public communicator
{
public:
    virtual ~tcp_server();
    tcp_server(ushort port);
    virtual void start(bool& stop);
};

}

#endif // TCP_SERVER_H
