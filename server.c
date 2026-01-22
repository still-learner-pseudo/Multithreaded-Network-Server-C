#include "server.h"

// int fd = -1;
// FILE* outputFile = NULL;

FILE* openFileToWrite( char* filename ) {
    FILE* file = fopen( filename, "w" );
    if( file == NULL ) {
        perror( "Error opening file to write in server" );
        exit(1);
    }
    return file;
}

void* readSocket( void* param ) {
    int fd = *(int*)param;
    option op = -1;
    size_t offset = sizeof(option);
    while(1) {
        if( read( fd, &op, sizeof( option ) ) == 4 ) {
            if( op == addStudentOption ) {
                addS student;
                if( read( fd, (char* )&student + offset, sizeof( addS ) - offset ) == -1 ) {
                    perror( "Error with reading from socket(add student) in server" );
                    close( fd );
                    pthread_exit( NULL );
                }
                // printf( "%d, %s, %f, %d\n", student.rollNo, student.name, student.cgpa, student.numSubjects );
                sem_wait( &sem );
                int retVal = addStudent( student.rollNo, student.name, student.cgpa, student.numSubjects );
                sem_post( &sem );

                writeMessage( fd, retVal, "Add Student" );
                
                FILE* outputFile = openFileToWrite( "2104_2105.out" );
                
                sem_wait( &sem );
                writeStudentData( outputFile );
                sem_post( &sem );
                fclose( outputFile );
            }
            else if( op == deleteStudentOption ) {
                deleteS student;
                if( read( fd, (char* )&student + offset, sizeof( deleteS ) - offset ) == -1 ) {
                    perror( "Error with reading from socket(delete student) in server" );
                    close( fd );
                    pthread_exit( NULL );
                }
                // printf( "%d\n", student.rollNo );
                sem_wait( &sem );
                int retVal = deleteStudent( student.rollNo );
                sem_post( &sem );

                writeMessage( fd, retVal, "Delete Student" );

                FILE* outputFile = openFileToWrite( "2104_2105.out" );

                sem_wait( &sem );
                writeStudentData( outputFile );
                sem_post( &sem );
                fclose( outputFile );
            }
            else if( op == modifyStudentOption ) {
                modifyS student;
                if( read( fd, (char* )&student + offset, sizeof( modifyS ) - offset ) == -1 ) {
                    perror( "Error with reading from socket(modify student) in server" );
                    close( fd );
                    pthread_exit( NULL );
                }
                // printf( "%d, %f\n", student.rollNo, student.cgpa );
                sem_wait( &sem );
                int retVal = modifyStudent( student.rollNo, student.cgpa );
                sem_post( &sem );

                writeMessage( fd, retVal, "Modify Student" );

                FILE* outputFile = openFileToWrite( "2104_2105.out" );

                sem_wait( &sem );
                writeStudentData( outputFile );
                sem_post( &sem );
                fclose( outputFile );
            }
            else if( op == addCourseOption ) {
                add_modify_C student;
                if( read( fd, (char* )&student + offset, sizeof( add_modify_C ) - offset ) == -1 ) {
                    perror( "Error with reading from socket(add modify course) in server" );
                    close( fd );
                    pthread_exit( NULL );
                }
                // printf( "%d, %d, %d\n", student.rollNo, student.courseCode, student.marks );
                sem_wait( &sem );
                int retVal = addCourseStudent( student.rollNo, student.courseCode, student.marks );
                sem_post( &sem );

                writeMessage( fd, retVal, "Add Course" );

                FILE* outputFile = openFileToWrite( "2104_2105.out" );

                sem_wait( &sem );
                writeStudentData( outputFile );
                sem_post( &sem );
                fclose( outputFile );
            }
            else if( op == deleteCourseOption ) {
                deleteC student;
                if( read( fd, (char* )&student + offset, sizeof( deleteC ) - offset ) == -1 ) {
                    perror( "Error with reading from socket(delete course) in server" );
                    close( fd );
                    pthread_exit( NULL );
                }
                // printf( "%d, %d\n", student.rollNo, student.courseCode );
                sem_wait( &sem );
                int retVal = deleteCourseStudent( student.rollNo, student.courseCode );
                sem_post( &sem );

                writeMessage( fd, retVal, "Modify Course" );

                FILE* outputFile = openFileToWrite( "2104_2105.out" );

                sem_wait( &sem );
                writeStudentData( outputFile );
                sem_post( &sem );
                fclose( outputFile );
            }
            else if( op == modifyCourseOption ) {
                add_modify_C student;
                if( read( fd, (char* )&student + offset, sizeof( add_modify_C ) - offset ) == -1 ) {
                    perror( "Error with reading from socket(modify course) in server" );
                    close( fd );
                    pthread_exit( NULL );
                }
                // printf( "%d, %d, %d\n", student.rollNo, student.courseCode, student.marks );
                sem_wait( &sem );
                int retVal = modifyCourseStudnet( student.rollNo, student.courseCode, student.marks );
                sem_post( &sem );

                writeMessage( fd, retVal, "Delete Course" );

                FILE* outputFile = openFileToWrite( "2104_2105.out" );
                
                sem_wait( &sem );
                writeStudentData( outputFile );
                sem_post( &sem );
                fclose( outputFile );
            }
            // else if( op == writeToFileOption ) {
            //     writeFile info;
            //     if( read( fd, &info.file, sizeof( writeFile ) - sizeof( option ) ) == -1 ) {
            //         perror( "Error with reading from fifo(write to file) in server" );
            //         return -1;
            //     }

            //     FILE *outputFile = fopen( info.file, "w" );
            //     if( !outputFile ) {
            //         perror( "Error with opening output file in server" );
            //         exit(-1);
            //     }

            //     writeStudentData( outputFile );
            //     fclose( outputFile );

            //     break;
            // }
            else {
                perror( "Error couldn't find the option specified" );
                close( fd );
                pthread_exit( NULL );
            }
        }
        else if( read( fd, &op, sizeof( option ) ) == 0 ) {
            // sem_wait( &sem );
            // writeStudentData( outputFile );
            // sem_post( &sem );
            printf( "Closing connection\n" );
            close( fd );
            break;
        }
    }
    // close( fd );
    return NULL;
}


void writeMessage( int client_fd, int value, char* message ) {
    replyMessage msg;
    if( value == -1 || value == 0 ) {
        msg.code = 404;
        strcpy( msg.data, "Cannot perform the operation " );
        strcat( msg.data, message );
    }

    else {
        msg.code = 200;
        strcpy( msg.data, "Operation " );
        strcat( msg.data, message );
        strcat( msg.data, " was successful" );
    }

    if( write( client_fd, &msg, sizeof(replyMessage) ) == -1 ) {
        perror( "Write to client failed" );
    }
}
