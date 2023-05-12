/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include "application.h"

#include <algorithm>
#include <list>
#include <thread>
#include <string.h>
#include <unistd.h>

#include "communicate/buffer_tools.h"

#include "communicate/udp_client.h"
#include "communicate/udp_server.h"
#include "communicate/tcp_client.h"
#include "communicate/tcp_server.h"

static bool stop = false;

static std::list<std::shared_ptr<communicate::communicator>> communicators;

void usage()
{
    std::cout << "Usage:" << std::endl << std::endl;
    std::cout << "\tberkeley_sockets [key]" << std::endl << std::endl;
    std::cout << "\tKeys:" << std::endl;
    std::cout << "\t\thelp                 - this help" << std::endl;
    std::cout << "\t\ttcp server           - run TCP server" << std::endl;
    std::cout << "\t\ttcp client <message> - run TCP client and send message" << std::endl;
    std::cout << "\t\tudp server           - run UDP server" << std::endl;
    std::cout << "\t\tudp client <message> - run UDP client and send message" << std::endl;
}

application::~application()
{
    while(std::any_of(communicators.begin(), communicators.end(),
                      [&](const std::shared_ptr<communicate::communicator>& c)
    { return !c->is_stopped(); }))
        sleep(1);
}

void application::run(int argc, char *argv[])
{
    if(0 == strcmp(argv[1], "udp"))
    {
        if(0 == strcmp(argv[2], "client"))
        {
            communicate::udp_client udp_client;

            if(!udp_client.initialize(LOCALHOST_ADDRESS, UDP_SERVER_PORT))
                return;

            communicate::buffer b;
            auto s = std::string(argv[3]);
            communicate::buffer_set(b, s);
            udp_client.send(b);
        }
        else if(0 == strcmp(argv[2], "server"))
        {
            std::thread([&]()
            {
                communicate::udp_server udp_server;

                if(!udp_server.initialize(UDP_SERVER_PORT))
                    return;

                udp_server.start(stop);
            }).detach();

            std::cin >> argc;
            stop = true;
        }
        else
        {
            std::cerr << "error: " << "wrong argv" + WHERE_ERROR << std::endl;

            usage();
        }
    }
    else if(0 == strcmp(argv[1], "tcp"))
    {
        if(0 == strcmp(argv[2], "client"))
        {
            communicate::tcp_client tcp_client;

            if(!tcp_client.initialize(LOCALHOST_ADDRESS, TCP_SERVER_PORT))
                return;

            communicate::buffer b;
            auto s = std::string(argv[3]);
            communicate::buffer_set(b, s);
            tcp_client.send(b);
        }
        else if(0 == strcmp(argv[2], "server"))
        {
            std::thread([&]()
            {
                communicate::tcp_server tcp_server;

                if(!tcp_server.initialize(TCP_SERVER_PORT))
                    return;

                tcp_server.start(stop);
            }).detach();

            std::cin >> argc;
            stop = true;
        }
        else
        {
            std::cerr << "error: " << "wrong argv" + WHERE_ERROR << std::endl;

            usage();
        }
    }
    else if(0 == strcmp(argv[1], "help"))
    {
        usage();
    }
    else
    {
        std::cerr << "error: " << "wrong argv" + WHERE_ERROR << std::endl;

        usage();
    }
}
