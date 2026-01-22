client: client.o parser.o client_main.o
	gcc client.o parser.o client_main.o -o client

client_main.o: client_main.c client.h parser.h
	gcc -Wall -c client_main.c

client.o: client.c client.h client_server.h server.h
	gcc -Wall -c client.c

parser.o: parser.c parser.h client.h
	gcc -Wall -c parser.c

server: server.o student.o course.o server_main.o
	gcc server.o student.o course.o server_main.o -o server

server_main.o: server_main.c server.h
	gcc -Wall -c server_main.c

server.o: server.c server.h student.h course.h client_server.h
	gcc -Wall -Wextra  -c server.c

student.o: student.c student.h course.h
	gcc -Wall -Wextra -c student.c

course.o: course.c course.h
	gcc -Wall -c course.c

# 2104_2105: 2104_2105.o parser.o student.o course.o
# 	gcc 2104_2105.o student.o course.o parser.o -o 2104_2105

# 2104_2105.o: 2104_2105.c parser.h client.h student.h course.h
# 	gcc -Wall -c 2104_2105.c
	
# parser.o: parser.c parser.h client.h
# 	gcc -Wall -c parser.c

# student.o: student.c student.h course.h
# 	gcc -Wall -c student.c

# course.o: course.c course.h
# 	gcc -Wall -c course.c

# client.o : client.c client.h
# 	gcc -Wall -c client.c

.PHONY: clean clean_client clean_server

clean_client:
	rm -f client client.o parser.o client_main.o

clean_server:
	rm -f server server.o student.o course.o server_main.o

clean: clean_client clean_server
	rm -f 2104_2105.out /tmp/client_server
