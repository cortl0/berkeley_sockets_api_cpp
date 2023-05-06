/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include "../business_logic/business_logic.h"
#include "udp_client.h"

namespace communicate
{

udp_client::~udp_client()
{

}

udp_client::udp_client(uint server_addres, ushort server_port) : communicator(PF_INET, SOCK_DGRAM, IPPROTO_UDP)
{
    address.sin_addr.s_addr = htonl(server_addres);
    address.sin_port = htons(server_port);
}

void udp_client::start(bool& stop)
{
    struct sockaddr_in sender_address;

    stopped = false;

    try
    {
        while(!stop)
        {
            buffer b;
            business_logic::business_logic::input(b);
            send(file_descriptor, b, address);
            ssize_t number_of_bytes_resived = receive(file_descriptor, b, sender_address);
            business_logic::business_logic::output(b, number_of_bytes_resived);
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
