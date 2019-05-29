#include "stdio.h"  
#include "stdlib.h"  
#include "sys/types.h"  
#include "sys/socket.h"  
#include "string.h"  
#include "netinet/in.h"  
#include "netdb.h"
  
#define PORT 4444 
#define BUF_SIZE 2000
#define swap(type, a, b) {type temp = a; a = b; b = temp; }
  
int main(int argc, char** argv)
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
    addr.sin_port = PORT;
    
    // Thiết lập kết nối với máy chủ TCP
    ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
    if (ret < 0)
    {
        printf("Error connecting to the server!\n");
        exit(1);
    }
    printf("Connected to the server...\n");
    
    // tao mang luu thong tin ball nhan duoc
    int a[1000], i = 0;

    memset(buffer, 0, BUF_SIZE);
    printf("This is Client1!!\n");
    
    while (strcmp(buffer, "stop") != 0)
    {
        strcpy(buffer, "client1");
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
            {
                printf("Receiver last message!!\n");
                break;
            }
            else
            {
                //printf("Server: %s\n", buffer);
                x = atoi(buffer);
                a[i] = x;
                i++;
            }
        }
    }

    // sort mang sau do ghi vao file
    quickSort(a, 0, i);
    FILE *openForWrite;
    openForWrite = fopen("client1.txt", "w");

    for (int k = 0; k < i; k++)
    {
        fprintf(openForWrite, "%d\n", a[k]);
    }
    fclose(openForWrite);

    // mo file de gui cho server
    char* fs_name = "client1.txt";
		//char sdbuf[LENGTH]; 
	printf("[Client] Sending %s to the Server...\n", fs_name);
	FILE *openForSend = fopen(fs_name, "r");
	if (openForSend == NULL)
	{
		printf("ERROR: File %s not found.\n", fs_name);
		exit(1);
	}

    // copy zeroes into string 
	bzero(buffer, BUF_SIZE); 
	int fs_block_sz;

    // Doc du lieu vao buffer
	while ((fs_block_sz = fread(buffer, sizeof(char), BUF_SIZE, openForSend)) > 0)
	{
        // gui buffer
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
void quickSort(int *a, int l, int r)
{
    srand(time(NULL));  //khoi tao tham so ham rand()
    int key = a[l + rand() % (r-l+1)];  //lay khoa la gia tri ngau nhien tu a[l] -> a[r]
    //int key = a[(l+r)/2];
    int i = l, j = r;
 
    while(i <= j)
    {
        while(a[i] < key) i++;       // tim phan tu ben trai ma >=key
        while(a[j] > key) j--;       // tim phan tu ben trai ma <=key
        if(i <= j)
        {
            if (i < j)
                swap(int, a[i], a[j]);  // doi cho 2 phan tu kieu int a[i], a[j].
            i++;
            j--;
        }
    }
    //bay gio ta co 1 mang : a[l]....a[j]..a[i]...a[r]
    if (l < j) quickSort(a, l, j);   // lam lai voi mang a[l]....a[j]
    if (i < r) quickSort(a, i, r); // lam lai voi mang a[i]....a[r]
}