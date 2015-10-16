#include "socket.h"

int main(){
	int my_sock, connection_socket, their_port;
	char *their_ip_addr, *message;

	my_sock = new_socket_listen(3002,1);

	if (my_sock < 0){
		printf("Errore funzione new_socket_listen()");
		return -1;
	}

	struct sockaddr_in their_addr;
	socklen_t their_addr_len;
	their_addr_len = sizeof(their_addr);

	while(1){
		connection_socket = accept_connection(my_sock, &their_addr, &their_addr_len);
		if (connection_socket == -1){
			printf("Errore nella funzione accept_connection()\n");
			continue;
		}
		their_ip_addr = inet_ntoa(their_addr.sin_addr);
		their_port = their_addr.sin_port;
		printf("Connesso con @%s:%d\n",their_ip_addr,htons(their_port));
		while(1){
			message = read_message(connection_socket);
			if (message == NULL){
				printf("Errore nella funzione read_message()\n");
				continue;
			}
		}
		printf(">> %s\n",message);
		if (strcmp("exit",message) == 0)
			break;
	}

	printf("Chiusura del server.\n");
	return 0;
}
