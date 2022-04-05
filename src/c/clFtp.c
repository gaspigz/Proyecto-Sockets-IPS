//Recibe como argumento una IP y el puerto que le pusimos al sv
//Ejemplo: ./clFtp
#include <stdio.h>
#include <sys/socket.h> 
#include <string.h>

// IPv4 AF_INET sockets:
struct sockaddrx {
    unsigned short    sa_family;    // address family, AF_xxx
    char              sa_data[14];  // 14 bytes of protocol address
};

struct in_addrx {
    unsigned long s_addr;          // load with inet_pton()
};

struct sockaddr_inx {
    short            sin_family;   // e.g. AF_INET, AF_INET6
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addrx   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};





int main(int argc , char *argv[])
{
    //SOCKET CREATION
	int socket_desc; //ESTA ES LA DESCRIPCION DEL SOCKET QUE SE CREA CON socket()
    char *message;
    char *ip_mandada;
    int puerto_mandado;
    
    //PASAMOS DATOS POR ARGUMENTOS
    ip_mandada = argv[1];
    puerto_mandado = atoi(argv[2]);

    printf("IP MANDADA:%s PUERTO MANDADO: %d", ip_mandada, puerto_mandado);

	socket_desc = socket(AF_INET , SOCK_STREAM , 0); // SOCK_STREAM DETERMINA QUE USAREMOS TCP, AF_INET ES EL TIPO DE IP (IPv4) Y EL 0 PROTOCOLO IP
	
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	
    struct sockaddr_inx server; //server ES UNA STRUCT DE TIPO sockaddr_in

    //Descripcion del servidor

    server.sin_addr.s_addr = inet_addr(ip_mandada); //IP DE LA PC DONDE ESTA EL SERVIDOR
	server.sin_family = AF_INET;   //AF_INET ES EL TIPO DE IP (IPv4)
	server.sin_port = htons( puerto_mandado );  //htons(80) ES LA FUNCION QUE OBTIENE EL PUERTO

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}
	
	puts("Connected");
	
    //Send some data
	message = "Prueba mensaje.\n";
	if( send(socket_desc , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");

	return 0;
}