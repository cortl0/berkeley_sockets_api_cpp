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
    struct sockaddr_in address;

    std::string receive(const int &file_descriptor, sockaddr_in &address) const;
    void send(const int &file_descriptor, const std::string &str, sockaddr_in &address) const;

public:
    virtual ~communicator();
    communicator(int domain, int type, int protocol);
    virtual void start(bool &stop) = 0;
};

}

#endif // COMMUNICATOR_H
