// server for SMTP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void main()
{
	int server_sock, client_sock;
	struct sockaddr_in server_addr, client_addr;
	socklen_t server_len = sizeof(server_addr);
	socklen_t client_len = sizeof(client_addr);

	server_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (server_sock == -1)
	{
		printf("Socket failed\n");
		return;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(8080);

	if (bind(server_sock, (struct sockaddr *)&server_addr, server_len) == -1)
	{
		printf("Bind failed\n");
		return;
	}

	listen(server_sock, 1);
	printf("Server is listening on port %d...\n", 8080);

	client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);

	if (client_sock == -1)
	{
		printf("Accept failed\n");
		return;
	}

	char buffer[1024];
	int received = recv(client_sock, buffer, sizeof(buffer), 0);
	buffer[received] = '\0';
	printf("Client: %s\n", buffer);

	printf("Enter command (RCPT TO): ");
	gets(buffer);
	send(client_sock, buffer, strlen(buffer), 0);
	
	received = recv(client_sock, buffer, sizeof(buffer), 0);
	buffer[received] = '\0';
	if (!(strchr(buffer, '@') && strchr(buffer, '.')))
	{
		printf("Invalid sender email. Closing connection.\n");
		close(client_sock);
		return;
	}
	printf("Sender: %s\n", buffer);

	printf("Enter command (MAIL FROM): ");	
	gets(buffer);
	send(client_sock, buffer, strlen(buffer), 0);

	received = recv(client_sock, buffer, sizeof(buffer), 0);
	buffer[received] = '\0';
	if (!(strchr(buffer, '@') && strchr(buffer, '.')))
	{
		printf("Invalid recipient email. Closing connection.\n");
		close(client_sock);
		return;
	}
	printf("Recipient: %s\n", buffer);

	printf("Enter command (DATA): ");
	gets(buffer);
	send(client_sock, buffer, strlen(buffer), 0);

	printf("\n	Begin body	\n");
	while (1)
	{
		received = recv(client_sock, buffer, sizeof(buffer), 0);
		buffer[received] = '\0';

		if (strcmp(buffer, "QUIT") == 0)
		{
			break;
		}

		printf("%s\n", buffer);
	}
	printf("	End body	\n");

	close(client_sock);
	close(server_sock);
}
