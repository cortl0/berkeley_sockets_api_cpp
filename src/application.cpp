#include <thread>

#include "application.h"

void application::run(int argc, char *argv[])
{
    bool stop = false;

    switch (argc)
    {
    case 1:
    {
        std::cout << "server start" << std::endl;

        std::thread ([&]()
        {
            communicate::udp_server comm(UDP_SERVER_PORT);

            comm.start(stop);
        }).detach();

        std::thread ([&]()
        {
            communicate::tcp_server comm(TCP_SERVER_PORT);

            comm.start(stop);
        }).detach();

        std::cin >> argc;

        break;
    }
    case 2:
    {
        if(0 == strcmp(argv[1], "udp"))
        {
            std::cout << "udp client start" << std::endl;

            communicate::udp_client comm(LOCALHOST_ADDRESS, UDP_SERVER_PORT);

            comm.start(stop);
        }
        else if(0 == strcmp(argv[1], "tcp"))
        {
            std::cout << "tcp client start" << std::endl;

            communicate::tcp_client comm(LOCALHOST_ADDRESS, TCP_SERVER_PORT);

            comm.start(stop);
        }
        else
            throw std::runtime_error("wrong argv" + WHERE_ERROR);

        break;
    }

    default:
    {
        throw std::runtime_error("wrong argc" + WHERE_ERROR);
    }
    }
}

