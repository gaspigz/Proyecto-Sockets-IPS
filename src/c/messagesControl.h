#define __MESSAGESCONTROL_H__

#include <stddef.h>

/**
* leerMensajes: recibe un mensaje por un socket y evalúa el retorno. Indica si hubo algún error.
*/
int leerMensajes(int socket_emisor, char message[]);

/**
* enviarMensajes: envía un mensaje a socket_desc. Puede funcionar para servidor (serverOrClient = 0) o cliente (serverOrClient = 1), aunque esta bandera sólo cambia si el mensaje ya está almacenado en message o si se debe pedir al usuario que lo ingrese. 
*/
int enviarMensajes(int socket_desc, char* message, int serverOrClient);