#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *pFile_output;
FILE *pFile_input;

typedef struct Node
{
    char name[51];
    struct Node *next;
    struct Node *prev;
} Node;

void add(struct Node **head, char name[])
{
    // If the list is empty
    if (*head == NULL)
    {
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        strcpy(new_node->name, name);
        new_node->next = new_node->prev = new_node;
        *head = new_node;
        fprintf(pFile_output, "[ OK ] ADD %s", name);
        return;
    }

    // If list is not empty
    /* Find last node */
    Node *last = (*head)->prev;
    // Create Node dynamically
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    strcpy(new_node->name, name);
    // Start is going to be next of new_node
    new_node->next = *head;
    // Make new node previous of start
    (*head)->prev = new_node;
    // Make last previous of new node
    new_node->prev = last;
    // Make new node next of old last
    last->next = new_node;
    // Print
    fprintf(pFile_output, "[ OK ] ADD %s\n", name);
}

int test(struct Node *start, char name[])
{
    struct Node *temp = start;
    if (temp->name == NULL)
    {
        return 0;
    }

    do
    {
        int valor = strcmp(name, temp->name);
        if (valor == 0)
        {
            fprintf(pFile_output, "\n[ ERROR ] ADD %s\n", name);
            return 1;
        }
        temp = temp->next;
    } while (temp->next != start);
}

void show(struct Node *start, char name[])
{
    struct Node *temp = start;
    int value = strcmp(temp->name, name);
    while (value != 0 || temp->next != start)
    {
        temp = temp->next;
        value = strcmp(temp->name, name);
        if (value == 0)
        {
            fprintf(pFile_output, "[ OK ] %s <- %s -> %s", temp->prev->name, temp->name, temp->next->name);
            return;
        }
        if (temp->next == start)
        {
            return;
        }
    }
    fprintf(pFile_output, "[ OK ] %s <- %s -> %s", temp->prev->name, temp->name, temp->next->name);
}

int main(int argc, char *argv[])
{
    struct Node *head = NULL;
    int remove_string = 0;
    int show_string = 0;
    int add_string = 0;
    int cmp;
    char command[2];
    char line[256];
    char name[51];

    pFile_input = fopen("redesocial.input", "r");
    if (pFile_input == NULL)
    {
        return 1;
    }
    pFile_output = fopen("teste.output", "w");
    if (pFile_output == NULL)
    {
        return 1;
    }

    while ((fscanf(pFile_input, "%[^\n]", line)) != EOF)
    {
        strncpy(command, line, 1);
        add_string = strcmp(command, "A");
        show_string = strcmp(command, "S");
        remove_string = strcmp(command, "R");

        strncpy(name, line, 51);
        if (add_string == 0)
        {
            strncpy(name, line + 4, 51);
            cmp = test(head, name);

            if (cmp == 1)
            {
                fgetc(pFile_input);
                continue;
            }
            add(&head, name);
        }
        else if (show_string == 0)
        {
            strncpy(name, line + 5, 51);
            show(head, name);
        }
        else if (remove_string == 0)
        {
            strncpy(name, line + 7, 51);
        }
        fgetc(pFile_input);
    }

    fclose(pFile_input);
    fclose(pFile_output);
    return 0;
}