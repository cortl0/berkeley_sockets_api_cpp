/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#ifndef APPLICATION_H
#define APPLICATION_H

/**
 * @brief The application class
 *
 * @todo For real use split into server and client parts
 * @todo Release file descriptor on SIGKILL
 */
class application
{
public:
    ~application();

    /**
     * @brief run
     * @param argc - from main
     * @param argv - from main
     */
    void run(int argc, char *argv[]);
};

#endif // APPLICATION_H
