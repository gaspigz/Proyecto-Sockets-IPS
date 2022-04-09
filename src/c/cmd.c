#include "cmd.h"

//Falta todo lo de los códigos de error y las funciones user y pass (eso incluye crear un struct usuario y almacenar los datos ahí. E implementar bien todo eso en el cliente

void cmd_QUIT (int socket_server, int socket_client, struct sockaddr_in* addressP){
		printf("\ncmd QUIT\n");
		close(socket_client);
		close(socket_server);		
}

void cmd_USER (int socket_server, int socket_client, struct sockaddr_in* addressP){
		printf("\ncmd USER\n");
}

void cmd_PASS (int socket_server, int socket_client, struct sockaddr_in* addressP){
		printf("\ncmd PASS\n");
}

void* cmd_command(char* message){
	//Verifico si el mensaje contiene algún comando
	//Note that strstr returns a pointer to the start of the word in sent if the word word is found, otherwise it returns NULL.
	
	//Si el mensaje contiene el comando "USER" y este comienza en el primer caracter enviado
	if(strstr(message,"USER") == message)
		return &cmd_USER;

	//Si el mensaje contiene el comando "PASS" y este comienza en el primer caracter enviado
	if(strstr(message,"PASS") == message)
		return &cmd_PASS;
	
	//Si el mensaje contiene el comando "QUIT" y este comienza en el primer caracter enviado
	if(strstr(message,"QUIT") == message)
		return &cmd_QUIT;
	
	return NULL;
}