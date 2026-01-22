#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>

#include "client_server.h"

int openFIFO();
int addStudent( int rollNo, char* name, float cgpa, int numSubjects );
int deleteStudent( int rollNo );
int modifyStudent( int rollNo, float cgpa );
int addCourseStudent( int rollNo, int courseCode, int marks );
int deleteCourseStudent( int rollNo, int courseCode );
int modifyCourseStudnet( int rollNo, int courseCode, int marks );
void writeToFile( char* file );
void sigHandler( int signum );
void setSignalHandler();