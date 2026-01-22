#include "course.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
typedef struct student student;
// typedef struct studentData studentData;

// struct studentData{
//     int rollNo;
//     char name[100];
//     float cgpa;
//     int numSubjects;
//     course* courses;
// };

struct student{
    student* prev;
    int rollNo;
    char name[100];
    float cgpa;
    int numSubjects;
    course* courses;
    student* next;
};

extern student* students;

student* findStudent( int rollNo );
int addStudent( int rollNo, char* name, float cgpa, int numSubjects );
int deleteStudent( int rollNo );
int modifyStudent( int rollNo, float cgpa );
int addCourseStudent( int rollNo, int courseCode, int marks );
int deleteCourseStudent( int rollNo, int courseCode );
int modifyCourseStudnet( int rollNo, int courseCode, int marks );
void writeStudentData( FILE* outputFile );