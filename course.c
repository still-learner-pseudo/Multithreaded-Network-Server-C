#include "course.h"

course* findCourse( course* course, int courseCode ) {
    if( course == NULL ) {
        return NULL;
    }

    while( course != NULL ) {
        if( course -> courseCode == courseCode ) {
            return course;
        }
        course = course -> next;
    }

    return NULL;
}

int addCourse( course** head, int courseCode, int marks ) {
    if( findCourse( *head, courseCode ) != NULL ) {
	fprintf( stderr, "Cannot add course %d courseCode(already exists).\n", courseCode );
        return 0;
    }

    course* newCourse = ( course* ) malloc( sizeof( course ) );
    if( newCourse == NULL ) {
	perror( "Malloc of course failed.\n" );
        return -1;
    }

    newCourse -> prev = NULL;
    newCourse -> courseCode = courseCode;
    newCourse -> marks = marks;
    newCourse -> next = *head;

    if( *head != NULL ) {
        ( *head ) -> prev = newCourse;
    }

    *head = newCourse;

    return 1;
}

int deleteCourse( course** head, int courseCode ) {
    course* delCourse = findCourse( *head, courseCode );
    if( delCourse == NULL ) {
	fprintf( stderr, "Cannot delete course %d courseCode(course doesn't exist)\n", courseCode );
        return 0;
    }
    
    if( delCourse -> prev != NULL ) {
        delCourse -> prev -> next = delCourse -> next;
    }
    else { // delCourse is the head
        *head = delCourse -> next;
    }

    if( delCourse -> next != NULL ) {
        delCourse -> next -> prev = delCourse -> prev;
    }

    free( delCourse );

    return 1;
}

int modifyCourse( course** head, int courseCode, int marks ) {
    course* modCourse = findCourse( *head, courseCode );
    if( modCourse == NULL ) {
	fprintf( stderr, "Cannot modify course %d courseCode(course doesn't exist)\n", courseCode );
        return 0;
    }

    modCourse -> marks = marks;

    return 1;
}
