#include "server.h"

int	main()
{
	struct sockaddr_in	address;
	int					addrlen;
	char				buffer[BUFFER_SIZE] = {0};

	int server_fd, new_socket;
	addrlen = sizeof(address);
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == 0)
	{
		perror("Socket failed");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("Listen failed");
		exit(EXIT_FAILURE);
	}
	printf("Server listening on port %d...\n", PORT);
	new_socket = accept(server_fd, (struct sockaddr *)&address,
			(socklen_t *)&addrlen);
	if (new_socket < 0)
	{
		perror("Accept failed");
		exit(EXIT_FAILURE);
	}
	read(new_socket, buffer, BUFFER_SIZE);
	printf("Received: %s\n", buffer);
	send(new_socket, buffer, strlen(buffer), 0);
	close(new_socket);
	close(server_fd);
	return (0);
}
