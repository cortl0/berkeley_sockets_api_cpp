/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#ifndef COMMUNICATE_UDP_SERVER_H
#define COMMUNICATE_UDP_SERVER_H

#include "communicate/communicator.h"

namespace communicate::udp
{

class server
{
public:
    ~server();
    bool initialize(address local, address remote);
    void start(bool& stop);

private:
    communicator communicator_;
};

} // namespace communicate::udp

#endif // COMMUNICATE_UDP_SERVER_H
