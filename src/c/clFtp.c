//Recibe como argumento una IP y el puerto que le pusimos al sv
//Ejemplo: ./clFtp

#include "messagesControl.h"

int main(int argc , char *argv[])
{
    //SOCKET CREATION
	int socket_desc; //ESTA ES LA DESCRIPCION DEL SOCKET QUE SE CREA CON socket()
    int puerto_mandado = puerto_mandado = atoi(argv[2]); //En este trabajo, se pidió que sea el 21
	char *ip_mandada = argv[1];
	char temp[MAX_BUFFER_DEF]; //String temporal para guardar cadenas de char de manera dinamica
    
    printf("IP MANDADA: %s\tPUERTO MANDADO: %d\n\n", ip_mandada, puerto_mandado); //Print temporal

	// SOCK_STREAM DETERMINA QUE USAREMOS TCP, AF_INET ES EL TIPO DE IP (IPv4) Y EL 0 PROTOCOLO IP (default). Si hay un error de creación del socket, devuelve -1.
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	
	if (socket_desc == -1)
	{
		perror("Could not create socket");
	}
	
    struct sockaddr_in server; //server ES UNA STRUCT DE TIPO sockaddr_in

    //Descripcion del servidor
    server.sin_addr.s_addr = inet_addr(ip_mandada); //IP DE LA PC DONDE ESTA EL SERVIDOR
	server.sin_family = AF_INET;   //AF_INET ES EL TIPO DE IP (IPv4)
	server.sin_port = htons( puerto_mandado );  //htons(80) ES LA FUNCION QUE OBTIENE EL PUERTO

	//Connect to remote server
	if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}
	
	puts("Connected");
	
    //Send some data
	
	for(int i = 0; i < 5; i++){				//TODO: Hacer una funcion que haga esto (Y quizas una libreria?)
		char* message = NULL;
		printf("Ingrese el mensaje que desea enviar: ");
		scanf("%[^\n]", temp)  ; 	
		getchar() ;	
		message = malloc(sizeof(char) * strlen(temp) + 1);
		
		strcpy(message, temp); 
		enviarMensajes(socket_desc, message);
		free(message);	
	
	}
	// TODO: que si el cliente manda "quit" se desconecte.
	
	close(socket_desc);

	return 0;
}