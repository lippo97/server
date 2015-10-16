#include "socket.h"
#define PORT 2560

int main(int argc, char** argv){
	if (argc != 2){
		printf("Usage: %s file\n",argv[0]);
	}

	FILE *f;
	f = fopen(argv[1],"r");
	if (f == NULL){
		printf("Errore in apertura del file");
		return -3;
	}

	int my_sock;
	my_sock = new_socket(0);
	if(my_sock < 0){
		printf("Errore funzione new_socket()");
		return -1;
	}

	int retcode;
	retcode = try_connection(my_sock,LOCALHOST,PORT);
	if (retcode < 0){
		printf("Errore funzione try_connection()");
		return -2;
	}


	return 0;
}
