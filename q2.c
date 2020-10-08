#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
struct students
{
    char name[100];
    char rollNo[100];
    char email[100];
} students;
int main()
{
    int length = 0;
    char input[500];
    int size = 3;
    struct students array[size];
    int sentinel = -5;
    int fd = open("data.txt", O_WRONLY);
    //hardcoded values in struct of array of 3 size
    strcpy(array[0].name, "Abdullah Bashir\n");
    strcpy(array[0].email, "L180996@lhr.nu.edu.pk\n");
    strcpy(array[0].rollNo, "18L-0996\n");
    strcpy(array[1].name, "Ahmed Abdullah\n");
    strcpy(array[1].email, "L180435@lhr.nu.edu.pk\n");
    strcpy(array[1].rollNo, "18L-0435\n");
    strcpy(array[2].name, "Zia Samad\n");
    strcpy(array[2].email, "L182343@lhr.nu.edu.pk\n");
    strcpy(array[2].rollNo, "18L-2343\n");

    for (int i = 0; i < size; i++)
    {
        write(fd, array[i].name, strlen(array[i].name));
        write(fd, array[i].rollNo, strlen(array[i].rollNo));
        write(fd, array[i].email, strlen(array[i].email));
    }
    printf("----------MENU---------\n add student data press 1\n read data from file press 2\n delete student press 3\n -1 to Exit\n");
    int choice = -2;
    while (sentinel != -1)
    {

        scanf("%d", &sentinel);
        if (sentinel == 1)
        {
            printf("press 0 to add to your data, 1 to add to fellow student 1 and 2 to add to fellow student 2\n");
            printf("Choice: ");
            scanf("%d", &choice);
            printf("Name:");
            scanf("%s", array[choice].name);
            strcat(array[choice].name, "\n");
            printf("RollNo:");
            scanf("%s", array[choice].rollNo);
            strcat(array[choice].rollNo, "\n");
            printf("Email:");
            scanf("%s", array[choice].email);
            strcat(array[choice].email, "\n");
            printf("-1 to exit");
        }
        if (sentinel == 2)
        {
            printf("read data on yours 0, fellow student 1 or fellow student 2 \n");
            printf("Choice: ");
            scanf("%d", &choice);
            if (choice == 0 || choice == 1 || choice == 2)
            {
                printf("%s", array[choice].name);
                printf("%s", array[choice].rollNo);
                printf("%s", array[choice].email);
                printf("press -1 to exit\n");
            }
            else
            {
                printf("wrong input terminating");
                return 0;
            }
        }
        if (sentinel == 3)
        {
            printf("press 0 to delete to your data, 1 to delete fellow student 1 and 2 to delete fellow student 2\n");
            printf("Choice: ");
            scanf("%d", &choice);
            strcpy(array[choice].name, "NULL\n");
            strcpy(array[choice].rollNo, "NULL\n");
            strcpy(array[choice].email, "NULL\n");
            printf("Press -1 to exit\n");
        }
    }
    close(fd);
    fclose(fopen("data.txt", "w"));
    fd = open("data.txt", O_WRONLY);
    for (int i = 0; i < size; i++)
    {
        write(fd, array[i].name, strlen(array[i].name));
        write(fd, array[i].rollNo, strlen(array[i].rollNo));
        write(fd, array[i].email, strlen(array[i].email));
    }
    close(fd);
    return 0;
}

