The client-server application only supports single client to server not multiple client to server.

"SIGPIPE" handling is done gracefully so that if the server is quitting due to some unexpected reason it terminates the client gracefully(exit is called, Fifo is unlinked, all fd's are closed by exit).

If client is started first but the server is not yet started, it tries for 30 times by waiting 1 second before it tries again(out of 30 tries), if the server opens within that time then the client and server can communicate, but if the client exceeded the time, then the client is exited gracefully by unlinking fifo and calling exit.

In the server added a Note saying to delete the file if you are trying to add same roll number or course code, it will print error messages in console telling that student/course with id already exists.

Server is a process that never ends until it is explicitly killed.

In parser there is a scope to improve the way the comparision is done(by using finite automata concept said by Anupama mam) -- this is incomplete, will try to do it in future revisions.

No signal handling is done in server and there is only SIGPIPE signal handling in client(to not terminate the process but exit the process gratefully).