build:
	gcc server.c -o server -lpthread
	gcc client.c -o client
runServer:
	./server
runClient:
	./client 127.0.0.1
clean:
	rm -f client_file/*.txt
	rm -f server_file/*.txt
file:
	mkdir client_file
	mkdir server_file