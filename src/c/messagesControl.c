#include "messagesControl.h"
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#define MAX_BUFFER_DEF 1024

int leerMensajes(int socket_emisor, char message[]){

    if ((read( socket_emisor, message, 1024)) < 0) //Aca message es el mensaje que recibimos
    { 
        perror("No se pudo leer el mensaje"); 
        exit(EXIT_FAILURE); 
    } 
	
    printf("Mensaje recibido: %s\n", message); // Para comprobar, eliminar al terminar el código
    return 0;
        
}

int enviarMensajes(int socket_desc, char *message, int serverOrClient){ //1 = client, 0 = server
	
	if(serverOrClient){ //Si es cliente
		char temp[MAX_BUFFER_DEF];
		
		printf("Ingrese el mensaje que desea enviar: ");
		scanf("%[^\n]", temp)  ; 	
		getchar() ;	
		
		message = malloc(sizeof(char) * strlen(temp) + 1);
		
		strcpy(message, temp); 
	}
	
	if( send(socket_desc, message, strlen(message), 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	
	puts("Data Sent\n");

	if(serverOrClient) free(message);
	return 0;
}
