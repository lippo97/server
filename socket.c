#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define LOCALHOST "127.0.0.1"
#define MAX_CHARS 256

int new_socket_listen (int port, int n_listen){
	if (n_listen < 1) n_listen = 1;

	int my_sock, retcode;

	my_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (my_sock == -1){
		perror("Errore funzione socket()");
		return -1;
	}

	struct sockaddr_in my_addr;
	memset(&my_addr,'\0',sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(port);
	/*my_addr.sin_addr.s_addr = inet_addr(LOCALHOST);*/
	my_addr.sin_addr.s_addr = INADDR_ANY;

	retcode = bind(my_sock, (struct sockaddr*) &my_addr, sizeof(my_addr));
	if (retcode == -1){
		perror("Errore funzione bind()");
		return -2;
	}

	retcode = listen(my_sock, n_listen);
	if (retcode == -1){
		perror("Errore funzione listen()");
		return -3;
	}

	return my_sock;

}

int accept_connection(int my_sock, struct sockaddr_in* their_sock, socklen_t* their_sock_len){
	int connection_socket;
	*their_sock_len = sizeof(*their_sock);

	connection_socket = accept(my_sock, (struct sockaddr*) their_sock, their_sock_len);
	if (connection_socket == -1){
		perror("Errore funzione accept()");
		return -1;
	}

	return connection_socket;
}

char* read_message(int connection_socket){
	int n_chars;
	char *buffer;

	buffer = (char*) malloc(sizeof(char)*MAX_CHARS);

	n_chars = read(connection_socket, buffer, MAX_CHARS);
	if (n_chars == -1){
		perror("Errore funzione read()");
		return NULL;
	}

	buffer[n_chars] = '\0';
	return buffer;
}

int main(){
	int my_sock, connection_socket, their_port;
	char *their_addr, *message;

	my_sock = new_socket_listen(3002,1);

	struct sockaddr_in their_sock;
	socklen_t their_sock_len;
	their_sock_len = sizeof(their_sock);

	while(1){
		connection_socket = accept_connection(my_sock, &their_sock, &their_sock_len);
		if (connection_socket == -1){
			printf("Errore nella funzione connection_socket()\n");
			continue;
		}
		their_addr = inet_ntoa(their_sock.sin_addr);
		their_port = their_sock.sin_port;
		printf("Connesso con @%s:%d\n",their_addr,their_port);
		message = read_message(connection_socket);
		if (message == NULL){
			printf("Errore nella funzione read_message()\n");
			continue;
		}
		printf(">> %s\n",message);
		if (strcmp("exit",message) == 0)
			break;
	}

	printf("Chiusura del server.\n");
	return 0;
}
