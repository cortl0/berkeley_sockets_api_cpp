/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#ifndef COMMUNICATE_TCP_CLIENT_H
#define COMMUNICATE_TCP_CLIENT_H

#include "communicate/communicator.h"

namespace communicate
{

class tcp_client
{
public:
    ~tcp_client();
    bool initialize(uint server_addres, ushort server_port);
    void send(buffer& b);

private:
    communicator communicator_;
};

} // namespace communicate

#endif // COMMUNICATE_TCP_CLIENT_H
