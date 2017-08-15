#include "netenv.h"

void        init_server(t_server *server)
{
    server->sock = socket(AF_INET, SOCK_STREAM, 0);
    ft_bzero(server, sizeof(t_server));
    server->sin.sin_addr.s_addr = htonl(INADDR_ANY);
    server->.sin_family = AF_INET;
    server->.sin_port = htons(PORT);
    if(server->sock == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }
    if(listen(server->sock, MAXCONNECT) == SOCKET_ERROR)
    {
        perror("listen()");
        exit(errno);
    }
}