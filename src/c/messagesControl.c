#include "messagesControl.h"
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#define MAX_BUFFER_DEF 1024

int leerMensajes(int socket_emisor, char* message){

    if ((read( socket_emisor, message, 1024)) < 0) //Aca message es el mensaje que recibimos
    { 
        perror("No se pudo leer el mensaje: "); 
        exit(EXIT_FAILURE); 
    } 
	
    printf("Mensaje recibido: %s\n", message); // Para comprobar, eliminar al terminar el código
    return 0;
        
}


//Pato: ¿No seria mejor que esta funcion funcione para tanto server como
//cliente sin necesidad de "serverOrClient"? Tipo, que le mandes directamente el mensaje y lo envie al socket
//que le mandes. (Lo puedo hacer yo)
int enviarMensajes(int socket_desc, char *message){
	if( send(socket_desc, message, strlen(message), 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	
	puts("Data Sent\n");
	return 0;
}
