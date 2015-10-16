#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define LOCALHOST "127.0.0.1"
#define MAX_CHARS 256

int new_socket (int); //0 se non si vuole specificare una porta
			//restituisce il file descriptor del socket
int new_socket_listen (int, int); //porta e numero massimo di connessioni in attesa
				//restituisce il file descriptor del socket
int try_connection (int, char *, int); //fd del socket, ip e porta a cui connettersi
					//-1 se la connessione non va a buon fine
int accept_connection(int, struct sockaddr_in*, socklen_t*); //fd del socket, indirizzo di un sockaddr_in e socklen_t che verranno modificati
								//ritorna il fd della connessione
int write_message (int, char *); //fd del socket, messaggio
					//ritorna > 0 se sono stati inviati tutti i dati
char* read_message(int); //fd della connessione
			//ritorna una stringa contenente il messaggio
