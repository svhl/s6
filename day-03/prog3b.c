// client for TCP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// for close()
#include <unistd.h>
// for network functions
#include <arpa/inet.h>

void main()
{
	int client_sock;
	// no need to define struct as already defined by <arpa/inet.h>
	struct sockaddr_in server_addr;
	// datatype for size of socket address structure
	socklen_t server_len = sizeof(server_addr);

	// AF_INET for IPv4 address
	// SOCK_STREAM for TCP
	// 0 means system chooses the protocol
	client_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (client_sock == -1)
	{
		printf("Socket failed\n");
		return;
	}

	// sin_family is address family (here IPv4)
	server_addr.sin_family = AF_INET;
	// sin_port to set port number
	// htons to make port number big endian
	server_addr.sin_port = htons(8080);
	// convert IP address from string to binary
	inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

	// server_addr is of type sockaddr_in
	// so we type cast to sockaddr
	// also we need pointer not the struct to server_addr
	// server_len because expects int
	if (connect(client_sock, (struct sockaddr *)&server_addr, server_len) == -1)
	{
		printf("Connect failed\n");
		return;
	}

	char buffer[1024];
	printf("Enter a message: ");
	gets(buffer);
	// 0 means no special flag parameters
	send(client_sock, buffer, strlen(buffer), 0);

	int received = recv(client_sock, buffer, sizeof(buffer), 0);
	// add eol
	buffer[received] = '\0';
	printf("Received from server: %s\n", buffer);

	close(client_sock);
}
