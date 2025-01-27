// server for UDP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// for close()
#include <unistd.h>
// for network functions
#include <arpa/inet.h>

void main()
{
	int server_sock;
	// no need to define struct as already defined by <arpa/inet.h>
	struct sockaddr_in server_addr, client_addr;
	// datatype for size of socket address structure
	socklen_t server_len = sizeof(server_addr);
	socklen_t client_len = sizeof(client_addr);

	// AF_INET for IPv4 address
	// SOCK_DGRAM for UDP
	// 0 means system chooses the protocol
	server_sock = socket(AF_INET, SOCK_DGRAM, 0);

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

	printf("Server is listening on port %d...\n", 8080);

	char buffer[1024];
	// sizeof(buffer)-1 because one byte reserved for eol
	int received = recvfrom(server_sock, buffer, sizeof(buffer)-1, 0, (struct sockaddr *)&client_addr, &client_len);
	// add eol
	buffer[received] = '\0';
	printf("Received from client: %s\n", buffer);

	printf("Enter a message: ");
	gets(buffer);
	sendto(server_sock, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, client_len);

	close(server_sock);
}

