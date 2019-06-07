#include <stdio.h>

int main()
{
    FILE *test;
    test = fopen("test.txt", "r");
    char name[100][10];
    int sum[10];
    int i = 0;
    while(!feof(test))
    {
        fscanf(test, "%s", name[i]);
        fscanf(test, "%d", &sum[i]);
        printf("%s: %d\n", name[i], sum[i]);
        i++;
    }
    fclose(test);

    int *rank = (int*)malloc(sizeof(int)*i);
    for(int j = 0; j < i; j++)
    {
        rank[j] = 1;
    }

    for(int m = 0; m < i; m++)
    {
        for(int n = 0; n < i; n++)
        {
            if(sum[m] < sum[n])
                rank[m]++;
        }
    }

    for(int k = 0; k < i; k++)
    {
        printf("%s: %d\n", name[k], rank[k]);
    }

    return 0;
}