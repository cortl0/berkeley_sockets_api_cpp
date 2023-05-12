/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#ifndef COMMUNICATE_BUFFER_H
#define COMMUNICATE_BUFFER_H

#include <sys/types.h>

namespace communicate
{

constexpr ssize_t buffer_size{1 << 16};

struct buffer
{
    char data[buffer_size];
    size_t size{0};
};

} // namespace communicate

#endif // COMMUNICATE_BUFFER_H
