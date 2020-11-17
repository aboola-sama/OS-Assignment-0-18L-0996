#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

int potentialCPatients = 0;
int counter = 0;
bool test__results[100];
sem_t coronaMutex, fluMutex;

bool flag = true;

void *coronaManagement(void *param)
{
    int pateintid = (int)param;

    puts("Testing the patients now");

        if (rand() % 2 == 0)
    {
        puts("Patient is infected!!");
        flag = false;
        test__results[counter] = flag;
        counter++;
        sem_post(&fluMutex);
    }
    else
    {
        test__results[counter] = flag;
        counter++;
        puts("Patient not infected!!");
        sem_post(&coronaMutex);
    }

    potentialCPatients++;
    pthread_exit(pateintid);
}

int main(int argc, char *argv[])
{
    int i;
    int noofpatients = atoi(argv[1]); //convert to integer

    sem_init(&coronaMutex, 0, 1);
    sem_init(&fluMutex, 0, 1);

    pthread_t thread_fd[noofpatients];

    for (i = 0; i < noofpatients; i++) //execute this loop for each patient
    {

        if((pthread_create(&thread_fd[i], NULL, (void *)&coronaManagement, (void *)& i)) == 0 ) //i represent patient id
		{
            puts("Thread Failure!!!");
            exit(EXIT_FAILURE);
		}

        printf("For %d\n", i);

		void* return__value;
		pthread_join(thread_fd[i], &return__value);
	
	

		if (test__results[i] == true) 
		{
            int noofnegativetest = 0;

            while (noofnegativetest >= 2)
            {

                if (rand() % 2 == 0) // loop until two tests come negative
                   noofnegativetest++;
            }

            printf("Following %d patient is now recovered:", i); //display patient
            sem_wait(&coronaMutex);
		}

		sem_wait(&fluMutex);
		potentialCPatients--;
    }

    sem_destroy(&coronaMutex);
    sem_destroy(&fluMutex);

    return 0;
}
