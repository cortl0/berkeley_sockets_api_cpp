/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#include "communicate/udp/peer.h"

#include <iostream>

namespace communicate::udp
{

peer::~peer()
{
}

bool peer::initialize(address* local)
{
    log = [](const std::string& s){ std::cout << s << std::endl; };

    if(!socket(SOCK_DGRAM, IPPROTO_UDP))
        return false;

    if(local && !bind(*local))
        return false;

    return true;
}

} // namespace communicate::udp
