#include "socket.h"

int new_socket (int port){
	int my_sock;

	my_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (my_sock == -1){
		perror("Errore funzione socket()");
		return -1;
	}

	if (port > 0){
		int retcode;
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
	}

	return my_sock;
}

int new_socket_listen (int port, int n_listen){
	if (n_listen < 1) n_listen = 1;

	int my_sock, retcode;

	/*my_sock = socket(AF_INET, SOCK_STREAM, 0);*/
	/*if (my_sock == -1){*/
		/*perror("Errore funzione socket()");*/
		/*return -1;*/
	/*}*/

	/*struct sockaddr_in my_addr;*/
	/*memset(&my_addr,'\0',sizeof(my_addr));*/
	/*my_addr.sin_family = AF_INET;*/
	/*my_addr.sin_port = htons(port);*/
	/*[>my_addr.sin_addr.s_addr = inet_addr(LOCALHOST);<]*/
	/*my_addr.sin_addr.s_addr = INADDR_ANY;*/

	/*retcode = bind(my_sock, (struct sockaddr*) &my_addr, sizeof(my_addr));*/
	/*if (retcode == -1){*/
		/*perror("Errore funzione bind()");*/
		/*return -2;*/
	/*}*/

	my_sock = new_socket(port);
	if (my_sock < 0){
		printf("Errore funzione new_socket()");
		return -2;
	}

	retcode = listen(my_sock, n_listen);
	if (retcode == -1){
		perror("Errore funzione listen()");
		return -3;
	}

	return my_sock;

}

int try_connection (int my_sock, char * ip_addr, int port){
	struct sockaddr_in dest_addr;

	memset(&dest_addr, '\0', sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(port);
	dest_addr.sin_addr.s_addr = inet_addr(ip_addr);

	int retcode;

	retcode = connect(my_sock,(struct sockaddr*) &dest_addr, sizeof(dest_addr));
	if (retcode == -1){
		perror("Errore funzione connect()");
		return -1;
	}

	return retcode;
}

int accept_connection(int my_sock, struct sockaddr_in* their_addr, socklen_t* their_addr_len){
	int connection_socket;
	*their_addr_len = sizeof(*their_addr);

	connection_socket = accept(my_sock, (struct sockaddr*) their_addr, their_addr_len);
	if (connection_socket == -1){
		perror("Errore funzione accept()");
		return -1;
	}

	return connection_socket;
}

int write_message (int my_sock, char * buffer){
	int retcode;
	int len = sizeof(buffer);
	retcode = write(my_sock,buffer,len);
	if (retcode != len){
		printf("Errore funzione write():non tutti i dati non sono stati inviati: %i", retcode-len);
		return retcode - len;
	}
	return retcode;
}

char* read_message(int connection_socket){
	int n_chars;
	char *buffer;

	buffer = (char*) malloc(sizeof(char)*MAX_CHARS);

	n_chars = read(connection_socket, buffer, MAX_CHARS-1);
	if (n_chars == -1){
		perror("Errore funzione read()");
		return NULL;
	}

	buffer[n_chars] = '\0';
	return buffer;
}

int send_txt_file(int my_sock, FILE *f){
	
}
