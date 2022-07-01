ALL : file_server file_client
file_server : file_server.o
	gcc -o file_server file_server.o
file_client : file_client.o
	gcc -o file_client file_client.o
file_client.o : file_client.c
	gcc -c file_client.c
file_server.o : file_server.c
	gcc -c file_server.c
clean :
	$(RM) *.o file_server file_client
