/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include <algorithm>
#include <iostream>
#include <set>

#include "../communicate/buffer_tools.h"
#include "business_logic.h"
#include "string_extensions.h"

namespace business_logic
{

bool business_logic::calculate(communicate::buffer& b, int type)
{
    std::string str = communicate::buffer_get(b);

    if(str.size() == 0)
        return false;

    std::cout << (type == 1 ? "udp <<< " : "tcp <<< ") << str << std::endl;

    auto strings = string_extensions::split(
                string_extensions::remove_all(
                    string_extensions::remove_all(str, ','), '.'), ' ');

    std::multiset<int> nums;

    for_each(strings.begin(), strings.end(), [&](const std::string& s)
    {
        if(s.size() == 0)
            return ;

        if(std::any_of(s.begin(), s.end(), [](const char& c)
        {
            if(c < 0x30 || c > 0x39)
                return true;

            return false;
        }))
            return ;

        try
        {
            nums.insert(std::stoi(s));
        }
        catch(...) { }
    });

    int sum = 0;

    std::string result;

    for_each(nums.begin(), nums.end(), [&](const int& i)
    {
        result += std::to_string(i) + " ";
        sum += i;
    });

    if(result.size() > 0)
        result.resize(result.size() - 1);

    result += '\n' + std::to_string(sum) + '\0';
    communicate::buffer_set(b, result);
    std::cout << (type == 1 ? "udp >>> " : "tcp >>> ") << str << std::endl;
    return true;
}

void business_logic::input(communicate::buffer& b)
{
    std::string s;
    std::getline(std::cin, s);
    buffer_set(b, s);
}

void business_logic::output(const communicate::buffer& b, ssize_t number_of_bytes_resived)
{
    std::cout << "bytes recieved: " << number_of_bytes_resived << std::endl;
    std::cout << "bytes: " << std::string((char*)b.data, number_of_bytes_resived) << std::endl;
}

}
