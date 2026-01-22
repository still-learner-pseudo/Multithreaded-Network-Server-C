#include "client.h"

int sockfd = -1;

// void setSignalHandler() {
//     if ( signal( SIGPIPE, sigHandler ) == SIG_ERR ) {
//         perror( "Error with SIGPIPE handler" );
//         exit(-1);
//     }
// }

void setSockfd( int sock_fd ) {
    sockfd = sock_fd;
}

int addStudent( int rollNo, char* name, float cgpa, int numSubjects ) {
    // printf("%d, %s, %f, %d\n", rollNo, name, cgpa, numSubjects);

    addS student;
    student.rollNo = rollNo;
    student.numSubjects = numSubjects;
    student.cgpa = cgpa;
    strcpy( student.name, name );
    student.op = addStudentOption;

    if( write( sockfd, &student, sizeof(addS) ) == -1 ) {
        perror( "Error with writing to socket(add student)" );
        return -1;
    }

    replyMessage msg;
    if( read( sockfd, &msg, sizeof(msg) ) == -1 ){
        perror( "Error with reading from socket(add student)" );
        return -1;
    }

    printf("%d: %s\n", msg.code, msg.data);

    return 0;
}

int deleteStudent( int rollNo ) {
    // printf("%d\n", rollNo);

    deleteS student;
    student.rollNo = rollNo;
    student.op = deleteStudentOption;

    if( write( sockfd, &student, sizeof(deleteS) ) == -1 ) {
        perror( "Error with writing to socket(delete student)" );
        return -1;
    }

    replyMessage msg;
    if( read( sockfd, &msg, sizeof(msg) ) == -1 ){
        perror( "Error with reading from socket(delete student)" );
        return -1;
    }

    printf("%d: %s\n", msg.code, msg.data);

    return 0;
}

int modifyStudent( int rollNo, float cgpa ) {
    // printf("%d, %f\n", rollNo, cgpa);

    modifyS student;
    student.rollNo = rollNo;
    student.cgpa = cgpa;
    student.op = modifyStudentOption;

    if( write( sockfd, &student, sizeof(modifyS) ) == -1 ) {
        perror( "Error with writing to socket(modify student)" );
        return -1;
    }

    replyMessage msg;
    if( read( sockfd, &msg, sizeof(msg) ) == -1 ){
        perror( "Error with reading from socket(modify student)" );
        return -1;
    }

    printf("%d: %s\n", msg.code, msg.data);

    return 0;
}

int addCourseStudent( int rollNo, int courseCode, int marks ) {
    // printf("%d, %d, %d\n", rollNo, courseCode, marks);

    add_modify_C course;
    course.rollNo = rollNo;
    course.courseCode = courseCode;
    course.marks = marks;
    course.op = addCourseOption;

    if( write( sockfd, &course, sizeof(add_modify_C) ) == -1 ) {
        perror( "Error with writing to socket(add course)" );
        return -1;
    }

    replyMessage msg;
    if( read( sockfd, &msg, sizeof(msg) ) == -1 ){
        perror( "Error with reading from socket(add course)" );
        return -1;
    }

    printf("%d: %s\n", msg.code, msg.data);

    return 0;
}

int deleteCourseStudent( int rollNo, int courseCode ) {
    // printf("%d, %d\n", rollNo, courseCode);

    deleteC course;
    course.rollNo = rollNo;
    course.courseCode = courseCode;
    course.op = deleteCourseOption;

    if( write( sockfd, &course, sizeof(deleteC) ) == -1 ) {
        perror( "Error with writing to socket(delete course)" );
        return -1;
    }

    replyMessage msg;
    if( read( sockfd, &msg, sizeof(msg) ) == -1 ){
        perror( "Error with reading from socket(delete course)" );
        return -1;
    }

    printf("%d: %s\n", msg.code, msg.data);

    return 0;
}
int modifyCourseStudnet( int rollNo, int courseCode, int marks ) {
    // printf("%d, %d, %d\n", rollNo, courseCode, marks);

    add_modify_C course;
    course.rollNo = rollNo;
    course.courseCode = courseCode;
    course.marks = marks;
    course.op = modifyCourseOption;

    if( write( sockfd, &course, sizeof(add_modify_C) ) == -1 ) {
        perror( "Error with writing to socket(modify course)" );
        return -1;
    }

    replyMessage msg;
    if( read( sockfd, &msg, sizeof(msg) ) == -1 ){
        perror( "Error with reading from socket(modify course)" );
        return -1;
    }

    printf("%d: %s\n", msg.code, msg.data);

    return 0;
}

// void writeToFile( char* file ) {
//     writeFile info;

//     info.op = writeToFileOption;
//     strcpy( info.file, file );

//     if( write( sockfd, &info, sizeof( info ) ) == -1 ) {
//         perror( "Error with writing to fifo(write to file)" );
//         return;
//     }

//     printf( "Completed execution of client\n" );

//     return;
// }

// void sigHandler( int signum ) {
//     // if( signum == SIGPIPE ) {
//     //     int retry = RETRY;
//     //     while( retry-- ) {
//     //         if( openFIFO() != -1 ) {
//     //             break;
//     //         }
//     //         sleep(1);
//     //     }

//     //     if( retry == 0 ) {
//     //         perror( "Error with opening fifo(tried 25 times) server is down(not reading)" );
//     //         exit(-1);
//     //     }
//     // }
//     // return ;
//     if( signum == SIGPIPE ){
//         perror( "Server is down unexpectedly, please try after some time\n" );
//         unlink( FIFO );
//         exit(-1);
//     }
// }
