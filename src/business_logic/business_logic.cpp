#include <algorithm>
#include <set>

#include "business_logic.h"
#include "string_extensions.h"

namespace business_logic
{

std::string business_logic::calculate(const std::string &str)
{
    auto strings = string_extensions::split(str, ' ');

    std::multiset<int> nums;

    for_each (strings.begin(), strings.end(), [&](const std::string &s)
    {
        if(s.size() == 0)
            return ;

        if(std::any_of(s.begin(), s.end(), [](const char &c)
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
        catch (...) { }
    });

    int sum = 0;

    std::string result;

    for_each (nums.begin(), nums.end(), [&](const int &i)
    {
        result += std::to_string(i) + " ";

        sum += i;
    });

    if(result.size() > 0)
        result.resize(result.size() - 1);

    result += '\n' + std::to_string(sum) + '\0';

    return result;
}

}
