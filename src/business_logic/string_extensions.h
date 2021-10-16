#ifndef STRING_WORK_H
#define STRING_WORK_H

#include <list>
#include <string>

namespace business_logic
{

class string_extensions
{
public:
    static std::list<std::string> split(std::string str, char delimiter);
    static std::string remove_all(std::string str, char c);
};

}

#endif // STRING_WORK_H
