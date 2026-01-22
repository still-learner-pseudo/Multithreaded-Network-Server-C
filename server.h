#include "client_server.h"
#include "student.h"
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_CLIENTS 100

extern pthread_t clientConnection[MAX_CLIENTS];
extern sem_t sem;
void* readSocket( void* param );
FILE* openFileToWrite( char* file );
void writeMessage( int client_fd, int value, char* message );
