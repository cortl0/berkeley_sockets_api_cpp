#ifndef STRING_WORK_H
#define STRING_WORK_H

#include <list>
#include <string>

namespace business_logic
{

class string_extensions
{
public:
    static std::list<std::string> split(const std::string &str, const char &delimiter);
    static std::string remove_all(const std::string &str, const char &c);
};

}

#endif // STRING_WORK_H
