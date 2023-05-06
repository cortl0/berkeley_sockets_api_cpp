/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include "udp_server.h"
#include "../business_logic/business_logic.h"

namespace communicate
{

udp_server::~udp_server()
{

}

udp_server::udp_server(ushort port) : communicator(PF_INET, SOCK_DGRAM, IPPROTO_UDP)
{
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);
}

bool udp_server::get_stopped()
{
    return stopped;
}

void udp_server::start(bool& stop)
{
    if(-1 == bind(file_descriptor, reinterpret_cast<struct sockaddr*>(&address), sizeof(struct sockaddr)))
        throw std::runtime_error(ERROR_STRING_BY_ERRNO);

    stopped = false;

    try
    {
        while(!stop)
        {
            struct sockaddr_in address;
            buffer b;
            receive(file_descriptor, b, address);

            if(!business_logic::business_logic::calculate(b, 1))
                continue;

            try
            {
                struct sockaddr_in address_ = address;
                send(file_descriptor, b, address_);
            } catch(...) { }
        }

        stopped = true;
    }
    catch(...)
    {
        stopped = true;
        throw ;
    }
}

}
