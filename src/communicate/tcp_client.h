#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "communicator.h"

namespace communicate
{

class tcp_client : public communicator
{
public:
    virtual ~tcp_client();
    tcp_client(uint server_addres, ushort server_port);
    virtual void start(bool &stop);
};

}

#endif // TCP_CLIENT_H
