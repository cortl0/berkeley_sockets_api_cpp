/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#ifndef COMMUNICATE_UDP_SERVER_H
#define COMMUNICATE_UDP_SERVER_H

#include "communicate/communicator.h"

namespace communicate::udp
{

class server : public communicator
{
public:
    ~server();
    bool initialize(address local);
};

} // namespace communicate::udp

#endif // COMMUNICATE_UDP_SERVER_H
