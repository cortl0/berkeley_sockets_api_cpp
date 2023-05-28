/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#include "communicate/tcp/server.h"

#include <iostream>
#include <thread>

namespace communicate::tcp
{

server::~server()
{
}

bool server::initialize(address local)
{
    log = [](const std::string& s){ std::cout << s << std::endl; };

    if(!socket(SOCK_STREAM, IPPROTO_TCP))
        return false;

    if(!bind(local))
        return false;

    if(!listen())
        return false;

    return true;
}

bool server::start(bool& stop)
{
    using namespace std::chrono_literals;

    while(!stop)
    {
        int new_file_descriptor = accept();

        if(socket_error == new_file_descriptor)
            return false;

        std::thread([&]()
        {
            int file_descriptor = new_file_descriptor;

            while(!stop)
            {
                buffer b;
                ssize_t number_of_bytes = receive(file_descriptor, b);

                if(socket_error == number_of_bytes)
                    break;

                if(0 < number_of_bytes)
                {
                    number_of_bytes = send(file_descriptor, b);

                    if(socket_error == number_of_bytes)
                        break;
                }
            }

            shutdown(file_descriptor);
            close(file_descriptor);
        }).detach();
    }

    return true;
}

} // namespace communicate::tcp
