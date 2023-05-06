
#ifndef COMMUNICATE_BUFFER_TOOLS_H
#define COMMUNICATE_BUFFER_TOOLS_H

#include <string.h>
#include <string>

#include "buffer.h"

namespace communicate
{

void buffer_set(buffer& b, std::string& s)
{
    b.size = s.size() + 1;
    memcpy((void*)b.data, s.c_str(), b.size);
}

std::string buffer_get(buffer& b)
{
    ((char*)b.data)[b.size-1] = '\0';
    std::string s(((char*)b.data));
    return s;
}

} // namespace communicate

#endif // COMMUNICATE_BUFFER_TOOLS_H
