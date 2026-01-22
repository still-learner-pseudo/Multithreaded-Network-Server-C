2104_2105: 2104_2105.o parser.o student.o course.o
	gcc 2104_2105.o student.o course.o parser.o -o 2104_2105

2104_2105.o: 2104_2105.c parser.h student.h course.h
	gcc -Wall -c 2104_2105.c
	
parser.o: parser.c parser.h student.h
	gcc -Wall -c parser.c

student.o: student.c student.h course.h
	gcc -Wall -c student.c

course.o: course.c course.h
	gcc -Wall -c course.c


clean:
	rm -f *.o 2104_2105 04_05.out
