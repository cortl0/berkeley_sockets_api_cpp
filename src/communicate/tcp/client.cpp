/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#include "communicate/tcp/client.h"

#include <iostream>

namespace communicate::tcp
{

client::~client()
{
}

bool client::initialize(address* local, address remote)
{
    log = [](const std::string& s){ std::cout << s << std::endl; };

    if(!socket(SOCK_STREAM, IPPROTO_TCP))
        return false;

    if(local && !bind(*local))
        return false;

    if(!connect(remote))
        return false;

    return true;
}

} // namespace communicate::tcp
