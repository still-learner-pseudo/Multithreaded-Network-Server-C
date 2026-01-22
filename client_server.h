#include <fcntl.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

// #define SERVER_PORT 12000

// typedef union allValues allValues;
typedef struct addStudent addS;
typedef struct modifyStudent modifyS;
typedef struct deleteStudent deleteS;
typedef struct addModifyCourse add_modify_C;
typedef struct deleteCourse deleteC;
typedef enum opt option;
typedef struct writeToFile writeFile;
typedef struct message replyMessage;


enum opt{
    addStudentOption,
    modifyStudentOption,
    deleteStudentOption,
    addCourseOption,
    modifyCourseOption,
    deleteCourseOption,
    writeToFileOption
};

// union allValues{

    struct addStudent{
        option op;
        int rollNo;
        int numSubjects;
        float cgpa;
        char name[100];
    };

    struct modifyStudent{
        option op;
        int rollNo;
        float cgpa;
    };

    struct deleteStudent{
        option op;
        int rollNo;
    };

    struct addModifyCourse{
        option op;
        int rollNo;
        int courseCode;
        int marks;
    };

    struct deleteCourse{
        option op;
        int rollNo;
        int courseCode;
    };

    struct writeToFile{
        option op;
        char file[100];
    };
// };

// #define RETRY 30
// #define FIFO "/tmp/client_server"

// int fd = -1;

struct message{
    int code;
    char data[100];
};
