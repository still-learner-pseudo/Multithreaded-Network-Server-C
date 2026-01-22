#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void fileReader( const char* input, const char* output );

void addInitialData( char* buffer );
void addStudentData( char* buffer );
void modifyStudentData( char* buffer );
void deleteStudentData( char* buffer );
void addCourseData( char* buffer );
void modifyCourseData( char* buffer );
void deleteCourseData( char* buffer );
void trimSpaces( char* name );
