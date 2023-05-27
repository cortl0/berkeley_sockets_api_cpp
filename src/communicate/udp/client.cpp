/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#include "communicate/udp/client.h"

#include <iostream>

namespace communicate::udp
{

client::~client()
{
}

bool client::initialize(address local, address remote)
{
    communicator_.log = [](const std::string& s){ std::cout << s << std::endl; };

    if(!communicator_.initialize(SOCK_DGRAM, IPPROTO_UDP))
        return false;

    return true;
}

} // namespace communicate::udp
