#ifndef COMMUNICATE_BUFFER_H
#define COMMUNICATE_BUFFER_H

#include <sys/types.h>

#define COMMUNICATOR_BUFFER_SIZE 1024

namespace communicate
{

struct buffer
{
    buffer()
    {
        size = COMMUNICATOR_BUFFER_SIZE;
        data = data_internal;
    }

    void* data;
    size_t size;

private:
    char data_internal[COMMUNICATOR_BUFFER_SIZE];
};

} // namespace communicate

#endif // COMMUNICATE_BUFFER_H
