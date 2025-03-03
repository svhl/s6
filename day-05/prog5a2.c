// client for stop and wait

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

void main()
{
	int client_sock;
	struct sockaddr_in server_addr;
	socklen_t server_len = sizeof(server_addr);
	char buffer[1024];
	char message[1024];
	int seq = 0;
	srand(time(NULL));

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

	struct timeval tv;
	// timeout in seconds
	tv.tv_sec = 2;
	// timeout in microseconds
	tv.tv_usec = 0;
	setsockopt(client_sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));

	printf("Enter a message:\n");
	gets(message);

	for (int i = 0; i < strlen(message); i++)
	{
		char lastsent = message[i];
		// simulate lost data
		int loss = rand() % 2;
		
		if (loss == 0)
		{
			printf("Simulating lost data for %c\n", lastsent);
			snprintf(buffer, sizeof(buffer), "%c", lastsent);
			send(client_sock, buffer, strlen(buffer), 0);
			printf("Resending %s\n", buffer);
		}
		
		else
		{
			snprintf(buffer, sizeof(buffer), "%c", lastsent);
			send(client_sock, buffer, strlen(buffer), 0);
			printf("Sending %s\n", buffer);
		}

		while (1)
		{
			int received = recv(client_sock, buffer, sizeof(buffer), 0);
			
			if (received <= 0)
			{
				printf("No ACK received, resending %s\n", buffer);
				send(client_sock, buffer, strlen(buffer), 0);
			}
			
			else
			{
				buffer[received] = '\0';
				printf("Received %s from server\n", buffer);
				break;
			}
		}
	}

	close(client_sock);
}

