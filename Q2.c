#include <stdio.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

char buffer_1[50];
int b1 = 0; //counter for buffer_1
char buffer_2[100];

sem_t pro_A;
sem_t pro_B;
sem_t pro_C;
sem_t pro_D;
sem_t mutex;

void *process_A(void *param)
{

    sem_wait(&pro_A);
    sem_wait(&mutex);

    FILE *fin;
    char temp[50];

    fin = fopen("file1.txt", "r");

   

    while (!feof(fin))
    {
        fgets(temp, 50, fin);
        buffer_1[b1++] = temp[0];
    }

    close(fin);

    sem_post(&pro_C);
    sem_post(&mutex);

    pthread_exit(NULL);
}

void *process_B(void *param)
{
    sem_wait(&pro_B);
    sem_wait(&mutex);

    FILE *fin;
    char temp[50];
    

    fin = fopen("file2.txt", "r");

    while (!feof(fin))
    {
        fgets(temp, 50, fin);
        buffer_1[b1++] = temp[0];
    }

    close(fin);

    sem_post(&pro_C);
    sem_post(&mutex);

    pthread_exit(NULL);
}

void *process_C(void *param)
{
    sem_wait(&pro_C);

    for (size_t i = 0; i < b1; i++)
    {
        buffer_2[i] = buffer_1[i];
    }

 

    
    sem_post(&pro_D);

    pthread_exit(NULL);

}

void *process_D(void *param)
{

    sem_wait(&pro_D);

   

    printf(buffer_2);

    pthread_exit(NULL);
}

int main()
{

    sem_init(&pro_A, 0, 1);
    sem_init(&pro_B, 0, 1);
    sem_init(&pro_C, 0, -1);
    sem_init(&pro_D, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t fd_1;
    pthread_t fd_2;
    pthread_t fd_3;
    pthread_t fd_4;
    if ((pthread_create(&fd_1, NULL, process_A, NULL) < 0))
    {
        puts("Thread Failure!!!");
        return 1;
    }

    pthread_join((pthread_t) * &fd_1, NULL); // exiting thread

    if ((pthread_create(&fd_2, NULL, process_B, NULL) < 0))
    {
        puts("Thread Failure!!!");
        return 1;
    }

    pthread_join((pthread_t) * &fd_2, NULL); // exiting thread

    if ((pthread_create(&fd_3, NULL, process_C, NULL) < 0))
    {
        puts("Thread Failure!!!");
        return 1;
    }

    pthread_join((pthread_t) * &fd_3, NULL); // exiting thread

    if ((pthread_create(&fd_4, NULL, process_D, NULL) < 0))
    {
        puts("Thread Failure!!!");
        return 1;
    }

    pthread_join((pthread_t) * &fd_4, NULL); // exiting thread

    sem_destroy(&pro_A);
    sem_destroy(&pro_B);
    sem_destroy(&pro_C);
    sem_destroy(&pro_D);
    sem_destroy(&mutex);

    return 0;
}