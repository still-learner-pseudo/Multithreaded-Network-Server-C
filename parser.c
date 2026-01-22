#include "parser.h"

#define BUFFER_SIZE 2048
int rollNumber = -1;

void fileReader( char* input, char* output ) {
	FILE *inputFile = fopen( input, "r" );
	if( !inputFile ) {
		perror( "Error with opening input file" );
		exit(-1);
	}
	// FILE *outputFile = fopen( output, "w" );
	// if( !outputFile ) {
	// 	perror( "Error with opening output file" );
	// 	fclose( inputFile );
	// 	exit(-1);
	// }

	char buffer[BUFFER_SIZE];

	// setSignalHandler();

	// if( openFIFO() == -1 ) {
	// 	perror( "Couldn't open fifo from the client side\n" );
	// 	exit(-1);
	// }

	while( fgets( buffer, BUFFER_SIZE - 1, inputFile ) != NULL ) {
		// printf( "%s\n", buffer );
		if( buffer[0] == '#' ) {
			// if( !strncasecmp( buffer,  "# Initial Database", strlen( "# Initial Database" ) ) ) {
			// 	while( fgets( buffer, BUFFER_SIZE - 1, inputFile ) !=  NULL ) {
			// 		if( buffer[0] == '#' ) {
			// 			fseek( inputFile, -strlen( buffer ) - 1, SEEK_CUR );
			// 			break;
			// 		}
			// 		else if( buffer[0] != '\n' ) {
			// 			addInitialData( buffer );
			// 		}
			// 	}
				// printf( "Database Initialized\n" );
			// }
			if( !strncasecmp( buffer, "# Add Student", strlen( "# Add Student" ) ) ) {
				while( fgets( buffer, BUFFER_SIZE - 1, inputFile ) !=  NULL ) {
					if( buffer[0] == '#' ) {
						fseek( inputFile, -strlen( buffer ) - 1, SEEK_CUR );
						break;
					}
					if( buffer[0] != '\n' ) {
						addStudentData( buffer );
					}
				}
				// printf( "Student Added\n" );
			}
			else if( !strncasecmp( buffer, "# Modify Student", strlen( "# Modify Student" ) ) ) {
				while( fgets( buffer, BUFFER_SIZE - 1, inputFile ) !=  NULL ) {
					if( buffer[0] == '#' ) {
						fseek( inputFile, -strlen( buffer ) - 1, SEEK_CUR );
						break;
					}
					if( buffer[0] != '\n' ) {
						modifyStudentData( buffer );
					}
				}
				// printf( "Student Modified\n" );
			}
			else if( !strncasecmp( buffer, "# Delete Student", strlen( "# Delete Student" ) ) ) {
				while( fgets( buffer, BUFFER_SIZE - 1, inputFile ) !=  NULL ) {
					if( buffer[0] == '#' ) {
						fseek( inputFile, -strlen( buffer ) - 1, SEEK_CUR );
						break;
					}
					if( buffer[0] != '\n' ) {
						deleteStudentData( buffer );
					}
				}
				// printf( "Student Deleted\n" );
			}
			else if( !strncasecmp( buffer, "# Add Course", strlen( "# Add Course" ) ) ) {
            	while( fgets( buffer, BUFFER_SIZE - 1, inputFile ) !=  NULL ) {
					if( buffer[0] == '#' ) {
						fseek( inputFile, -strlen( buffer ) - 1, SEEK_CUR );
						break;
					}
					if( buffer[0] != '\n' ) {
						addCourseData( buffer );
					}
				}
				// printf( "Course Added\n" );
            }
			else if( !strncasecmp( buffer, "# Modify Course", strlen( "# Modify Course" ) ) ) {
            	while( fgets( buffer, BUFFER_SIZE - 1, inputFile ) !=  NULL ) {
					if( buffer[0] == '#' ) {
						fseek( inputFile, -strlen( buffer ) - 1, SEEK_CUR );
						break;
					}
					if( buffer[0] != '\n' ) {
						modifyCourseData( buffer );
					}
				}
				// printf( "Course Modified\n" );
            }
            else if( !strncasecmp( buffer, "# Delete Course", strlen( "# Delete Course" ) ) ) {
            	while( fgets( buffer, BUFFER_SIZE - 1, inputFile ) !=  NULL ) {
					if( buffer[0] == '#' ) {
						fseek( inputFile, -strlen( buffer ) - 1, SEEK_CUR );
						break;
					}
					if( buffer[0] != '\n' ) {
						deleteCourseData( buffer );
					}
				}
				// printf( "Course Deleted\n" );
            }

		}
	}

	fclose( inputFile );
	// writeStudentData( outputFile );
	// writeToFile( output );
	// fclose( outputFile );
}

void addInitialData( char* buffer ) {
	char temp[BUFFER_SIZE];
	strcpy( temp, buffer );
	// char* token = strtok( temp, ", " );
	// int counter = 0;

	// while( token != NULL ) {
	// 	token = strtok( NULL, ", " );
	// 	counter++;
	// }

	// printf( "Counter: %d\n", counter );
    int rollNo, numSubjects;
    char name[100];
    float cgpa;

    trimSpaces( temp );

    int tokens = sscanf( temp, "%d, %99[^,], %f, %d", &rollNo, name, &cgpa, &numSubjects );

	if( tokens == 4 ) {

		// sscanf( buffer, "%d, %99[^, ], %f, %d", &rollNo, name, &cgpa, &numSubjects );

        	//trimSpaces( name );

		rollNumber = rollNo;

		addStudent( rollNo, name, cgpa, 0 );
	}
	else if( tokens == 2 ) {
		int rollNo, courseCode, marks;
		sscanf( buffer, "%d, %d", &courseCode, &marks );

		// printf( "Course code: %d, Marks: %d\n", courseCode, marks );

		if( rollNumber == -1 ) {
			perror( " No student found to add course\n" );
			exit(-1);
		}

		rollNo = rollNumber;

		addCourseStudent( rollNo, courseCode, marks );
	}
	else{
		fprintf(stderr, "Invalid data in initial database: %s\n", buffer);
		exit(-1);
	}
}

void addStudentData( char* buffer ) {
	char temp[BUFFER_SIZE];
	strcpy( temp, buffer );
	// char* token = strtok( temp, ", " );
	// int counter = 0;

	// while( token != NULL ) {
	// 	token = strtok( NULL, ", " );
    //     printf( "%s\n", token );
    //     if( !isspace( token ) )
	// 	    counter++;
	// }

	// printf( "Counter: %d\n", counter );

    int rollNo, numSubjects;
    char name[100];
    float cgpa;

    trimSpaces( temp );

    int tokens = sscanf( temp, "%d, %99[^,], %f, %d", &rollNo, name, &cgpa, &numSubjects );

	if( tokens == 4 ) {
		// printf( "%s\n", buffer );

		// sscanf( buffer, "%d, %99[^, ], %f, %d", &rollNo, name, &cgpa, &numSubjects );

        trimSpaces( name );

		addStudent( rollNo, name, cgpa, 0 ); //using 0 initial number of subjects
	}
	else{
		fprintf(stderr, "Invalid data in add student: %s\n", buffer);
		exit(-1);
	}
}

void modifyStudentData( char* buffer ) {
	char temp[BUFFER_SIZE];
	strcpy( temp, buffer );
	// char* token = strtok( temp, ", " );
	// int counter = 0;

	// while( token != NULL ) {
	// 	token = strtok( NULL, ", " );
	// 	counter++;
	// }

	// printf( "Counter: %d\n", counter );
    int rollNo;
    float cgpa;

    int tokens = sscanf( temp, "%d, %f", &rollNumber, &cgpa );

	if( tokens == 2 ) {

		sscanf( temp, "%d, %f", &rollNo, &cgpa );

		modifyStudent( rollNo, cgpa );
	}
	else{
		fprintf(stderr, "Invalid data in modify student: %s\n", buffer);
		exit(-1);
	}
}

void deleteStudentData( char* buffer ) {
	char temp[BUFFER_SIZE];
	strcpy( temp, buffer );
	// char* token = strtok( temp, ", " );
	// int counter = 0;

	// while( token != NULL ) {
	// 	token = strtok( NULL, ", " );
	// 	counter++;
	// }

	// printf( "Counter: %d\n", counter );

    int rollNo;
    int tokens = sscanf( temp, "%d", &rollNo );

	if( tokens == 1) {

		// sscanf( buffer, "%d", &rollNo );

		deleteStudent( rollNo );
	}
	else{
		fprintf(stderr, "Invalid data in delete student: %s\n", buffer);
		exit(-1);

	}
}

void addCourseData( char* buffer ) {
	char temp[BUFFER_SIZE];
	strcpy( temp, buffer );
	// char* token = strtok( temp, ", " );
	// int counter = 0;

	// while( token != NULL ) {
	// 	token = strtok( NULL, ", " );
	// 	counter++;
	// }

	// printf( "Counter: %d\n", counter );

    int rollNo, courseCode, marks;
    int tokens = sscanf( temp, "%d, %d, %d", &rollNo, &courseCode, &marks );

	if( tokens == 3 ) {

		// sscanf( buffer, "%d, %d, %d", &rollNo, &courseCode, &marks );

		addCourseStudent( rollNo, courseCode, marks );
	}
	else{
		fprintf(stderr, "Invalid data in add course: %s\n", buffer);
		exit(-1);
	}
}

void deleteCourseData( char* buffer ) {
	char temp[BUFFER_SIZE];
	strcpy( temp, buffer );
	// char* token = strtok( temp, ", " );
	// int counter = 0;

	// while( token != NULL ) {
	// 	token = strtok( NULL, ", " );
	// 	counter++;
	// }

	// printf( "Counter: %d\n", counter );

    int rollNo, courseCode;
    int tokens = sscanf( temp, "%d, %d", &rollNo, &courseCode );

	if( tokens == 2 ) {

		sscanf( buffer, "%d, %d", &rollNo, &courseCode );

		deleteCourseStudent( rollNo, courseCode );
	}
	else{
		fprintf(stderr, "Invalid data in delete course: %s\n", buffer);
		exit(-1);
	}
}

void modifyCourseData( char* buffer ) {
	char temp[BUFFER_SIZE];
	strcpy( temp, buffer );
	// char* token = strtok( temp, ", " );
	// int counter = 0;

	// while( token != NULL ) {
	// 	token = strtok( NULL, ", " );
	// 	counter++;
	// }

	// printf( "Counter: %d\n", counter );

    int rollNo, courseCode, marks;
    int tokens = sscanf( temp, "%d, %d, %d", &rollNo, &courseCode, &marks );

	if( tokens == 3 ) {

		sscanf( buffer, "%d, %d, %d", &rollNo, &courseCode, &marks );

		modifyCourseStudnet( rollNo, courseCode, marks );
	}
	else{
		fprintf(stderr, "Invalid data in modify course: %s\n", buffer);
		exit(-1);
	}
}

void trimSpaces(char* buffer) {
    if ( buffer == NULL ) {
        return;
    }

    int read = 0, write = 0;

    while ( buffer[read] != '\0' ) {
        if ( !isspace( ( unsigned char ) buffer[read] ) ) {
            buffer[write++] = buffer[read];
        }
        read++;
    }

    buffer[write] = '\0';
}
