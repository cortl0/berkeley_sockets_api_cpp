/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#ifndef COMMUNICATE_COMMUNICATOR_H
#define COMMUNICATE_COMMUNICATOR_H

#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

#include "buffer.h"

#define LOCALHOST_ADDRESS 0x7F000001
#define TCP_SERVER_PORT 5005
#define UDP_SERVER_PORT 41797

#define WHERE_ERROR (" at function: " + std::string(__FUNCTION__) + ", file: " + __FILE__ + ", line: " + std::to_string(__LINE__))
#define ERROR_STRING_BY_ERRNO (std::string(strerror(errno)) + WHERE_ERROR)

namespace communicate
{

class communicator
{
protected:
    int file_descriptor;
    bool stopped = true;
    struct sockaddr_in address;

    ssize_t receive(int file_descriptor, buffer&, sockaddr_in&) const;
    ssize_t send(int file_descriptor, const buffer&, const sockaddr_in&) const;

public:
    virtual ~communicator();
    explicit communicator(int domain, int type, int protocol);
    bool is_stopped();
    virtual void start(bool& stop) = 0;
};

}

#endif // COMMUNICATE_COMMUNICATOR_H
