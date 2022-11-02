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
#define SERVERPORT 5820

int main()
{
    struct sockaddr_in servizio, addr_remoto; // record con i dati del server e del client
    int socketfd, soa, fromlen = sizeof(servizio), cnt;
    char str[DIM], src[1], counter[1];
    // definizione dei dati del socket
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    // impostazione del transport endpoint del server
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    // leghiamo l'indirizzo al transport endpoint
    bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));
    // poniamo il server in ascolto delle richieste dei client
    listen(socketfd, 10); // può attendere fino a 10 client
    // ciclo infinito
    for (;;)
    {
        printf("\n\nServer in ascolto...");

        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, &fromlen);
        // legge dal client
        read(soa, str, sizeof(str));
        read(soa, src, sizeof(src));

        cnt = 0;
        for(int i = 0; i < DIM; i++){
            if(str[i] == src[0]){
                cnt++;
            }
        }

        counter[0] = cnt;

        printf("Stringa ricevuta: %s\n", str);
        printf("Carattere ricevuto: %s\n", src);
        printf("Contatore: %d - %s\n", cnt, counter);

        //write(socketfd,counter,sizeof(counter));

        close(soa);
    }

    return 0;
}