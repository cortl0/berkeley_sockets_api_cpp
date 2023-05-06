/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#ifndef BUSINESS_LOGIC_H
#define BUSINESS_LOGIC_H

#include <string>

#include "../communicate/buffer.h"

namespace business_logic
{

class business_logic
{
public:
    static bool calculate(communicate::buffer&, int type);
    static void input(communicate::buffer&);
    static void output(const communicate::buffer&, ssize_t number_of_bytes_resived);
};

}

#endif // BUSINESS_LOGIC_H
