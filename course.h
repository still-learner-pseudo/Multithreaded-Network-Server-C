#include <stdio.h>
#include <stdlib.h>

typedef struct course course;

struct course{
    course* prev;
    int courseCode;
    int marks;
    course* next;
};

course* findCourse( course* course, int courseCode );
int addCourse( course** head, int courseCode, int marks );
int deleteCourse( course** head, int courseCode );
int modifyCourse( course** head, int courseCode, int marks );
