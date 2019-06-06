#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h>   //inet_addr
#include <unistd.h>     //write
#include <pthread.h>   //for threading , link with lpthread
#include <time.h>

int i = 0;

void* count(int num)
{
    i++;
    printf("Thread %d : i = %d\n",num, i);
}

int main()
{
    pthread_t thread;

    for(int j = 0; j < 3; j++)
    {
        pthread_create(&thread, NULL, count, j);
        pthread_join(thread, NULL);
    }
    return 0;
}