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

#include <functional>
#include <iostream>

#include "address.h"
#include "buffer.h"

#define WHERE_ERROR (" at function: " + std::string(__FUNCTION__) + ", file: " + __FILE__ + ", line: " + std::to_string(__LINE__))
#define ERROR_STRING_BY_ERRNO (std::string(strerror(errno)) + WHERE_ERROR)

namespace communicate
{

class communicator
{
public:
    virtual ~communicator();
    bool initialize(int type, int protocol, address local, address remote);
    bool is_stopped();
    virtual void start(bool& stop) {}//= 0;

//protected:
    int file_descriptor;
    bool stopped = true;
    struct sockaddr_in address5;
    ssize_t receive(int file_descriptor, buffer&, sockaddr_in&) const;
    ssize_t send(int file_descriptor, const buffer&, const sockaddr_in&) const;
    std::function<void(std::string&)> log = [](const std::string& s) { /*std::cout << s << std::endl;*/ };
};

} // namespace communicate

#endif // COMMUNICATE_COMMUNICATOR_H
