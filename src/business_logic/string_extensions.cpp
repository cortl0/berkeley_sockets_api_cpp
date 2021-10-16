#include <algorithm>

#include "string_extensions.h"

namespace business_logic
{

std::list<std::string> string_extensions::split(std::string str, char delimiter)
{
    std::list<std::string> l;
    std::string s;

    std::for_each(str.begin(), str.end(), [&](char& c)
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

std::string string_extensions::remove_all(std::string str, char ch)
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
