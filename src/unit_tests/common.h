/*
 *   Binary Neurons Network
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   http://8iter.ru/ai.html
 *   https://github.com/cortl0/binary_neurons_network
 *   licensed by GPL v3.0
 */

#ifndef BERKELEY_SOCKETS_UNIT_TESTS_COMMON_H
#define BERKELEY_SOCKETS_UNIT_TESTS_COMMON_H

#include <iostream>

using namespace std::string_literals;

#define place_string std::string().append(std::string(__FUNCTION__)).append(": ").append(__FILE__).append(": ").append(std::to_string(__LINE__))
#define log_string(msg) std::string().append(" | ").append(msg).append(" | at: ").append(place_string)
#define logging(msg) std::cout << log_string(msg) << std::endl

#define ASSERT_EQ(x, y)\
if((x) != (y))\
{\
    logging("error: expected ["s + std::to_string(x) + "], actual ["s + std::to_string(y) + "]"s);\
    return EXIT_FAILURE;\
}

#define ASSERT_TRUE(x)\
if(!(x))\
{\
    logging("error: not true"s);\
    return EXIT_FAILURE;\
}

#define ASSERT_FALSE(x)\
if((x))\
{\
    logging("error: not false"s);\
    return EXIT_FAILURE;\
}

#endif // BERKELEY_SOCKETS_UNIT_TESTS_COMMON_H
