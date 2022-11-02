#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define DIM 512
#define SERVERPORT 1313

int main(int argc,char** argv)
{   
    struct sockaddr_in servizio;
    int socketfd;
    char str1[DIM], str2[DIM];

    // servizio -> Struct contenente i dati per la socket
    servizio.sin_family=AF_INET; // famiglia protocolli
    servizio.sin_addr.s_addr=htonl(INADDR_ANY); // indirizzo della socket, INADDR_ANY = Tutti gli indirizzi disponibili sulla macchina
    servizio.sin_port=htons(SERVERPORT); // porta della socket, definita all'inizio del programma

    socketfd=socket(AF_INET,SOCK_STREAM,0); //apro la socket

    connect(socketfd,(struct sockaddr*)&servizio,sizeof(servizio));
    
    printf("Inserisci la stringa\n");
    scanf("%s",str1);
    write(socketfd,str1,sizeof(str1));

    read(socketfd, str2, sizeof(str2));

    printf("\n%s", str2);
    
    close(socketfd);

    return 0;
}