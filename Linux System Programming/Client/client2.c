#include "stdio.h"  
#include "stdlib.h"  
#include "sys/types.h"  
#include "sys/socket.h"  
#include "string.h"  
#include "netinet/in.h"  
#include "netdb.h"
  
#define PORT 4444 
#define BUF_SIZE 2000 
  
int main(int argc, char**argv)
{
    struct sockaddr_in addr, cl_addr;
    int sockfd, ret;
    char buffer[BUF_SIZE];
    struct hostent * server;
    char * serverAddr;
    
    if (argc < 2)
    {
        printf("usage: client < ip address >\n");
        exit(1);
    }
    
    serverAddr = argv[1];
    
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
    addr.sin_port = PORT;
    
    ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
    
    if (ret < 0)
    {
        printf("Error connecting to the server!\n");
        exit(1);
    }
    printf("Connected to the server...\n");
    
    int a[1000], i = 0;

    memset(buffer, 0, BUF_SIZE);
    printf("This is Client2!!\n");
    while (strcmp(buffer, "stop") != 0)
    {
        strcpy(buffer, "client2");
        ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));
        if (ret < 0)
        {
            printf("Error sending data!\n\t-%s", buffer);
        }
        int x;
        ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);
        if (ret < 0)
        {
            printf("Error receiving data!\n");
        }
        else
        {
            if (strcmp(buffer, "stop") == 0)
                break;
            else
            {
                //printf("Server: %s\n", buffer);
                x = atoi(buffer);
                a[i] = x;
                i++;
            }
        }
    }
    //quickSort(a, 0, i);
    FILE *openForWrite;
    openForWrite = fopen("Client/client2.txt", "w");

    for (int k = 0; k < i; k++)
    {
        fprintf(openForWrite, "%d\n", a[k]);
    }
    fclose(openForWrite);

    char* fs_name = "Client/client2.txt";
		//char sdbuf[LENGTH]; 
	printf("[Client] Sending %s to the Server...\n", fs_name);
	FILE *openForSend = fopen(fs_name, "r");
	if (openForSend == NULL)
	{
		printf("ERROR: File %s not found.\n", fs_name);
		exit(1);
	}

	bzero(buffer, BUF_SIZE); 
	int fs_block_sz; 
	while ((fs_block_sz = fread(buffer, sizeof(char), BUF_SIZE, openForSend)) > 0)
	{
		if (send(sockfd, buffer, fs_block_sz, 0) < 0)
		{
		    fprintf(stderr, "ERROR: Failed to send file %s.\n", fs_name);
		    break;
		}
		bzero(buffer, BUF_SIZE);
	}
	printf("Ok File %s from Client was Sent!\n", fs_name);
    fclose(openForSend);

    return 0;    
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int left = low;
    int right = high - 1;
    while(1)
    {
        while(left <= right && arr[left] < pivot)
            left++;
        while(right >= left && arr[right] > pivot)
            right--;
        if (left >= right)
            break;
        int t = arr[left];
        arr[left] = arr[right];
        arr[right] = t;
        //swap(arr[left], arr[right]);
        left++;
        right--;
    }
    int t = arr[left];
    arr[left] = arr[high];
    arr[high] = t;
    return left;
}
 
/* Hàm thực hiện giải thuật quick sort */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi là chỉ số nơi phần tử này đã đứng đúng vị trí
         và là phần tử chia mảng làm 2 mảng con trái & phải */
        int pi = partition(arr, low, high);
 
        // Gọi đệ quy sắp xếp 2 mảng con trái và phải
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}