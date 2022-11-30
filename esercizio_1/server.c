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
#define DIMR 1
#define SERVERPORT 1313

int ContaCaratteri(char str[DIM])
{
    int car = 0;
    for (int i = 0; i < DIM; i++)
    {
        // printf("%d", str[i]);
        if (str[i] != 0)
        {
            car++;
        }
        else if (str[i] == 0)
        {
            break;
        }
    }

    return car;
}

int ControlloPalindroma(char str[DIM], int strl)
{
    int n = strl - 1;

    for (int i = 0; i < n; i++)
    {
        if (strl % 2 != 0 && i == n / 2)
            break;
        if (str[i] != str[n - i])
            return 0;
    }

    return 1;
}

int main()
{
    struct sockaddr_in servizio, addr_remoto; // record con i dati del server e del client
    int socketfd, soa, fromlen = sizeof(servizio), strl, cp;
    char str[DIM], res[DIMR];
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

        printf("Stringa ricevuta: %s\n", str);

        strl = ContaCaratteri(str);
        
        cp = ControlloPalindroma(str, strl);

        if(cp == 0){
            res[0] = 'n';
        }
        if(cp == 1){
            res[0] = 'p';
        }

        write(soa, res, sizeof(res));

        close(soa);
    }

    return 0;
}