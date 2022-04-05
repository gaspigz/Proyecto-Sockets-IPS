#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h> 

int main(int argc, char *argv[]) 
{ 
	//server_fd: socket file descriptor; new_socket: el socket de destino; valread: la cant de caracteres que leídos
    int server_fd, new_socket, valread; 
	
    struct sockaddr_in address; 
    
	//int opt = 1; 
    
	int addrlen = sizeof(address); 
		
	char buffer[1024] = {0}; 
    
	char *hello = "Hello from server"; 
	
    int puertoSocket; //En este trabajo, se pidió que sea el 21
	
    puertoSocket = atoi(argv[1]);

    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 

        exit(EXIT_FAILURE); 
    } 

       
    // Forcefully attaching socket to the port 8080 
/*    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 

        exit(EXIT_FAILURE); 
    } 
*/
    address.sin_family = AF_INET; 

    address.sin_addr.s_addr = INADDR_ANY; 

    address.sin_port = htons(puertoSocket); 

       

    // Forcefully attaching socket to the PORT

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
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
    valread = read( new_socket , buffer, 1024); 

    printf("%s\n",buffer ); 

	//Envía una respuesta al cliente
    send(new_socket , hello , strlen(hello) , 0 ); 

    printf("Hello message sent\n"); 

    return 0; 
} 
 