/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets_api_cpp
 *   licensed by GPL v3.0
 */

#ifndef BERKELEY_SOCKETS_UNIT_TESTS_COMMON_H
#define BERKELEY_SOCKETS_UNIT_TESTS_COMMON_H

#include <iostream>

#define place_string std::string().append(std::string(__FUNCTION__)).append(": ").append(__FILE__).append(": ").append(std::to_string(__LINE__))
#define log_string(msg) std::string().append((msg)).append(" | at: ").append(place_string)
#define logging(msg) std::cout << log_string((msg)) << std::endl

#define ASSERT_EQ(x, y)\
{\
    if((x) != (y))\
    {\
        logging("error: [not equivalent]");\
        std::cerr << "expected: [" << x << "], actual: [" << y << "]" << std::endl;\
        return EXIT_FAILURE;\
    }\
}

#define ASSERT_TRUE(x)\
if(!(x))\
{\
    logging("error: [not true]");\
    return EXIT_FAILURE;\
}

#define EXPECT_TRUE(x)\
if(!(x))\
{\
    logging("error: [not true]");\
}

#define ASSERT_FALSE(x)\
if((x))\
{\
    logging("error: [not false]");\
    return EXIT_FAILURE;\
}

#define EXPECT_FALSE(x)\
if((x))\
{\
    logging("error: [not false]");\
}

#endif // BERKELEY_SOCKETS_UNIT_TESTS_COMMON_H
