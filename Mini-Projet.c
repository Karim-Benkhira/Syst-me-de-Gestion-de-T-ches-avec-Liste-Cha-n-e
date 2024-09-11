#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
char title[MAX][MAX];
char description[MAX][MAX];
char dueDate[MAX][MAX];

void AddTask(char taskTitle[],char taskDescription[],char taskDueDate[],char title[][MAX],char description[][MAX],char dueDate[][MAX],int next[],int *head,int *freeIndex)
{
    if(*freeIndex < MAX)
    {
        strcpy(title[*freeIndex], taskTitle);
        strcpy(description[*freeIndex], taskDescription);
        strcpy(dueDate[*freeIndex], taskDueDate);
        next[*freeIndex] = *head;
        *head = *freeIndex;
        (*freeIndex)++;
    }
    else
        printf("Impossible d'ajouter d'autres tâches, la liste est pleine\n");
}


void deleteTask(char taskTitle[], char title[][MAX], int next[], int *head)
{
    int current = *head;
    int previous = -1;

    while(current != -1)
    {
        if(strcmp(title[current], taskTitle) == 0)
        {
            if(previous == -1)
                *head = next[current];
            else
                next[previous] = next[current];

            printf("La tâche a été supprimée: %s\n", taskTitle);
            return;
        }
        previous = current;
        current = next[current];
    }
    printf("Tâche introuvable: %s\n", taskTitle);
}

void displayTasks(char title[][MAX], char description[][MAX], char dueDate[][MAX], int next[], int head)
{
    int current = head;

    if (current == -1)
    {
        printf("Il n'y a aucune tâche à afficher \n");
        return;
    }
    
    while (current != -1)
    {
        printf("title : %s\n", title[current]);
        printf("description : %s\n", description[current]);
        printf("dueDate : %s\n", dueDate[current]);

        printf("-------------------------\n");

        current = next[current];
    }
}

void searchTask(char taskTitle[], char title[][MAX], char description[][MAX], char dueDate[][MAX], int next[], int head)
{
    int current = head;

    while(current != -1)
    {
        if(strcmp(title[current], taskTitle) == 0)
        {
            printf("Tâche trouvée :\n");
            printf("------------------------\n");
            printf("title : %s\n", title[current]);
            printf("description : %s\n", description[current]);
            printf("dueDate : %s\n", dueDate[current]);
            return;
        }
        current = next[current];
    }

    printf("Tâche introuvable: %s\n", taskTitle);
}

void menu(char title[][MAX], char description[][MAX], char dueDate[][MAX], int next[], int *head, int *freeIndex)
{
    int choice;
    char taskTitle[MAX], taskDescription[MAX], taskDueDate[MAX];

    do
    {
        printf("Ajouter une tâche : 1\n");
        printf("Supprimer une tâche : 2\n");
        printf("Afficher toutes les tâches : 3\n");
        printf("Rechercher une tâche : 4 \n");
        printf("Sortie : 5 \n");
        printf("Entrez votre choix : \n");

        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            printf("Saisissez le titre de la tâche :");
            fgets(taskTitle, MAX, stdin);
            taskTitle[strcspn(taskTitle, "\n")] = 0;
            printf("Entrez la description de la tâche :");
            fgets(taskDescription, MAX, stdin);
            taskDescription[strcspn(taskDescription, "\n")] = 0;
            printf("Entrez la date d'échéance (AAAA-MM-JJ) ");
            fgets(taskDueDate, MAX, stdin);
            taskDueDate[strcspn(taskDueDate, "\n")] = 0;
            AddTask(taskTitle, taskDescription, taskDueDate, title, description, dueDate, next, head, freeIndex);
            break;
        case 2:
            printf("Saisissez le titre de la tâche que vous souhaitez supprimer :");
            fgets(taskTitle, MAX, stdin);
            taskTitle[strcspn(taskTitle, "\n")] = 0;
            deleteTask(taskTitle, title, next, head);
            break;
        case 3:
            displayTasks(title, description, dueDate, next, *head);
            break;
        case 4:
            printf("Saisissez le titre de la tâche que vous souhaitez rechercher : ");
            fgets(taskTitle, MAX, stdin);
            taskTitle[strcspn(taskTitle, "\n")] = 0;
            searchTask(taskTitle, title, description, dueDate, next, *head);
            break;
        case 5:
            printf("Quittez le programme.\n");
            break;
        default:
            printf("Option invalide. Essayer à nouveau \n");
        }
    } while (choice != 5);
}

int main() {
    int next[MAX];
    int head = -1, freeIndex = 0;

    menu(title, description, dueDate, next, &head, &freeIndex);

    return 0;
}
