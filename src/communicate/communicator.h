/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#ifndef COMMUNICATE_COMMUNICATOR_H
#define COMMUNICATE_COMMUNICATOR_H

#include <netdb.h>
#include <string>
#include <unistd.h>

#include <functional>

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
    bool initialize(int type, int protocol);
    ssize_t receive(buffer&) const;
    ssize_t receive(buffer&, address&) const;
    ssize_t receive(int file_descriptor, buffer&) const;
    ssize_t receive(int file_descriptor, buffer&, address&) const;
    ssize_t send(const buffer&) const;
    ssize_t send(const buffer&, const address&) const;
    ssize_t send(int file_descriptor, const buffer&) const;
    ssize_t send(int file_descriptor, const buffer&, const address&) const;

//protected:
    int file_descriptor;
    std::function<void(const std::string&)> log{ [](const std::string& s){} };
};

} // namespace communicate

#endif // COMMUNICATE_COMMUNICATOR_H
