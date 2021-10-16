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
        std::cout << "error: " << e.what() << std::endl;

        return EXIT_FAILURE;
    }
    catch(...)
    {
        std::cout << "unknown error" << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
