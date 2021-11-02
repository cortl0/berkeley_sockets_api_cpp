/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#include <iostream>

#include "application.h"

int main(int argc, char *argv[])
{
    try
    {
        application app;

        app.run(argc, argv);
    }
    catch(std::runtime_error& e)
    {
        std::cerr << "error: " << e.what() << std::endl;

        return EXIT_FAILURE;
    }
    catch(...)
    {
        std::cerr << "unknown error" << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
