# Student Database Management System

A client-server application implemented in C for managing student records and course enrollments over a TCP network. The server maintains an in-memory database using linked list data structures and supports concurrent client connections through multithreading.

---

## Overview

This system provides a networked interface for performing CRUD (Create, Read, Update, Delete) operations on student records and their associated courses. The architecture separates client-side parsing and server-side database management, enabling multiple clients to interact with a centralized student database simultaneously.

---

## Key Features

- **In-Memory Database:** Student records and course enrollments are stored in memory using doubly-linked lists, providing efficient insertion, deletion, and traversal operations.

- **Concurrent Client Handling:** The server spawns a separate thread for each connected client, enabling simultaneous operations from multiple clients. Thread synchronization is achieved using POSIX semaphores to protect shared database state.

- **Network Communication:** Client-server communication occurs over TCP sockets using a custom binary protocol for efficient data transmission.

- **Persistent Output:** After each operation, the server writes the complete database state to `2104_2105.out`, maintaining a snapshot of all student records and their courses.

- **Command File Parser:** The client reads commands from a text file and translates them into network requests, supporting batch operations on the student database.

---

## Technical Architecture

### Data Structures

- **Student Record (Doubly-Linked List):**  
  Each student node contains roll number, name, CGPA, number of subjects, and a pointer to a linked list of enrolled courses.

- **Course Record (Doubly-Linked List):**  
  Each course node contains a course code and marks, linked to a specific student.

### Server Architecture

- **Main Thread:** Accepts incoming TCP connections on a specified IP address and port.
- **Worker Threads:** Each client connection is handled by a dedicated thread that processes requests sequentially.
- **Synchronization:** A POSIX semaphore protects the shared student database from race conditions during concurrent read/write operations.
- **Persistence:** After each database modification, the entire student database is written to `2104_2105.out`.

### Client Architecture

- **File-Based Input:** Reads operation commands from a text file with sections marked by headers (e.g., `# Add Student`, `# Modify Course`).
- **Binary Protocol:** Sends structured requests to the server containing operation type and relevant data.
- **Response Handling:** Receives acknowledgment messages with status codes (200 for success, 404 for failure).

---

## Supported Operations

1. **Add Student:** Insert a new student with roll number, name, CGPA, and number of subjects.
2. **Delete Student:** Remove a student and all associated course records.
3. **Modify Student:** Update the CGPA of an existing student.
4. **Add Course:** Enroll a student in a course with a specified course code and marks.
5. **Delete Course:** Remove a course enrollment from a student's record.
6. **Modify Course:** Update the marks for a student's existing course enrollment.

---

## Building the Project

Use the provided Makefile to compile both server and client executables:

```bash
make
```

This generates two executables:
- `server` - The database server
- `client` - The client program

To clean build artifacts:

```bash
make clean
```

---

## Usage

### Starting the Server

Run the server by specifying the IP address and port:

```bash
./server <server_ip> <server_port>
```

Example:

```bash
./server 192.168.0.101 8080
```

**Requirements:**
- Port must be in the range 4097-65535
- Server listens for incoming client connections on the specified IP and port

### Running the Client

Execute the client with an input file, server IP, and port:

```bash
./client <input_file> <server_ip> <server_port>
```

Example:

```bash
./client input1.txt 192.168.0.101 8080
```

### Input File Format

The input file should contain sections marked with headers, followed by comma-separated data:

```
# Add Student
<rollNo>, <name>, <cgpa>, <numSubjects>

# Modify Student
<rollNo>, <cgpa>

# Delete Student
<rollNo>

# Add Course
<rollNo>, <courseCode>, <marks>

# Modify Course
<rollNo>, <courseCode>, <marks>

# Delete Course
<rollNo>, <courseCode>
```

### Multiple Concurrent Clients

The system supports multiple simultaneous clients. Use the provided `run.sh` script or run multiple client instances:

```bash
./client input1.txt 192.168.0.101 8080 &
./client input2.txt 192.168.0.101 8080 &
./client input3.txt 192.168.0.101 8080 &
```

---

## Output

The server generates `2104_2105.out` containing the current state of the database after each operation:

```
<rollNo>, <name>, <cgpa>, <numSubjects>
<courseCode>, <marks>
<courseCode>, <marks>
<rollNo>, <name>, <cgpa>, <numSubjects>
...
```

Students are written in reverse insertion order, and courses for each student are also written in reverse order.

---

## Technical Details

- **Language:** C (C11 standard)
- **Platform:** POSIX-compliant systems (Linux/Unix)
- **Threading:** POSIX Threads (pthread)
- **Synchronization:** POSIX Semaphores
- **Networking:** BSD Sockets (TCP/IP)
- **Compiler:** GCC with flags: `-Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L`

---

## File Structure

```
├── client.c              # Client-side socket communication functions
├── client.h              # Client function declarations
├── client_main.c         # Client entry point
├── client_server.h       # Shared protocol definitions
├── course.c              # Course linked list operations
├── course.h              # Course structure and function declarations
├── makefile              # Build configuration
├── parser.c              # Input file parsing logic
├── parser.h              # Parser function declarations
├── server.c              # Server request handling and threading
├── server.h              # Server function declarations
├── server_main.c         # Server entry point and socket initialization
├── student.c             # Student database operations
├── student.h             # Student structure and function declarations
└── run.sh                # Script to run multiple concurrent clients
```

---

## Author

**Saathvikk Muthyala**  
Email: saathvikkmuthyala@gmail.com  
GitHub: [still-learner-pseudo](https://github.com/still-learner-pseudo)
