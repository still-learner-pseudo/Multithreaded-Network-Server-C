#include "client.h"

int fd = -1;

void setSignalHandler() {
    if ( signal( SIGPIPE, sigHandler ) == SIG_ERR ) {
        perror( "Error with SIGPIPE handler" );
        exit(-1);
    }
}

int openFIFO() {

    if( mkfifo( FIFO, 0666 ) == -1 ) {
        if( errno != EEXIST ) {
            perror( "Error with creating fifo at /tmp/client_server" );
            return -1;
        }
    }

    int retry = RETRY;
    while( retry > 0 ) {
        fd = open( FIFO, O_WRONLY | O_NONBLOCK );
        if( fd != -1 ) {
            return fd;
        }
        perror( "Error with opening FIFO at /tmp/client_server, retrying \n " );
        sleep(1);

        if( retry == 1 ) {
            fprintf( stderr, "Failed to open FIFO after %d times\n", RETRY );
            unlink( FIFO );
            exit(-1);
        }
        retry--;
    }

    return -1;
}

int addStudent( int rollNo, char* name, float cgpa, int numSubjects ) {
    // printf("%d, %s, %f, %d\n", rollNo, name, cgpa, numSubjects);

    addS student;
    student.rollNo = rollNo;
    student.numSubjects = numSubjects;
    student.cgpa = cgpa;
    strcpy( student.name, name );
    student.op = addStudentOption;

    if( write( fd, &student, sizeof(addS) ) == -1 ) {
        perror( "Error with writing to fifo(add student)" );
        return -1;
    }
    
    return 0;
}

int deleteStudent( int rollNo ) {
    // printf("%d\n", rollNo);

    deleteS student;
    student.rollNo = rollNo;
    student.op = deleteStudentOption;

    if( write( fd, &student, sizeof(deleteS) ) == -1 ) {
        perror( "Error with writing to fifo(delete student)" );
        return -1;
    }

    return 0;
}

int modifyStudent( int rollNo, float cgpa ) {
    // printf("%d, %f\n", rollNo, cgpa);

    modifyS student;
    student.rollNo = rollNo;
    student.cgpa = cgpa;
    student.op = modifyStudentOption;

    if( write( fd, &student, sizeof(modifyS) ) == -1 ) {
        perror( "Error with writing to fifo(modify student)" );
        return -1;
    }

    return 0;
}

int addCourseStudent( int rollNo, int courseCode, int marks ) {
    // printf("%d, %d, %d\n", rollNo, courseCode, marks);

    add_modify_C course;
    course.rollNo = rollNo;
    course.courseCode = courseCode;
    course.marks = marks;
    course.op = addCourseOption;

    if( write( fd, &course, sizeof(add_modify_C) ) == -1 ) {
        perror( "Error with writing to fifo(add course)" );
        return -1;
    }

    return 0;
}

int deleteCourseStudent( int rollNo, int courseCode ) {
    // printf("%d, %d\n", rollNo, courseCode);

    deleteC course;
    course.rollNo = rollNo;
    course.courseCode = courseCode;
    course.op = deleteCourseOption;

    if( write( fd, &course, sizeof(deleteC) ) == -1 ) {
        perror( "Error with writing to fifo(delete course)" );
        return -1;
    }

    return 0;
}
int modifyCourseStudnet( int rollNo, int courseCode, int marks ) {
    // printf("%d, %d, %d\n", rollNo, courseCode, marks);

    add_modify_C course;
    course.rollNo = rollNo;
    course.courseCode = courseCode;
    course.marks = marks;
    course.op = modifyCourseOption;

    if( write( fd, &course, sizeof(add_modify_C) ) == -1 ) {
        perror( "Error with writing to fifo(modify course)" );
        return -1;
    }

    return 0;
}

void writeToFile( char* file ) {
    writeFile info;

    info.op = writeToFileOption;
    strcpy( info.file, file );

    if( write( fd, &info, sizeof( info ) ) == -1 ) {
        perror( "Error with writing to fifo(write to file)" );
        return;
    }

    printf( "Completed execution of client\n" );

    return;
}

void sigHandler( int signum ) {
    // if( signum == SIGPIPE ) {
    //     int retry = RETRY;
    //     while( retry-- ) {
    //         if( openFIFO() != -1 ) {
    //             break;
    //         }
    //         sleep(1);
    //     }

    //     if( retry == 0 ) {
    //         perror( "Error with opening fifo(tried 25 times) server is down(not reading)" );
    //         exit(-1);
    //     }
    // }
    // return ;
    if( signum == SIGPIPE ){
        perror( "Server is down unexpectedly, please try after some time\n" );
        unlink( FIFO );
        exit(-1);
    }
}