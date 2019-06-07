#include "stdio.h"  
#include "stdlib.h"  
#include "sys/types.h"  
#include "sys/socket.h"  
#include "string.h"  
#include "netinet/in.h"  
#include "netdb.h"
  
#define PORT 8888
#define BUF_SIZE 2000

  
int main(int argc, char** argv)
{
    struct sockaddr_in addr, cl_addr;
    int sockfd, ret;
    int buffer;
    struct hostent * server;
    char * serverAddr;
    
    if (argc < 2)
    {
        printf("usage: client < ip address >\n");
        exit(1);
    }

    char name[100];
    printf("Enter your name: ");
    scanf("%s", &name);
    
    // nhan dia chi IP
    serverAddr = argv[1];
    
    // Tao socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("Error creating socket!\n");
        exit(1);
    }
    printf("Socket created...\n");
    
    memset(&addr, 0, sizeof(addr));
    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(serverAddr);
    addr.sin_port = htons(PORT);
    
    // Thiết lập kết nối với máy chủ TCP
    ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
    if (ret < 0)
    {
        printf("Error connecting to the server!\n");
        exit(1);
    }
    printf("Connected to the server...\n");
    printf("This is %s!!\n", name);
    
    // Tao mang luu thong tin ball
    int ballInfor[1000];
    int countBall = 0;
    char ser_mess[2000];

    while (strcmp(ser_mess, "start") != 0)
    {
        recv(sockfd, ser_mess, 2000, 0);
    }

    while (1)
    {
        ret = write(sockfd, name, sizeof(name));
        if (ret < 0)
        {
            printf("Error sending data!\n");
        }
        //memset(buffer, 0, BUF_SIZE);
        ret = recv(sockfd, (void*) &buffer, sizeof(int), 0);
        if (ret < 0)
        {
            printf("Error receiving data!\n");
        }
        else
        {
            if (buffer == 0)
                break;
            else
            {
                //puts(buffer);
                printf("Recv: %d\n", buffer);
                ballInfor[countBall] = buffer;
                countBall++;
            }
        }
    }

    insertionSort(ballInfor, countBall);

    send(sockfd, &countBall, sizeof(int), 0);
    send(sockfd, ballInfor, sizeof(int)*countBall, 0);

    char filename[100];
    strcpy(filename, "client_file/");
    strcat(filename, name);
    strcat(filename, ".txt");
    FILE *cl_file;
    cl_file = fopen(filename, "w");
    for(int i = 0; i < countBall; i++)
    {
        fprintf(cl_file, "%d\n", ballInfor[i]);
    }
    fclose(cl_file);

    /* while (strcmp(ser_mess, "start") != 0)
    {
        recv(sockfd, ser_mess, 2000, 0);
    }

    int rank;
    recv(sockfd, (void*) &rank, sizeof(int), 0);

    printf("Player %s rank %d\n", name, rank); */

    //printf("Recv: %d\n", buffer);
    close(sockfd);

    return 0;    
}

void insertionSort(int *arr, int length)
{
	int i, key, j;
	for (i = 1; i < length; i++)
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}