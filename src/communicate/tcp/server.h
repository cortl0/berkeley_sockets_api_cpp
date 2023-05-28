/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#ifndef COMMUNICATE_TCP_SERVER_H
#define COMMUNICATE_TCP_SERVER_H

#include "communicate/communicator.h"

namespace communicate::tcp
{

class server : public communicator
{
public:
    ~server();
    bool initialize(address local);
    bool start(bool& stop);
};

} // namespace communicate::tcp

#endif // COMMUNICATE_TCP_SERVER_H
