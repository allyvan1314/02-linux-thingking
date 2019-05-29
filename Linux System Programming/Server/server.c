#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "string.h"
#include "netinet/in.h"
#include "time.h"

#define PORT 4444
#define BUF_SIZE 2000
#define CLADDR_LEN 100

void main()
{
    struct sockaddr_in addr, cl_addr;
    int sockfd, len, ret, newsockfd;
    char buffer[BUF_SIZE];
    pid_t childpid;
    char clientAddr[CLADDR_LEN];

    // tạo mảng ngẫu nhiên có số phần tử từ 100 - 1000
    srand(time(NULL));
    int n = myRand(100, 1000);
    int *a = (int*) malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++)
    {
        a[i] = 1 + rand() % (500);
    }

    FILE *myfile;
    myfile = fopen("Server/server.txt", "w+");

    for (int k = 0; k < n; k++)
    {
        fprintf(myfile, "%d\n", a[k]);
    }

    fseek(myfile, 0, SEEK_SET);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("Error creating socket!\n");
        exit(1);
    }
    printf("Socket created...\n");
    
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = PORT;
    
    ret = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
    
    if (ret < 0)
    {
        printf("Error binding!\n");
        exit(1);
    }
    printf("Binding done...\n");
    
    printf("Waiting for a connection...\n");
    listen(sockfd, 5);

    char clientname[255];

    while(1)
    {   //lặp vô tận 
        len = sizeof(cl_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cl_addr, &len);
        if (newsockfd < 0)
        {
            printf("Error accepting connection!\n");
            exit(1);
        }
        printf("Connection accepted...\n");
        
        inet_ntop(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);
        
        if ((childpid = fork()) == 0)
        { //Tạo tiến trình con
        
            close(sockfd);
            //stop listening for new connections by the main process.
            //the child will continue to listen. 
            //the main process now handles the connected client.
            
            int SoLanLayBi = 0;

            while(1)
            {
                char fr_name[255];
                char temp[255];
                memset(buffer, 0, BUF_SIZE);
                
                while (SoLanLayBi < n)
                {
                    memset(buffer, 0, BUF_SIZE);
                    ret = recvfrom(newsockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &cl_addr, &len);
                    if(ret < 0)
                    {
                        printf("Error receiving data!\n");
                        exit(1);
                    }
                    //printf("Received data from %s: %s\n", clientAddr, buffer);
                    //printf("Sending ball...\n");
                    strcpy(clientname, buffer);

                    fgets(temp, 255, myfile);

                    ret = sendto(newsockfd, temp, 255, 0, (struct sockaddr *) &cl_addr, len);
                    if (ret < 0)
                    {  
                        printf("Error sending data!\n");
                        exit(1);
                    }
                    //printf("%d: Sent data to %s: %s\n", SoLanLayBi, clientAddr, temp);
                    SoLanLayBi++;
                }

                strcpy(temp, "stop");
                ret = sendto(newsockfd, temp, 255, 0, (struct sockaddr *) &cl_addr, len);
                if (ret < 0)
                {  
                    printf("Error sending data!\n");
                    exit(1);
                }
                printf("Send last message!\n");
                
                // nhan file tu client
                
                strcpy(fr_name, "");
                strcat(fr_name, "Server/");
                strcat(fr_name, clientname);
                strcat(fr_name, ".txt");
                //strcpy(fr_name, strcat(fr_name, ".txt"));
                printf("Filename: %s\n", fr_name);
		        FILE *fr = fopen(fr_name, "w");
		        if(fr == NULL)
			        printf("File %s Cannot be opened file on server.\n", fr_name);
		        else
		        {
			        bzero(buffer, BUF_SIZE); 
			        int fr_block_sz = 0;
			        while ((fr_block_sz = recv(newsockfd, buffer, BUF_SIZE, 0)) > 0) 
			        {
			            int write_sz = fwrite(buffer, sizeof(char), fr_block_sz, fr);
				        if(write_sz < fr_block_sz)
			            {
			                error("File write failed on server.\n");
			            }
				        bzero(buffer, BUF_SIZE);
				        if (fr_block_sz == 0 || fr_block_sz != 512) 
				        {
					        break;
				        }
			        }
			        if (fr_block_sz < 0)
		            {
	                    printf("recv() failed due to errno\n");
					    exit(1);
        	        }
			        printf("Ok received from client!\n");
			        fclose(fr);
                    //break;
		        }
                
            }
        }
        fclose(myfile);
        close(newsockfd);
    }
}

// Hàm sinh số ngẫu nhiên trong đoạn [min, max]
int myRand(int minN, int maxN)
{
    srand(time(NULL));
    return minN + rand() % (maxN + 1 - minN);
}

void myShow(int *a)
{
    for (int i = 0; i < sizeof(a); i++)
    {
        printf("%d\n", a[i]);
    }
}

void Del (int *arr, int vitri, int arrSize)
{
    for (int i = vitri; i < arrSize; i++)
    {
        arr[i] = arr[i+1];
    }
    arr[arrSize] = NULL;
}

void MyIntToChar(int a, char *ret)
{
    int x = 0, n = 0;
    while (a > 0)
    {
        x = x*10 + a%10;
        a = a/10;
        n++;
    }
    for (int i = 0; i < n; i++)
    {
        ret[i] = (x%10 + 48);
        x = x/10;
    }
}