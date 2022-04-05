#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h> 

int leerMensajes(int new_socket, char message[]){
    int valread;
    char *quitMSG = "El cliente se desconecto";
     

    if (read( new_socket , message, 1024)) < 0) //Aca message es el mensaje que recibimos
    { 
        perror("No se pudo leer el mensaje"); 
        exit(EXIT_FAILURE); 
    } 

    switch (message):
        case "quit":
            send(new_socket , quitMSG , strlen(quitMSG) , 0 );
            close(server_fd);
	        close(new_socket);
            break;
}

int main(int argc, char *argv[]) 
{ 
	//server_fd: socket file descriptor; new_socket: el socket de destino; valread: la cant de caracteres que leídos
    int server_fd, new_socket;
    char buffer[1024] = {0};  
	
    struct sockaddr_in address; //Socket por donde el servidor escucha
    
	int addrlen = sizeof(address);  
	
    int puertoSocket; //En este trabajo, se pidió que sea el 21
	
    puertoSocket = atoi(argv[1]);

    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) // SOCK_STREAM DETERMINA QUE USAREMOS TCP, AF_INET ES EL TIPO DE IP (IPv4) Y EL 0 PROTOCOLO IP (default). Si hay un error de creación del socket, devuelve -1.
    { 
        perror("socket failed"); 

        exit(EXIT_FAILURE); 
    } 

    
    address.sin_family = AF_INET; //AF_INET ES EL TIPO DE IP (IPv4)

    address.sin_addr.s_addr = INADDR_ANY; //IP DE LA PC DONDE ESTA EL SERVIDOR, INADDR_ANY ES LA IP LOCAL

    address.sin_port = htons(puertoSocket); //htons(80) ES LA FUNCION QUE OBTIENE EL PUERTO

       

    // Forcefully attaching socket to the PORT

    if (bind(server_fd, (struct sockaddr *)&address, addrlen)<0) //LE ASIGNA LA DIRECCION AL SOCKET
    { 
        perror("bind failed"); 

        exit(EXIT_FAILURE); 
    } 

    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 

        exit(EXIT_FAILURE); 
    } 
    
	//¿Acepta al primer socket de la lista de solicitudes?
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    //Si acepta, se queda escuchando por el nuevo socket y almacena lo recibido en el buffer
    //Si pasamos estos 3 if sin errores, es que el servidor está escuchando en el puerto que le piden
    printf("El servidor está escuchando en el puerto %d\n", puertoSocket);
	
	 //Lectura
    leerMensajes(new_socket, buffer);

	//Envía una respuesta al cliente
    char *hello = "Hello from server";
    send(new_socket , hello , strlen(hello) , 0 ); 

    printf("Hello message sent\n"); 

	
    return 0; 
} 
 