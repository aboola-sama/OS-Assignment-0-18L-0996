#include<sys/wait.h>
#include<assert.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main(int argc, char** argv)
{
    char filename[9]={};
    strcpy(filename,"q1_c.txt");
    filename[3]=argv[0][7];
    char buffer[500];
    FILE * filepointer;
    filepointer = fopen(filename,"r"); //r denotes as reading from a file
    fread(buffer,sizeof(buffer),1,filepointer);
    fclose(filepointer);
    
    int count = strlen(buffer); 
    printf("total string size: ");
    printf("%d\n",count);
    //counting digits
    int digitCount =0;
    for(int i=0;i<count;i++)
    {
        if(buffer[i]>=48 && buffer[i]<=57)//30 to 39
        {
            digitCount++;
        }
    }
    printf("digits in string: ");
    printf("%d\n",digitCount);
    return 0;
}










