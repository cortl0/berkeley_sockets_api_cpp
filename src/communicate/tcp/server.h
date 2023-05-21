/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#ifndef COMMUNICATE_TCP_SERVER_H
#define COMMUNICATE_TCP_SERVER_H

#include "communicate/communicator.h"

namespace communicate::tcp
{

class server
{
public:
    ~server();
    bool initialize(ushort port);
    void start(bool& stop);

private:
    communicator communicator_;
};

} // namespace communicate::tcp

#endif // COMMUNICATE_TCP_SERVER_H
