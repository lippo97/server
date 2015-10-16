#include "socket.h"

int main(){
	int my_sock;

	my_sock = new_socket(0);

	try_connection(my_sock,LOCALHOST,3002);

	char* buffer;
	buffer = (char*) malloc(sizeof(char)*MAX_CHARS);
	memcpy(buffer,"ciao",sizeof("ciao"));
	int i;
	for (i = 0; i < 3; i++) {
		write_message(my_sock, buffer);
	}
	return 0;
}
