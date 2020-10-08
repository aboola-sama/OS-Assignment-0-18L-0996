#include<sys/wait.h>
#include<assert.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
void reverse(char*begin,char *end,int flag)
{
    if(flag==1)
    {
        char temp;
        while(begin<end)
        {
            temp = *begin;
            *begin++=*end;
            *end--=temp;
        }
    }
    flag=0;
}
void reverseWords(char* s,int flag)
{
    char * word_begin = s;
    char * temp =s;
    while(*temp){
        temp++;
        if(*temp=='a'||*temp=='e'||*temp=='i'||*temp=='o'||*temp=='u')
        {
            flag = 1;
        }
        if(*temp=='\0'){
            reverse(word_begin,temp-1,flag);
        }
        else if(*temp==' '){
            reverse(word_begin,temp-1,flag);
            word_begin=temp+1;
        }
    }
    flag=0;
    reverse(s,temp-1,flag);
}
int main(int argc, char** argv)
{
    char filename[9]={};
    strcpy(filename,"q3_c.txt");
    filename[3]=argv[1][0];
    char buffer[500];
    int filepointer = open(filename,O_RDONLY);
    int n=read(filepointer, buffer,sizeof(buffer));
    close(filepointer);
    buffer[n] = 0;
    
    int count = strlen(buffer);
    printf("file: ");
    printf("%s\n",buffer);
    
    
    int flag = 0;
    char * temp = buffer;
    reverseWords(buffer,flag);
    printf("%s\n",buffer);
    //counting digits
    return 0;
}










