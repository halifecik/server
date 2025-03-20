#include "server.h"

int	main(void)
{
	int					sock;
	struct sockaddr_in	server_address;
	char				buffer[BUFFER_SIZE] = "Hello from client";

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("Socket failed");
		exit(EXIT_FAILURE);
	}
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0)
	{
		perror("Invalid address");
		exit(EXIT_FAILURE);
	}
	if (connect(sock, (struct sockaddr *)&server_address,
			sizeof(server_address)) < 0)
	{
		perror("Connection failed");
		exit(EXIT_FAILURE);
	}
	send(sock, buffer, strlen(buffer), 0);
	printf("Message sent\n");
	read(sock, buffer, BUFFER_SIZE);
	printf("Echo from server: %s\n", buffer);
	close(sock);
	return (0);
}
