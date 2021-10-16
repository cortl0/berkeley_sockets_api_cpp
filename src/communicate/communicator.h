#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <iostream>

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define LOCALHOST_ADDRESS 0x7F000001
#define TCP_SERVER_PORT 5005
#define UDP_SERVER_PORT 41797
#define COMMUNICATOR_BUFFER_SIZE 1024

#define WHERE_ERROR (" at function: " + std::string(__FUNCTION__) + ", file: " + __FILE__ + ", line: " + std::to_string(__LINE__))
#define ERROR_STRING_BY_ERRNO (std::string(strerror(errno)) + WHERE_ERROR)

namespace communicate
{

class communicator
{
protected:
    int file_descriptor;
    struct sockaddr_in sender_address, address;

    std::string receive(int file_descriptor, sockaddr_in& address);
    void send(int file_descriptor, const std::string& str, sockaddr_in& address);

public:
    virtual ~communicator();
    communicator(int domain, int type, int protocol);
    virtual void start(bool& stop) = 0;
};

}

#endif // COMMUNICATOR_H
