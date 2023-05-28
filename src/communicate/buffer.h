/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#ifndef COMMUNICATE_BUFFER_H
#define COMMUNICATE_BUFFER_H

#include <sys/types.h>
#include <string>

namespace communicate
{

constexpr ssize_t buffer_size{1 << 16};

struct buffer
{
    char data[buffer_size] = {0};
    size_t size{0};

    void from_string(const std::string& s);
    std::string to_string();
};

} // namespace communicate

#endif // COMMUNICATE_BUFFER_H
