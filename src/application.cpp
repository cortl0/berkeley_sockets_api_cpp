#include <thread>

#include "application.h"

static bool stop = false;

void try_catch_wrapper(void (*action)())
{
    try
    {
        action();
    }
    catch (std::runtime_error e)
    {
        std::cout << "error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "unknown error" << std::endl;
    }
}

void usage()
{
    std::cout << "Usage:\n  udp - run UDP client\n  tcp - run TCP client\n  nothing - run TCP/UDP server" << std::endl;
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
                communicate::udp_server comm(UDP_SERVER_PORT);

                comm.start(stop);
            });
        }).detach();

        std::thread ([&]()
        {
            try_catch_wrapper([]()
            {
                communicate::tcp_server comm(TCP_SERVER_PORT);

                comm.start(stop);
            });
        }).detach();

        std::cin >> argc;

        break;
    }

    case 2:
    {
        if(0 == strcmp(argv[1], "udp"))
        {
            std::cout << "udp client start" << std::endl;

            try_catch_wrapper([]()
            {
                communicate::udp_client comm(LOCALHOST_ADDRESS, UDP_SERVER_PORT);

                comm.start(stop);
            });
        }
        else if(0 == strcmp(argv[1], "tcp"))
        {
            std::cout << "tcp client start" << std::endl;

            try_catch_wrapper([]()
            {
                communicate::tcp_client comm(LOCALHOST_ADDRESS, TCP_SERVER_PORT);

                comm.start(stop);
            });
        }
        else
        {
            std::cout << "error: " << "wrong argv" + WHERE_ERROR << std::endl;

            usage();
        }

        break;
    }

    default:
    {
        std::cout << "error: " << "wrong argc" + WHERE_ERROR << std::endl;

        usage();

        break;
    }
    }
}



