for anyone interested in the boring details, the client-server connection in this program works like so:
->the server is constantly listening on a socket for connection requests (this is done in a loop on the main thread)
->a client wants to connect
->the server makes a seperate thread and hands the client connection over to it.
this way each client has a personal connection to the server, and will not be affected by what other clients are doing.

the data transfer is done like so:
->the client reads a raw data stream (raw bytes) into a buffer.
->the buffer is sent to the server, which copies the bytes from the receiving buffer over into a .BIN file.
->keep repeating until all the data has been sent.
->filename is sent to server, for renaming the .BIN after transaction is finished.

the algorithms part is sort of finicky:
->filename string is hashed and that hashed value is added to an avl tree.
->searches are then done on this avl tree instead of the user's filesystem.
->this has the benefit of added security as well as speed.
->log file is created on server's first startup, which keeps track of all transactions.
->avl tree is built on the basis of log file after server restart.
->a database would have been much simpler to use and way faster, but 3rd semester yknow.
