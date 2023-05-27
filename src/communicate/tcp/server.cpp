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
    communicator_.log = [](const std::string& s){ std::cout << s << std::endl; };

    if(!communicator_.initialize(SOCK_STREAM, IPPROTO_TCP))
        return false;

    if(-1 == bind(communicator_.file_descriptor, &local.address_.sockaddr_, local.length))
        return false;

    if(-1 == listen(communicator_.file_descriptor, 10))
    {
        communicator_.log(ERROR_STRING_BY_ERRNO);
        return false;
    }

    return true;
}

void server::start(bool& stop)
{
    using namespace std::chrono_literals;

    while(!stop)
    {
        int connect_file_descriptor = accept(communicator_.file_descriptor, nullptr, nullptr);

        if(-1 == connect_file_descriptor)
        {
            communicator_.log(ERROR_STRING_BY_ERRNO);
            break;
        }

        if(stop)
        {
            shutdown(connect_file_descriptor, SHUT_RDWR);

            close(connect_file_descriptor);

            break;
        }

        bool ok = false;

        std::thread([&]()
        {
            try
            {
                int connect_file_descriptor_ = connect_file_descriptor;
                ok = true;
                address a;

                while(!stop)
                {
                    buffer b;
                    ssize_t number_of_bytes = communicator_.receive(connect_file_descriptor_, b);

                    if(-1 == number_of_bytes)
                    {
                        communicator_.log(ERROR_STRING_BY_ERRNO);
                        break;
                    }

                    if(0 < number_of_bytes)
                    {
                        number_of_bytes = communicator_.send(connect_file_descriptor_, b);

                        if(-1 == number_of_bytes)
                        {
                            communicator_.log(ERROR_STRING_BY_ERRNO);
                            break;
                        }
                    }
                }

                shutdown(connect_file_descriptor_, SHUT_RDWR);
                close(connect_file_descriptor_);
            } catch(...) { }
        }).detach();

        while(!ok)
            usleep(10);
    }
}

} // namespace communicate::tcp
