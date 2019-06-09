#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h>   //inet_addr
#include <unistd.h>     //write
#include <pthread.h>   //for threading , link with lpthread
#include <time.h>

int numCl = 0, countCl = 0;
int numberBall, countBall = 0;
int *arr, *result;
pthread_mutex_t mutex;

void *Play(void *);
 
int main(int argc , char *argv[])
{
    //open file  for ball infor
    FILE *ballInfor;
    ballInfor = fopen("server_file/BallInfor.txt", "w");

    //random array ball
    srand(time(NULL));
    numberBall = rand() % (1000 - 100 + 1) + 100;
    arr = (int*)malloc(sizeof(int)*numberBall);
    for (int i = 0; i < numberBall; i++)
    {
        arr[i] = rand() % (500 - 10 + 1) + 10;
        fprintf(ballInfor, "%d\n", arr[i]);
    }
    fclose(ballInfor);

    int socket_desc , client_sock , c;
    struct sockaddr_in server , client;

    // number client
    while(numCl > 9 || numCl < 3)
    {
        printf("Enter number player (from 3 to 9): ");
        scanf("%d", &numCl);
    }
    //array result
    result = (int*)malloc(sizeof(int)*numCl);
     
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
    puts("Bind done");
     
    //Listen
    listen(socket_desc , numCl);
     
    //Accept and incoming connection
    printf("Waiting for %d connections...\n", numCl);
    c = sizeof(struct sockaddr_in);

	//create thread
    pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t)*numCl);

    int countCl = 0;
	
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted");
         
        if( pthread_create(&threads[countCl], NULL, Play, (void*) &client_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }
        if(countCl == numCl - 1)
            break;
        else
        {
            countCl++;
        }
        //pthread_join( thread_id , NULL);
        puts("Handler assigned");
    }

    for (int j = 0; j < numCl; j++)
        pthread_join(threads[j], NULL);
    
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
    int read_size, length = 0;
    char client_message[2000], cl_name[100];

    int cl_id = countCl;
    // cho nay khong dung mutex do thread dang chay lan luot
    countCl++;
    printf("Client %d connected with sock_id %d!\n", countCl, sock);
    // wait for all connection

    while(countCl < numCl)
    {
        // strcpy(client_message, "wait");
        // send(sock, client_message, sizeof(client_message), 0);
    }
    strcpy(client_message, "start");
    send(sock, client_message, sizeof(client_message), 0);
    
    while(1)
    {
        // receive client name
        read_size = recv(sock , cl_name , 100 , 0);
        //cho nay su dung mutex vi cac thread dang chay song song. Neu dung trylock thi sex bi lap gia tri
        pthread_mutex_lock(&mutex);

        //neu mang het ball thi gui -1 cho client
        if (countBall >= numberBall)
        {
            int signal = -1;
            send(sock, &signal, sizeof(int), 0);
            pthread_mutex_unlock(&mutex);
            break;
        }
        send(sock, &arr[countBall], sizeof(int), 0);
		countBall++;

        pthread_mutex_unlock(&mutex);
    }

    int sum = 0;
    int *cl_arr;

    //nhan chieu dai mang cua client
    read(sock, (void*)&length, sizeof(int));
    cl_arr = (int*)malloc(sizeof(int)*length);
    //nhan mang tu client
    read(sock,(void*) cl_arr, sizeof(int)*length);

    //open file for client ball infor
    char filename[100];
    strcpy(filename, "server_file/");
    strcat(filename, cl_name);
    strcat(filename, ".txt");
    FILE *cl_file;
    cl_file = fopen(filename, "w");
    for(int v = 0; v < length; v++)
    {
        fprintf(cl_file, "%d\n", *(cl_arr + v));
        sum += cl_arr[v];
    }
    fclose(cl_file);

    result[cl_id] = sum;
    printf("%s id %d\n", cl_name, cl_id);

    while (result[numCl - 1] < 0)
    {
        //strcpy(client_message, "wait");
        //send(sock, client_message, sizeof(client_message), 0);
    }
    strcpy(client_message, "rank");
    send(sock, client_message, sizeof(client_message), 0);

    sleep(0.01);
    int rank = 1;
    for (int temp = 0; temp < numCl; temp++)
    {
        if(result[cl_id] < result[temp])
            rank++;
    }
    
    
    send(sock, &rank, sizeof(int), 0);

    FILE *res = fopen("server_file/final.txt", "a");
    fprintf(res, "Player %s has %d point and rank %d / %d\n", cl_name, sum, rank, numCl);
    printf("Player %s has %d point and rank %d / %d\n", cl_name, sum, rank, numCl);
    fclose(res);


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