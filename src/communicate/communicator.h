/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#ifndef COMMUNICATE_COMMUNICATOR_H
#define COMMUNICATE_COMMUNICATOR_H

#include <unistd.h>

#include <functional>

#include "address.h"
#include "buffer.h"

#define WHERE_ERROR ("at function: [" + std::string(__FUNCTION__) + "], file: [" + __FILE__ + "], line: [" + std::to_string(__LINE__) + "]")
#define ERROR_STRING_BY_ERRNO_WITH_PLACE ("Error: [" + std::string(strerror(errno)) + "] " + WHERE_ERROR)

namespace communicate
{

constexpr int socket_error = -1;

class communicator
{
public:
    virtual ~communicator();
    ssize_t receive(buffer&) const;
    ssize_t receive(buffer&, address&) const;
    ssize_t receive(int file_descriptor, buffer&) const;
    ssize_t receive(int file_descriptor, buffer&, address&) const;
    ssize_t send(const buffer&) const;
    ssize_t send(const buffer&, const address&) const;
    ssize_t send(int file_descriptor, const buffer&) const;
    ssize_t send(int file_descriptor, const buffer&, const address&) const;

protected:
    int accept(address* remote = nullptr);
    bool bind(address local);
    bool close();
    bool close(int file_descriptor);
    bool connect(address remote);
    bool shutdown(int file_descriptor);
    bool listen();
    bool socket(int type, int protocol);

    std::function<void(const std::string&)> log{ [](const std::string& s){} };

private:
    int file_descriptor;
};

} // namespace communicate

#endif // COMMUNICATE_COMMUNICATOR_H
