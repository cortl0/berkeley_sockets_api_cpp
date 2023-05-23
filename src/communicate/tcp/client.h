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

namespace communicate::tcp
{

class client
{
public:
    ~client();
    bool initialize(address local, address remote);
    void send(buffer&);
    void send(buffer&, address&);

private:
    communicator communicator_;
};

} // namespace communicate::tcp

#endif // COMMUNICATE_TCP_CLIENT_H
