/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#include "communicate/tcp/client.h"

#include <iostream>
#include <thread>

namespace communicate::tcp
{

client::~client()
{
    // if(-1 == shutdown(communicator_.file_descriptor, SHUT_RDWR))
    //     communicator_.log(ERROR_STRING_BY_ERRNO);
}

bool client::initialize(address local, address remote)
{
    communicator_.log = [](const std::string& s){ std::cout << s << std::endl; };

    if(!communicator_.initialize(SOCK_STREAM, IPPROTO_TCP))
        return false;

    if(-1 == connect(communicator_.file_descriptor, &remote.address_.sockaddr_, remote.length))
        return false;

    return true;
}

} // namespace communicate::tcp
