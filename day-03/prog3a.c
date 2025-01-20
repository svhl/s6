// server for TCP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// for close()
#include <unistd.h>
// for network functions
#include <arpa/inet.h>

void main() {
	int server_sock, client_sock;
	// no need to define struct as already defined by <arpa/inet.h>
	struct sockaddr_in server_addr, client_addr;
	// datatype for size of socket address structure
	socklen_t server_len = sizeof(server_addr);
	socklen_t client_len = sizeof(client_addr);

	// AF_INET for IPv4 address
	// SOCK_STREAM for TCP
	// 0 means system chooses the protocol
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	
	if (server_sock == -1)
	{
		printf("Socket failed\n");
		return;
	}

	// sin_family is address family (here IPv4)
	server_addr.sin_family = AF_INET;
	// sin_addr is struct to represent IPv4 address
	// s_addr is int to store actual address
	// INADDR_ANY means accept connections from any IP address
	server_addr.sin_addr.s_addr = INADDR_ANY;
	// sin_port to set port number
	// htons to make port number big endian
	server_addr.sin_port = htons(8080);

	// server_addr is of type sockaddr_in
	// so we type cast to sockaddr
	// also we need pointer not the struct to server_addr
	// server_len because expects int
	if (bind(server_sock, (struct sockaddr *)&server_addr, server_len) == -1)
	{
		printf("Bind failed\n");
		return;
	}

	// 1 means only 1 client at a time
	listen(server_sock, 5);
	printf("Server is listening on port %d...\n", 8080);

	// &client_len because expects pointer
	// result needs to be stored in client_sock
	client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
	if (client_sock == -1)
	{
		printf("Accept failed\n");
		return;
	}

	char buffer[1024];
	// 0 means no special flag parameters
	int received = recv(client_sock, buffer, sizeof(buffer), 0);
	// add eol
	buffer[received] = '\0';
	printf("Received from client: %s\n", buffer);
	
	printf("Enter a message: ");
	gets(buffer);
	// 0 means no special flag parameters
	send(client_sock, buffer, strlen(buffer), 0);

	close(client_sock);
	close(server_sock);
}

