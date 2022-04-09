#include "messagesControl.h"
#define MAX_BUFFER_DEF 1024


int cmdAdmin(char* message, int socket_server, int socket_client, struct sockaddr_in* addressP){
	int flagEND = 0 ; // Esta variable indicará si se finalizó la sesión. 0 = no; 1 = sí.
	
	enviarMensajes(socket_client,"Ingrese un comando (HELP para la lista de comandos) \n:: ") ;
	char *comando = malloc(sizeof(char) * MAX_BUFFER_DEF) ;
	leerMensajes(socket_client,comando);	
	
	void (*exec_cmd)() = cmdServer(comando) ;

	if (exec_cmd == cmd_QUIT) flagEND = 1 ;

	while(exec_cmd == NULL){
		enviarMensajes(socket_client,"\nComando invalido. Por favor, vuelva a ingresar un comando. (El comando ""HELP"" muestra la lista de comandos).\n:: ") ;
		leerMensajes(socket_client,comando);

		exec_cmd = cmdServer(comando) ;
	}
	
	exec_cmd(socket_server,socket_client,addressP) ; //Mando todo pero porque todavía no sabemos bien qué necesitamos
	
	return flagEND;
}


int main(int argc, char *argv[]) { 

	//server_fd: socket file descriptor; new_socket: el socket de destino; valread: la cant de caracteres que leídos
    int server_fd, new_socket;  	
    struct sockaddr_in address; //Socket por donde el servidor escucha
	int addrlen = sizeof(address);  
	char buffer[MAX_BUFFER_DEF];
    int puertoSocket; //En este trabajo, se pidió que sea el 21
	
    puertoSocket = atoi(argv[1]);

    // Creating socket file descriptor 
	// SOCK_STREAM DETERMINA QUE USAREMOS TCP, AF_INET ES EL TIPO DE IP (IPv4) Y EL 0 PROTOCOLO IP (default). Si hay un error de creación del socket, devuelve -1.
	
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){ 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 

    
    address.sin_family = AF_INET; //AF_INET ES EL TIPO DE IP (IPv4)
    address.sin_addr.s_addr = INADDR_ANY; //IP DE LA PC DONDE ESTA EL SERVIDOR, INADDR_ANY ES LA IP LOCAL
    address.sin_port = htons(puertoSocket); //htons(80) ES LA FUNCION QUE OBTIENE EL PUERTO

      
    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0){ //LE ASIGNA LA DIRECCION AL SOCKET
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 

    if (listen(server_fd, 3) < 0) { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    
	//¿Acepta al primer socket de la lista de solicitudes?
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  (socklen_t*)&addrlen))<0) { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 

	int flagEND = 0;
	while(!flagEND) flagEND = cmdAdmin(buffer, server_fd, new_socket, &address);

    return 0; 
} 
 