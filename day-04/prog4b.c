// client for UDP

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
	// SOCK_DGRAM for UDP
	// 0 means system chooses the protocol
	client_sock = socket(AF_INET, SOCK_DGRAM, 0);

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

	char buffer[1024];
	printf("Enter a message: ");
	gets(buffer);
	sendto(client_sock, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, server_len);

	int received = recvfrom(client_sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, &server_len);
	// add eol
	buffer[received] = '\0';
	printf("Received from server: %s\n", buffer);

	close(client_sock);
}

