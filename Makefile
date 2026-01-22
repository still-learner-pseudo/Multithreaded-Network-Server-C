
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L -MMD -MP
LDFLAGS = -lpthread

CLIENT_OBJS = client.o parser.o client_main.o
SERVER_OBJS = server.o student.o course.o server_main.o

all: server client

server: $(SERVER_OBJS)
	@echo "Linking Server..."
	$(CC) $(SERVER_OBJS) -o server $(LDFLAGS)

client: $(CLIENT_OBJS)
	@echo "Linking Client..."
	$(CC) $(CLIENT_OBJS) -o client

%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning artifacts..."
	rm -f server client *.o *.d 2104_2105.out

-include $(CLIENT_OBJS:.o=.d)
-include $(SERVER_OBJS:.o=.d)

.PHONY: all clean
