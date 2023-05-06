/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#ifndef STRING_EXTENSIONS_H
#define STRING_EXTENSIONS_H

#include <list>
#include <string>

namespace business_logic
{

class string_extensions
{
public:
    static std::list<std::string> split(const std::string& str, const char& delimiter);
    static std::string remove_all(const std::string& str, const char& c);
};

}

#endif // STRING_EXTENSIONS_H
