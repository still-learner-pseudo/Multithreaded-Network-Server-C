#include "student.h"

student* students = NULL;

student* findStudent( int rollNo ){
    student* student = students;
    if( student == NULL ) {
        return NULL;
    }
    while( student != NULL ) {
        if( student -> rollNo == rollNo ) {
            return student;
        }
        student = student -> next;
    }

    return NULL;
}

int addStudent( int rollNo, char* name, float cgpa, int numSubjects ) {
    if( findStudent( rollNo ) != NULL ) {
        fprintf( stderr, "Cannot add student with %d roll number(already exists).\n", rollNo );
        return 0;
    }

    student* newStudent = ( student* ) malloc( sizeof( student ) );
    if( newStudent == NULL ) { //malloc failed
        perror( "Malloc failed\n" );
        return -1;
    }

    if( ( students ) != NULL ) {
        ( students ) -> prev = newStudent;
    }
     
    newStudent -> prev = NULL;
    newStudent -> rollNo = rollNo;
    strcpy( newStudent -> name, name );
    newStudent -> numSubjects = numSubjects;
    newStudent -> cgpa = cgpa;
    newStudent -> courses = NULL;
    newStudent -> next = students;

    students = newStudent;

    return 1;
}

int deleteStudent( int rollNo ) {
    student* delStudent = findStudent( rollNo );
    if( delStudent == NULL ) {
        fprintf( stderr, "Cannot delete student with %d roll number(not found).\n", rollNo );
        return 0;
    }

    if( delStudent -> prev != NULL ) {
        delStudent -> prev -> next = delStudent -> next;
    }
    else{
        students = delStudent -> next;
    }

    if( delStudent -> next != NULL ) {
        delStudent -> next -> prev = delStudent -> prev;
    }

    free( delStudent );

    return 1;
}

int modifyStudent( int rollNo, float cgpa ) {
    student* modStudent = findStudent( rollNo );
    if ( modStudent == NULL ) {
	fprintf( stderr, "Cannot modify student with %d roll number(not found).\n", rollNo );
        return 0;
    }
    modStudent -> cgpa = cgpa;

    return 1;
}

int addCourseStudent( int rollNo, int courseCode, int marks ) {
    student* student = findStudent( rollNo );
    if( student == NULL ) {
	fprintf( stderr, "Cannot add course %d courseCode to %d student(student not found).\n", courseCode, rollNo );
        return 0;
    }

    // if( findCourse( student -> courses, courseCode ) != NULL ) {
    //     return 0;
    // }

    int result = addCourse( &( student -> courses ), courseCode, marks );
    
    if( result == 1 ) {
        student -> numSubjects++;
    }

    return result;
}

int deleteCourseStudent( int rollNo, int courseCode ) {
    student* student = findStudent( rollNo );
    if( student == NULL ) {
	fprintf( stderr, "Cannot delete course %d courseCode to %d student(student not found).\n", courseCode, rollNo );
        return 0;
    }

    int result = deleteCourse( &( student -> courses ), courseCode );

    if( result == 1 ) {
        student -> numSubjects--;
    }

    return result;
}

int modifyCourseStudnet( int rollNo, int courseCode, int marks ) {
    student* student = findStudent( rollNo );
    if( student == NULL ) {
	fprintf( stderr, "Cannot modify course %d courseCode to %d student(student not found).\n", courseCode, rollNo );
        return 0;
    }

    int result = modifyCourse( &( student -> courses ), courseCode, marks );

    return result;
}

void writeStudentData( FILE* outputFile ) {
    student* student = students;
	if( student == NULL ) {
		fprintf( stderr, "No data to write(student is empty)\n" );
		return;
	}

	while( student -> next != NULL ) {
		student = student -> next;
	}

	while( student != NULL ) {
		fprintf( outputFile, "%d, %s, %0.1f, %d\n", student -> rollNo, student -> name, student -> cgpa, student -> numSubjects );
		course* course = student -> courses;
		while( course -> next != NULL ) {
			course = course -> next;
		}
		while( course != NULL ) {
			fprintf( outputFile, "%d, %d\n", course -> courseCode, course -> marks );
			course = course -> prev;
		}
		student = student -> prev;
	}

	// printf( "Data written to file\n" );

	return;
}
