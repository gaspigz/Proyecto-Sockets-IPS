#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#define MAX_BUFFER_DEF 1024
#define __MESSAGESCONTROL_H__

//TODO: Eliminar includes redundantes de los otros archivos.

#include <stddef.h>

/**
* leerMensajes: recibe un mensaje por un socket y evalúa el retorno. Indica si hubo algún error.
*/
int leerMensajes(int socket_emisor, char message[]);

/**
* enviarMensajes: envía un mensaje a socket_desc. 
*/
int enviarMensajes(int socket_desc, char* message);