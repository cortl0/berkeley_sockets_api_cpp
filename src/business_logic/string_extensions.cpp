/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include <algorithm>

#include "string_extensions.h"

namespace business_logic
{

std::list<std::string> string_extensions::split(const std::string &str, const char &delimiter)
{
    std::list<std::string> l;
    std::string s;

    std::for_each(str.begin(), str.end(), [&](const char &c)
    {
        if(c == delimiter)
        {
            if(s.size() > 0)
            {
                l.push_back(s);

                s = std::string();
            }

            return;
        }

        s.push_back(c);
    });

    if(s.size() > 0)
        l.push_back(s);

    return l;
}

std::string string_extensions::remove_all(const std::string &str, const char &ch)
{
    std::string s;

    std::for_each(str.begin(), str.end(), [&](char c)
    {
        if (c != ch)
            s += c;
    });
    return s;
}

}
