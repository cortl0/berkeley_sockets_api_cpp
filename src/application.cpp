/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include <algorithm>
#include <list>
#include <thread>
#include <string.h>
#include <unistd.h>

#include "application.h"

#include "communicate/udp_client.h"
#include "communicate/udp_server.h"
#include "communicate/tcp_client.h"
#include "communicate/tcp_server.h"

static bool stop = false;

static std::list<std::shared_ptr<communicate::communicator>> communicators;

void try_catch_wrapper(void (*action)())
{
    try
    {
        action();
    }
    catch (std::runtime_error e)
    {
        std::cerr << "error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "unknown error" << std::endl;
    }
}

void usage()
{
    std::cout << "Usage:" << std::endl << std::endl;
    std::cout << "\tberkeley_sockets [key]" << std::endl << std::endl;
    std::cout << "\tKeys:" << std::endl;
    std::cout << "\t\t--help         - this help" << std::endl;
    std::cout << "\t\ttcp            - run TCP client" << std::endl;
    std::cout << "\t\tudp            - run UDP client" << std::endl;
    std::cout << "\t\twithout key    - run TCP/UDP server" << std::endl << std::endl;
}

application::~application()
{
    while(std::any_of(communicators.begin(), communicators.end(),
                      [&](const std::shared_ptr<communicate::communicator> &c)
    { return !c->is_stopped(); }))
        sleep(1);
}

void application::run(int argc, char *argv[])
{
    switch (argc)
    {
    case 1:
    {
        std::cout << "server start" << std::endl;

        std::thread ([&]()
        {
            try_catch_wrapper([]()
            {
                communicators.push_back(
                            std::shared_ptr<communicate::communicator>(
                                new communicate::udp_server(UDP_SERVER_PORT)));

                communicators.back()->start(stop);
            });
        }).detach();

        std::thread ([&]()
        {
            try_catch_wrapper([]()
            {
                communicators.push_back(
                            std::shared_ptr<communicate::communicator>(
                                new communicate::tcp_server(TCP_SERVER_PORT)));

                communicators.back()->start(stop);
            });
        }).detach();

        std::cin >> argc;

        stop = true;

        break;
    }

    case 2:
    {
        if(0 == strcmp(argv[1], "udp"))
        {
            std::cout << "udp client start" << std::endl;

            try_catch_wrapper([]()
            {
                communicators.push_back(
                            std::shared_ptr<communicate::communicator>(
                                new communicate::udp_client(LOCALHOST_ADDRESS, UDP_SERVER_PORT)));

                communicators.back()->start(stop);
            });
        }
        else if(0 == strcmp(argv[1], "tcp"))
        {
            std::cout << "tcp client start" << std::endl;

            try_catch_wrapper([]()
            {
                communicators.push_back(
                            std::shared_ptr<communicate::communicator>(
                                new communicate::tcp_client(LOCALHOST_ADDRESS, TCP_SERVER_PORT)));

                communicators.back()->start(stop);
            });
        }
        else if(0 == strcmp(argv[1], "--help"))
        {
            usage();
        }
        else
        {
            std::cerr << "error: " << "wrong argv" + WHERE_ERROR << std::endl;

            usage();
        }

        break;
    }

    default:
    {
        std::cerr << "error: " << "wrong argc" + WHERE_ERROR << std::endl;

        usage();

        break;
    }
    }
}



