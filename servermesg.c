#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

#include "mesg.h" //описание структуры сообщения






int main(void)
{
    FILE *fd; //дескриптор файла результатов
    Message m; //структура сообщения
    key_t key; //ключ сообщения
    int i=0;
    int msgid; //идентификатор сообщения
    int sum;
    int n; //количесво прочитанных байт
    int randomchislo;
    char count[100];

    srand ( time(NULL) );
    printf("\n.:SERVER:.\n");


    m.mtype=1L; //определяем тип сообщения

    if ((key = ftok("server", 'A')) < 0) //получаем ключ сообщения
    {
        perror("\nError (server - ftok)\n");
        exit(EXIT_FAILURE);
    }

    printf("\nGet a key\n\n");

    if((msgid = msgget(key, PERM|IPC_CREAT)) < 0) //получаем дескриптор сообщения
    {
        perror("\nError (server - msgget)\n");
        exit(EXIT_FAILURE);
    }
    n = msgrcv(msgid,&m,sizeof(m),m.mtype,0); //получаем сообщение
    printf("Received message: %s\n",m.buff);
    if (n > 0)
    {
        while(i < n)
        {
            i++;
            if(count[i-1] == 'e' && count[i-2] == 'y' && count[i-3] == 'b')
            {
                printf("Bye!\n");
                exit(EXIT_SUCCESS);
            }

        }
      i = 0;

      while(i < n)
      {
        randomchislo = rand() % 2;

        if(m.buff[i] == ' ')
        {
            i++;
            continue;
        }
        if(randomchislo == 1)
        {
            for(i;;i++)
            {
                if((m.buff[i] == ' ')||(i == n))
                break;
                m.buff[i] = 'M';
            }
        }
        else
        {
            for(i;;i++)
            if((m.buff[i] == ' ')||(i == n))
            break;
        }
      }
    }
    msgsnd(msgid, (void*)&m, n, 0);

    printf("\nSuccesfull, modified message sent!\n\n");
    fclose(fd);
    return 0;
    }
