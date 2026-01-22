#include <stdio.h>
#include "server.h"

int main( int argc, char* argv[] ) {
    if( openFIFO() == -1 ) {
        perror( "Error with opening fifo at /tmp/client_server" );
        return -1;
    }

    while( 1 ) {
        if( readFIFO() == -1 ) {
            perror( "Error with reading from fifo" );
            return -1;
        }
    }

    return 0;
}