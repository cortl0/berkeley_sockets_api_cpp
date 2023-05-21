/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#ifndef COMMUNICATE_UDP_CLIENT_H
#define COMMUNICATE_UDP_CLIENT_H

#include "communicate/communicator.h"

namespace communicate::udp
{

class client
{
public:
    ~client();
    bool initialize(uint server_addres, ushort server_port);
    int send(buffer& b);

private:
    communicator communicator_;
};

} // namespace communicate::udp

#endif // COMMUNICATE_UDP_CLIENT_H
