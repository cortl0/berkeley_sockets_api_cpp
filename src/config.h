/**
 *   berkeley_sockets
 *   created by Ilya Shishkin
 *   cortl@8iter.ru
 *   https://github.com/cortl0/berkeley_sockets
 *   licensed by GPL v3.0
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>

struct
{
    uint16_t tcp_server_port{60001};
    uint16_t tcp_client_port{60002};
    uint16_t udp_server_port{60003};
    uint16_t udp_client_port{60004};
} config;

#endif // CONFIG_H
