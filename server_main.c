#include <stdio.h>
#include "server.h"

pthread_t clientConnection[MAX_CLIENTS];
sem_t sem;

int main( int argc, char* argv[] ) {

    if( argc != 3 ) {
        printf("Usage: %s <server_ip> <server_port>\n", argv[0]);
        exit(1);
    }

    int port = atoi(argv[2]);

    if( port <= 4096 || port >= 65536 ) {
        printf("Invalid port number, the range is 4097 to 65535\n");
        exit(1);
    }

    int socket_fd;
    int opt = 1, numberOfClients = 0;
    struct sockaddr_in server, client;

    socket_fd = socket( AF_INET, SOCK_STREAM, 0 );
    if( socket_fd < 0 ) {
        perror("Error creating a socket in server\n");
        exit(1);
    }
    // if( setsockopt( socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt) ) < 0 ){
    //     perror("Error setting socket options\n");
    //     exit(1);
    // }
    //

    // Set SO_REUSEADDR
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("Error setting SO_REUSEADDR");
        exit(1);
    }

    // Set SO_REUSEPORT
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        perror("Error setting SO_REUSEPORT");
        exit(1);
    }

    // printf("Socket created\n");
    bzero( &server, sizeof( server ) );
    bzero( &client, sizeof( client ) );

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(argv[1]);

    if( bind( socket_fd, ( struct sockaddr* ) &server, sizeof( server ) ) < 0 ) {
        perror( "Error binding socket in server\n" );
        exit(1);
    }

    // printf("bind successful\n");

    if( listen( socket_fd, 5 ) < 0 ) {
        perror( "Error listening to socket\n" );
        exit(1);
    }

    // printf("listen successful\n");

    openFileToWrite( "2104_2105.out" );

    // allocating space for semaphore

    // sem_t *sem = (sem_t *) malloc( sizeof( sem_t ) );
    if( sem_init( &sem, 0, 1 ) != 0 ) {
        perror("Error creating semaphore\n");
        exit(1);
    }

    while( 1 ) {
        int client_fd;
        socklen_t client_len = sizeof( client );
        client_fd = accept( socket_fd, ( struct sockaddr* ) &client, &client_len );

        if( client_fd < 0 ) {
            perror( "Error accepting client\n" );
            exit(1);
        }

        printf( "Client connected\n" );

        if( pthread_create( &clientConnection[numberOfClients++], NULL, readSocket, &client_fd ) != 0 ) {
            perror("Error creating thread\n");
            close( client_fd );
            continue;
        }

        pthread_detach( clientConnection[numberOfClients-1] );
    }

    close( socket_fd );
    return 0;
}
