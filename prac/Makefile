all : server client
client : client.o
	gcc -o client client.o
server : server.o
	gcc -o server server.o
client.o : client.c
	gcc -g -c client.c
server.o : server.c
	gcc -g -c server.c
clean :
	$(RM) *.o server client
