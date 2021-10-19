#include <thread>

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

    if (-1 == bind(file_descriptor, reinterpret_cast<struct sockaddr*>(&address), sizeof(struct sockaddr)))
        throw std::runtime_error(ERROR_STRING_BY_ERRNO);
}

void udp_server::start(bool& stop)
{
    while (!stop)
    {
        struct sockaddr_in address;

        std::string str(receive(file_descriptor, address));

        bool ok = false;

        std::thread([&]()
        {
            try
            {
                std::string str_(str);

                struct sockaddr_in address_ = address;

                ok = true;

                std::cout << "udp <<< " << str_ << std::endl;

                str_ = business_logic::business_logic::calculate(str_);

                send(file_descriptor, str_, address_);

                std::cout << "udp >>> " << str_ << std::endl;
            } catch (...) { }
        }).detach();

        while(!ok)
            usleep(10);
    }
}

}
