// server for stop and wait

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

void main()
{
	int server_sock, client_sock;
	struct sockaddr_in server_addr, client_addr;
	socklen_t server_len = sizeof(server_addr);
	socklen_t client_len = sizeof(client_addr);
	int seq = 0;
	srand(time(NULL));

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

	while (1)
	{
		int received = recv(client_sock, buffer, sizeof(buffer), 0);
		
		if (received <= 0)
		{
			break;
		}
		
		buffer[received] = '\0';
		printf("Received %s from client\n", buffer);

		// simulate ACK loss
		int loss = rand() % 2;
		if (loss == 0)
		{
			printf("Simulating lost ACK for sequence no. %d\n", seq);
			continue;
		}

		// simulate delayed ACK
		int delay = rand() % 2;
		
		if (delay == 1)
		{
			printf("Simulating delayed ACK for sequence no. %d\n", seq);
			sleep(1);
		}

		snprintf(buffer, sizeof(buffer), "ACK %d", seq);
		send(client_sock, buffer, strlen(buffer), 0);
		printf("Sent %s\n", buffer);

		// toggle sequence number for the next frame
		seq ^= 1;
	}

	close(client_sock);
	close(server_sock);
}

