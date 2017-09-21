#ifndef NETENV_H
# define NETENV_H

# include <sys/types.h> 
# include <sys/socket.h>
# include <netinet/in.h>
# include "corewar.h"

# define MAXCONNECT 4

typedef int t_socket;
typedef struct sockaddr_in t_sockaddr_in;
typedef struct sockaddr t_sockaddr;
typedef struct in_addr t_in_addr;

struct hostent *hostinfo = NULL;
const char *hostname = "localhost";

typedef struct    s_client
{
    t_sockaddr_in sin;
    t_socket      sock;
}                 t_client;

typedef struct  s_server
{
    t_socket      sock;    
    t_sockaddr_in sin;
    t_client      clients[4];
}                 t_server;

void    nte_init(t_core *core);

#endif