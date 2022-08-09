#include "mesg.h"

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
    char f = '\0';
    FILE *fd;
    Message m;
    key_t key;
    int msgid,length,n,i = 0;
    char count[100];

    printf("\n\t.:CLIENT:.\n");

    if ((key = ftok("server", 'A')) < 0)
    {
        perror("\n\tError (client - ftok)\n");
        exit(EXIT_FAILURE);
    }

    printf("\n\tGet a key\n");
    m.mtype = 1L;

    if((msgid = msgget(key, 0)) < 0)
    {
        perror("\n\tError (client - msgget)\n");
        exit(EXIT_FAILURE);
    }
    printf("\tGet access to messages\n");
    printf("Enter message:\n");
    while ((f = getchar()) != '\n')
    {
        count[i++] = f;
        if(count[i-1] == 'e' && count[i-2] == 'y' && count[i-3] == 'b')
        {
            length = sprintf(m.buff, count);
            msgsnd(msgid, (void*)&m, length, 0);
            printf("Bye!!\n");
            exit(EXIT_SUCCESS);
        }
    }

    length = sprintf(m.buff, count);

    if ((msgsnd(msgid, (void*)&m, length, 0)) != 0)
    {
        perror("\n\tError (client - msgsnd)\n");
        exit(EXIT_FAILURE);
    }

    printf("Message: \"%s\" Sent\n", m.buff);

    n = msgrcv(msgid, &m,sizeof(m), m.mtype, 0);
    printf("\nRecived message:%s\n", m.buff);

    if(msgctl(msgid,IPC_RMID,0) < 0)
    {
        perror("\n\tError (client - msgctl\n");
        exit(EXIT_FAILURE);
    }

    printf("\n\tMessage ID has deleted\n");
    fclose(fd);
    return 0;
}
