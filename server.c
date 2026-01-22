#include "server.h"

int fd = -1;

int openFIFO() {

    if( mkfifo( FIFO, 0666 ) == -1 ) {
        if(errno == EEXIST ) {
            unlink(FIFO);
            openFIFO();
        }
        else if( errno != EEXIST ) {
            perror( "Error with creating fifo at /tmp/client_server in server" );
            return -1;
        }

        return 0;
    }

    fd = open( FIFO, O_RDONLY | O_NONBLOCK );
    // printf( "server side fd is: %d\n", fd );

    if( fd == -1 ) {
        perror( "Error with opening fifo at /tmp/client_server in server" );
        return -1;
    }

    return fd;
}

int readFIFO() {
    option op = -1;
    while(1) {
        if( read( fd, &op, sizeof( option ) ) == 4 ) {
            if( op == addStudentOption ) {
                addS student;
                if( read( fd, &student.rollNo, sizeof( addS ) - sizeof( option ) ) == -1 ) {
                    perror( "Error with reading from fifo(add student) in server" );
                    return -1;
                }
                // printf( "%d, %s, %f, %d\n", student.rollNo, student.name, student.cgpa, student.numSubjects );
                addStudent( student.rollNo, student.name, student.cgpa, student.numSubjects );
            }
            else if( op == deleteStudentOption ) {
                deleteS student;
                if( read( fd, &student.rollNo, sizeof( deleteS ) - sizeof( option ) ) == -1 ) {
                    perror( "Error with reading from fifo(delete student) in server" );
                    return -1;
                }
                // printf( "%d\n", student.rollNo );
                deleteStudent( student.rollNo );
            }
            else if( op == modifyStudentOption ) {
                modifyS student;
                if( read( fd, &student.rollNo, sizeof( modifyS ) - sizeof( option ) ) == -1 ) {
                    perror( "Error with reading from fifo(modify student) in server" );
                    return -1;
                }
                // printf( "%d, %f\n", student.rollNo, student.cgpa );
                modifyStudent( student.rollNo, student.cgpa );
            }
            else if( op == addCourseOption ) {
                add_modify_C student;
                if( read( fd, &student.rollNo, sizeof( add_modify_C ) - sizeof( option ) ) == -1 ) {
                    perror( "Error with reading from fifo(add modify course) in server" );
                    return -1;
                }
                // printf( "%d, %d, %d\n", student.rollNo, student.courseCode, student.marks );
                addCourseStudent( student.rollNo, student.courseCode, student.marks );
            }
            else if( op == deleteCourseOption ) {
                deleteC student;
                if( read( fd, &student.rollNo, sizeof( deleteC ) - sizeof( option ) ) == -1 ) {
                    perror( "Error with reading from fifo(delete course) in server" );
                    return -1;
                }
                // printf( "%d, %d\n", student.rollNo, student.courseCode );
                deleteCourseStudent( student.rollNo, student.courseCode );
            }
            else if( op == modifyCourseOption ) {
                add_modify_C student;
                if( read( fd, &student.rollNo, sizeof( add_modify_C ) - sizeof( option ) ) == -1 ) {
                    perror( "Error with reading from fifo(modify course) in server" );
                    return -1;
                }
                // printf( "%d, %d, %d\n", student.rollNo, student.courseCode, student.marks );
                modifyCourseStudnet( student.rollNo, student.courseCode, student.marks );
            }
            else if( op == writeToFileOption ) {
                writeFile info;
                if( read( fd, &info.file, sizeof( writeFile ) - sizeof( option ) ) == -1 ) {
                    perror( "Error with reading from fifo(write to file) in server" );
                    return -1;
                }

                FILE *outputFile = fopen( info.file, "w" );
                if( !outputFile ) {
                    perror( "Error with opening output file in server" );
                    exit(-1);
                }

                writeStudentData( outputFile );
                fclose( outputFile );

                // printf( "***NOTE: PLEASE REMOVE 2104_2105.OUT FILE IF UNIQUE IDENTIFIERS(ROLL NUMBERS, COURSE CODE) ARE SAME***\n" );

                unlink( FIFO );
                openFIFO();
                break;
            }
            else {
                perror( "Error couldn't find the option specified" );
                return -1;
            }
        }
        // else if( read( fd, &op, sizeof( option ) ) == 0 ) {
        //     writeStudentData( file );
        //     break;
        // }
        // else if( read( fd, &op, sizeof( option ) ) != 4 ) {
        //     printf( "option is not read properly\n" );
        // }
        // else {
        //     sleep( 1 );
        //     printf("In sleep\n");
        //     break;
        // }
    }
    return 0;
}