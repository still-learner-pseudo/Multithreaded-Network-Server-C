#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int main( int argc, char* argv[] ) {
    if( argc != 2 ) {
        printf( "Usage: %s <input file>\n", argv[0] );
        exit( -1 );
    }

    fileReader( argv[1], "2104_2105.out" );

    return 0;
}
