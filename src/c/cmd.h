#include "messagesControl.h"


/**
* cmd_QUIT: Termina la coneccion y realiza los frees.
*/
void cmd_QUIT (int socket_server, int socket_client, struct sockaddr_in* addressP);

/**
* cmd_USER:
*/
void cmd_USER (int socket_server, int socket_client, struct sockaddr_in* addressP);

/**
* cmd_PASS:
*/
void cmd_PASS (int socket_server, int socket_client, struct sockaddr_in* addressP);

/**
* cmd_command: Lee message y retorna la funcion correspondiente al comando enviado.
*/
void* cmd_command(char* message);

