/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#include "buffer.h"

#include <string.h>

namespace communicate
{

void buffer::from_string(const std::string& s)
{
    size = s.size();

    if(size > buffer_size)
        size = buffer_size;

    memcpy(data, s.c_str(), size);
}

std::string buffer::to_string()
{
    std::string s;
    s.resize(size);
    memcpy(s.data(), data, size);
    return s;
}

} // namespace communicate
