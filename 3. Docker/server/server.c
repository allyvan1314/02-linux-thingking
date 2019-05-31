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
    // random so phan tu & gia tri phan tu cua mang
    srand(time(NULL));
    int n = 100 + rand() % (1000 - 100 + 1);
    int *a = (int*) malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++)
    {
        a[i] = 1 + rand() % (500);
    }

    // ghi thong tin mang vao file
    FILE *myfile;
    myfile = fopen("server.txt", "w+");

    for (int k = 0; k < n; k++)
    {
        fprintf(myfile, "%d\n", a[k]);
    }

    // chuyen con tro len dau file
    fseek(myfile, 0, SEEK_SET);


    //int PORT;
    int S_socket, S_res, newSocket, len;
    struct sockaddr_in S_addr, C_addr;
    char clientAddr[CLADDR_LEN];
    char buffer[BUF_SIZE];
    pid_t childpid;

    // Tạo socket - họ giao thức, kiểu socket, kiểu giao thức
    S_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (S_socket < 0)
    {
        printf("Error creating socket!\n");
        exit(1);
    }
    printf("Socket created...\n");
    
    // Trả về một con trỏ tới vùng nhớ str
    memset(&S_addr, 0, sizeof(S_addr));
    // Đặt tên cho socket của server 
    S_addr.sin_family = AF_INET;
    //Thiet lap dia chi IP va port
    S_addr.sin_addr.s_addr = INADDR_ANY;
    S_addr.sin_port = PORT;

    // Gán địa chỉ cho socket, các tham số lần lượt là mô tả socket vừa tạo, con trỏ trỏ đến địa chỉ socket, độ lớn địa chỉ
    S_res = bind(S_socket, (struct sockaddr *) &S_addr, sizeof(S_addr));
    
    if (S_res < 0)
    {
        printf("Error binding!\n");
        exit(1);
    }
    printf("Binding done...\n");

    printf("Waiting for a connection...\n");

    // Chỉ định socket lắng nghe kết nối, mô tả socket vừa tạo, backlog là số lượng tối đa các kết nối đang chờ
    listen(S_socket, 9);

    char clientname[255];

    while (1)
    {
        len = sizeof(C_addr);

        /* Chờ/chấp nhận kết nối - mô tả socket vừa tạo, con trỏ tới cấu trúc địa chỉ socket của tiến trình kết nối đến, độ lớn cấu trúc địa chỉ */
        newSocket = accept(S_socket, (struct sockaddr *) &C_addr, &len);
        if (newSocket < 0)
        {
            printf("Error accepting connection!\n");
            exit(1);
        }
        printf("Connection accepted...\n");

        // chuyen doi chuoi - dia chi IP
        inet_ntop(AF_INET, &(C_addr.sin_addr), clientAddr, CLADDR_LEN);

        if ((childpid = fork()) == 0)
        {
            int SoLanLayBi = 0;
            close(S_socket);

            while (1)
            {
                memset(buffer, 0, BUF_SIZE);

                char fr_name[255];
                char temp[255];
                memset(buffer, 0, BUF_SIZE);
                
                while (SoLanLayBi < n)
                {
                    memset(buffer, 0, BUF_SIZE);
                    
                    S_res = recvfrom(newSocket, buffer, BUF_SIZE, 0, (struct sockaddr *) &C_addr, &len);
                    if(S_res < 0)
                    {
                        printf("Error receiving data!\n");
                        exit(1);
                    }
                    //printf("Received data from %s: %s\n", clientAddr, buffer);
                    //printf("Sending ball...\n");
                    strcpy(clientname, buffer);

                    fgets(temp, 255, myfile);

                    S_res = sendto(newSocket, temp, 255, 0, (struct sockaddr *) &C_addr, len);
                    if (S_res < 0)
                    {  
                        printf("Error sending data!\n");
                        exit(1);
                    }
                    //printf("%d: Sent data to %s: %s\n", SoLanLayBi, clientAddr, temp);
                    SoLanLayBi++;
                }

                strcpy(temp, "stop");
                S_res = sendto(newSocket, temp, 255, 0, (struct sockaddr *) &C_addr, len);
                if (S_res < 0)
                {  
                    printf("Error sending data!\n");
                    exit(1);
                }
                printf("Send last message!\n");
                
                // nhan file tu client
                
                strcpy(fr_name, "");
                //strcat(fr_name, "Server/");
                strcat(fr_name, clientname);
                strcat(fr_name, ".txt");
                printf("Filename: %s\n", fr_name);
		        FILE *fr = fopen("sr.txt", "w");
		        if(fr == NULL)
			        printf("File %s Cannot be opened file on server.\n", fr_name);
		        else
		        {
			        bzero(buffer, BUF_SIZE); 
			        int fr_block_sz = 0;
			        while ((fr_block_sz = recv(newSocket, buffer, BUF_SIZE, 0)) > 0) 
			        {
			            int write_sz = fwrite(buffer, sizeof(char), fr_block_sz, fr);
				        if (write_sz < fr_block_sz)
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
        close(newSocket);
    }
}
