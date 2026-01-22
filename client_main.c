#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int main( int argc, char* argv[] ) {
    if( argc != 4 ) {
        printf( "Usage: %s <input file> <server IP> <server port>\n", argv[0] );
        exit( -1 );
    }

    int port = atoi(argv[3]);

    if( port <= 4096 || port >= 65536 ) {
        printf("Invalid port number, the range is 4097 to 65535\n");
        exit(1);
    }

    int socket_fd;

    struct sockaddr_in server;

    socket_fd = socket( AF_INET, SOCK_STREAM, 0 );
    if( socket_fd < 0 ) {
        perror("Error creating a socket in Client\n");
        exit(1);
    }

    bzero( &server, sizeof( server ) );
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(argv[2]);

    if (server.sin_addr.s_addr == INADDR_NONE) {
        perror("Invalid IP address\n");
        exit(1);
    }

    if( connect( socket_fd, ( struct sockaddr* ) &server, sizeof( server ) ) < 0 ) {
        perror( "Error connecting to server\n" );
        exit(1);
    }

    setSockfd( socket_fd );

    fileReader( argv[1], "2104_2105.out" );

    return 0;
}
