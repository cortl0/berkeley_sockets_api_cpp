/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include "communicate/tcp/server.h"

#include <thread>

namespace communicate::tcp
{

server::~server()
{

}

bool server::initialize(address local, address remote)
{
    printf("server:\n");

    if(!communicator_.initialize(SOCK_STREAM, IPPROTO_TCP, local, remote))
        return false;

    if(-1 == bind(communicator_.file_descriptor, reinterpret_cast<struct sockaddr*>(&local), local.length))
        return false;

    if(-1 == listen(communicator_.file_descriptor, 10))
    {
        std::cerr << ERROR_STRING_BY_ERRNO << std::endl;
        return false;
    }

    return true;
}

void server::start(bool& stop)
{
    using namespace std::chrono_literals;

    communicator_.stopped = false;

    while(!stop)
    {
        int connect_file_descriptor = accept(communicator_.file_descriptor, nullptr, nullptr);

        if(-1 == connect_file_descriptor)
            throw std::runtime_error(ERROR_STRING_BY_ERRNO);

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
                struct sockaddr_in address;

                while(!stop)
                {
                    buffer b;
                    ssize_t number_of_bytes = communicator_.receive(connect_file_descriptor_, b, address);

                    if(-1 == number_of_bytes)
                        break;

                    if(0 < number_of_bytes)
                        std::cout << "count of bytes received: " << b.size << std::endl;
                    else
                        std::this_thread::sleep_for(10ms);

                    number_of_bytes = communicator_.send(connect_file_descriptor_, b, address);

                    if(-1 == number_of_bytes)
                        break;
                }

                shutdown(connect_file_descriptor_, SHUT_RDWR);
                close(connect_file_descriptor_);
            } catch(...) { }

        }).detach();

        while(!ok)
            usleep(10);
    }

    communicator_.stopped = true;
}

} // namespace communicate::tcp
