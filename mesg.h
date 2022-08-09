//файл содержит объявление структуры сообщения
#define MAXBUFF 80
#define PERM 0666
typedef struct our_msgbuf //имя структуры
{
long mtype; //тип сообщения
char buff[MAXBUFF] ;
}Message; //тип структуры
