/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include <thread>

#include "tcp_server.h"
#include "../business_logic/business_logic.h"

namespace communicate
{

tcp_server::~tcp_server()
{

}

tcp_server::tcp_server(ushort port) : communicator(PF_INET, SOCK_STREAM, IPPROTO_TCP)
{
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);
}

bool tcp_server::get_stopped()
{
    return stopped;
}

void tcp_server::start(bool &stop)
{
    if (-1 == bind(file_descriptor, reinterpret_cast<struct sockaddr*>(&address), sizeof(struct sockaddr)))
        throw std::runtime_error(ERROR_STRING_BY_ERRNO);

    if (-1 == listen(file_descriptor, 10))
        throw std::runtime_error(ERROR_STRING_BY_ERRNO);

    stopped = false;

    try
    {
        while (!stop)
        {
            int connect_file_descriptor = accept(file_descriptor, nullptr, nullptr);

            if (-1 == connect_file_descriptor)
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

                    while (!stop)
                    {
                        std::string str(receive(connect_file_descriptor_, address));

                        if(str.size() == 0)
                            continue;

                        std::cout << "tcp <<< " << str << std::endl;

                        str = business_logic::business_logic::calculate(str);

                        send(connect_file_descriptor_, str, address);

                        std::cout << "tcp >>> " << str << std::endl;
                    }

                    shutdown(connect_file_descriptor_, SHUT_RDWR);

                    close(connect_file_descriptor_);
                } catch (...) { }

            }).detach();

            while(!ok)
                usleep(10);
        }

        stopped = true;
    }
    catch (...)
    {
        stopped = true;
        throw ;
    }
}

}
