#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h>   //inet_addr
#include <unistd.h>     //write
#include <pthread.h>   //for threading , link with lpthread
#include <time.h>

int numberBall;
int countBall = 0;
int *arr;
pthread_mutex_t mutex;

//the thread function
void *Play(void *);
 
int main(int argc , char *argv[])
{
    FILE *ballInfor;
    ballInfor = fopen("server_file/BallInfor.txt", "w");

    srand(time(NULL));
    //numberBall = rand() % (1000 - 100 + 1) + 100;
    numberBall = 10;
    arr = (int*)malloc(sizeof(int)*numberBall);
    for (int i = 0; i < numberBall; i++)
    {
        arr[i] = rand() % (500) + 1;
        fprintf(ballInfor, "%d\n", arr[i]);
    }
    fclose(ballInfor);

    int socket_desc , client_sock , c;
    struct sockaddr_in server , client;

    int num_Cl;
    printf("Enter number player: ");
    scanf("%d",&num_Cl);
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
	pthread_t thread_id[num_Cl];

    int countCl = 0;
	
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted");
         
        if( pthread_create(&thread_id[countCl], NULL, Play, (void*) &client_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }
        if(countCl == num_Cl - 1)
            break;
        else
        {
            countCl++;
        }
        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( thread_id , NULL);
        puts("Handler assigned");
    }

    for (int j = 0; j < num_Cl; j++)
        pthread_join(thread_id[j], NULL);
    
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
     
    return 0;
}

void *Play(void *socket_desc)
{
    int sock = *(int*)socket_desc;
    int read_size;
    char client_message[2000], cl_name[100];
     
    //Receive a message from client
    while(countBall < numberBall)
    {
        read_size = recv(sock , cl_name , 100 , 0);
        
        pthread_mutex_lock(&mutex);
        send(sock, &arr[countBall], sizeof(int), 0);
        printf("Send %d to %s...\n", arr[countBall], cl_name);
		
        countBall++;
        pthread_mutex_unlock(&mutex);
    }
    send(sock, 0, sizeof(int), 0);
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }

    pthread_mutex_destroy(&mutex);
    return 0;
} 