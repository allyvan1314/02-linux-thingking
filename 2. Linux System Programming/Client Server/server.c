#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h>   //inet_addr
#include <unistd.h>     //write
#include <pthread.h>   //for threading , link with lpthread
#include <time.h>

int numberBall, countBall = 0;
int *arr;
pthread_mutex_t mutex;
int num_Cl, count_Cl = 0;
int cl_id;

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
        arr[i] = rand() % (500 - 10 + 1) + 10;
        fprintf(ballInfor, "%d\n", arr[i]);
    }
    fclose(ballInfor);

    int socket_desc , client_sock , c;
    struct sockaddr_in server , client;

    printf("Enter number player: ");
    scanf("%d", &num_Cl);

    //result = (int*)malloc(sizeof(int)*num_Cl);
     
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
    listen(socket_desc , num_Cl);
     
    //Accept and incoming connection
    printf("Waiting for %d connections...\n", num_Cl);
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
        //pthread_join( thread_id , NULL);
        puts("Handler assigned");
    }

    for (int j = 0; j < num_Cl; j++)
        pthread_join(thread_id[j], NULL);
    

    //puts("done!");
    /* char nameCl[100][10];
    int sum[10], rank[10], v = 0;
    FILE *sumRank = fopen("server_file/result.txt", "r");
    while(!feof(sumRank))
    {
        fscanf(sumRank, "%s", nameCl[v]);
        fscanf(sumRank, "%d", &sum[v]);
        rank[v] = 1;
        v++;
    }
    fclose(sumRank);

    for(int m = 0; m < v; m++)
    {
        for(int n = m; n < v; n++)
        {
            if(sum[m] < sum[n])
                rank[m]++;
        }
    }

    FILE *final = fopen("server_file/rank.txt", "w");

    for(int m = 0; m < v; m++)
    {
        fprintf(final, "Player %s has %d point and rank %d\n", nameCl[m], sum[m], rank[m]);
        printf("Player %s has %d point and rank %d\n", nameCl[m], sum[m], rank[m]);
    }
    fclose(final);
 */
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

    count_Cl++;
    cl_id = count_Cl;
    printf("Client %d connected!\n", count_Cl);
    // wait for all connection

    while(count_Cl < num_Cl)
    {
        strcpy(client_message, "wait");
        send(sock, client_message, sizeof(client_message), 0);
    }
    strcpy(client_message, "start");
    send(sock, client_message, sizeof(client_message), 0);
    
    while(countBall < numberBall)
    {
        read_size = recv(sock , cl_name , 100 , 0);
        sleep(1);
        pthread_mutex_lock(&mutex);
        send(sock, &arr[countBall], sizeof(int), 0);
        printf("Send %d to %s...\n", arr[countBall], cl_name);
		countBall++;
        pthread_mutex_unlock(&mutex);

        if(arr[countBall-1] <= 500)
            length++;
    }
    int x = 0;
    send(sock, &x, sizeof(int), 0);

    int sum = 0;
    int *cl_arr;

    printf("length2 %s = %d\n", cl_name, length);
    cl_arr = (int*)malloc(sizeof(int)*length);
    //read(sock,(void*) cl_arr, sizeof(int)*length);
    for(int v = 0; v < length; v++)
    {
        int x;
        read(sock, (void*)&x, sizeof(int));
        cl_arr[v] = ntohl(x);
        printf("%s: %d\n", cl_name, cl_arr[v]);
    }

    /*
    char filename[100];
    strcpy(filename, "server_file/");
    strcat(filename, cl_name);
    strcat(filename, ".txt");
    FILE *cl_file;
    cl_file = fopen(filename, "w");
    for(int j = 0; j < length; j++)
    {
        if(cl_arr[j] <= 500 && cl_arr[j] >= 10)
        {
            sum += *(cl_arr + j);
            fprintf(cl_file, "%d\n", *(cl_arr + j));
        }
        else
        {
            fprintf(cl_file, "%d\n", 0);
        }
        
    }
    fclose(cl_file);
 */
    /* result[cl_id] = sum;

    while (result[num_Cl - 1] < 0)
    {
        strcpy(client_message, "wait");
        send(sock, client_message, sizeof(client_message), 0);
    }
    strcpy(client_message, "start");
    send(sock, client_message, sizeof(client_message), 0);

    sleep(0.5);
    int rank = 1;
    for (int temp = 0; temp < num_Cl; temp++)
    {
        if(result[cl_id] < result[temp])
            rank++;
    }
    
    
    send(sock, &rank, sizeof(int), 0); */

    FILE *res = fopen("server_file/result.txt", "a");
    fprintf(res, "%s %d\n", cl_name, sum);
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