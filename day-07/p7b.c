// client for SMTP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void main()
{
	int client_sock;
	struct sockaddr_in server_addr;
	socklen_t server_len = sizeof(server_addr);

	client_sock = socket(AF_INET, SOCK_STREAM, 0);
	
	if (client_sock == -1)
	{
		printf("Socket failed\n");
		return;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
	
	if (connect(client_sock, (struct sockaddr *)&server_addr, server_len) == -1)
	{
		printf("Connect failed\n");
		return;
	}

	char buffer[1024];
	printf("Enter command (HELLO): ");
	gets(buffer);
	send(client_sock, buffer, strlen(buffer), 0);

	int received = recv(client_sock, buffer, sizeof(buffer), 0);
	buffer[received] = '\0';
	printf("Server: %s\n", buffer);

	printf("Enter sender email: ");
	gets(buffer);
	send(client_sock, buffer, strlen(buffer), 0);

	received = recv(client_sock, buffer, sizeof(buffer), 0);
	buffer[received] = '\0';	
	printf("Server: %s\n", buffer);

	printf("Enter recipient email: ");
	gets(buffer);
	send(client_sock, buffer, strlen(buffer), 0);
	
	received = recv(client_sock, buffer, sizeof(buffer), 0);
	buffer[received] = '\0';
	printf("Server: %s\n", buffer);

	printf("Enter email body (type QUIT to end):\n");
	while (1)
	{
		gets(buffer);
		send(client_sock, buffer, strlen(buffer), 0);

		if (strcmp(buffer, "QUIT") == 0)
		{
			break;
		}
	}

	close(client_sock);
}
