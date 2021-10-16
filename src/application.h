#ifndef APPLICATION_H
#define APPLICATION_H

#include "communicate/udp_client.h"
#include "communicate/udp_server.h"
#include "communicate/tcp_client.h"
#include "communicate/tcp_server.h"

/**
 * @brief The application class
 *
 * @todo Fix tcp_server crash on loss of conection with tcp_client
 * @todo For real use split into server and client parts
 * @todo Release file descriptor on SIGKILL
 */
class application
{
public:
    /**
     * @brief run
     * @param argc - from main
     * @param argv - from main
     */
    void run(int argc, char *argv[]);
};

#endif // APPLICATION_H
