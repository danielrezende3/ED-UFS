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
    fprintf(pFile_output, "\n[ OK ] ADD %s", name);
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
            fprintf(pFile_output, "\n[ ERROR ] ADD %s", name);
            return 1;
        }
        temp = temp->next;
    } while (temp->next != start);
}

void show(struct Node *start, char name[])
{
    struct Node *temp = start;
    int value = strcmp(temp->name, name);
    while (value != 0)
    {
        temp = temp->next;
        value = strcmp(temp->name, name);
        if (value == 0)
        {
            fprintf(pFile_output, "\n[ OK ] %s < - %s - > %s", temp->prev->name, temp->name, temp->next->name);
            return;
        }
        if (temp == start)
        {
            fprintf(pFile_output, "\n[ ERROR ] ? < - %s - > ?", name);
            return;
        }
    }
    fprintf(pFile_output, "\n[ OK ] %s < - %s - > %s", temp->prev->name, temp->name, temp->next->name);
}

void deleteNode(struct Node **start, char name[])
{
    if (*start == NULL)
        return;
    struct Node *curr = *start, *prev_1 = NULL;
    while (curr->name != name)
    {
        // If node is not present in the list
        int value = strcmp(curr->name, name);
        if (value == 0)
        {
            fprintf(pFile_output, "\n[ OK ] REMOVE %s", name);
            break;
        }
        if (curr->next == *start)
        {
            fprintf(pFile_output, "\n[ ERROR ] REMOVE %s", name);
            return;
        }
        prev_1 = curr;
        curr = curr->next;
    }
    // Check if node is the only node in list
    if (curr->next == *start && prev_1 == NULL)
    {
        (*start) = NULL;
        free(curr);
        return;
    }

    // If list has more than one node,
    // check if it is the first node
    if (curr == *start)
    {
        // Move prev_1 to last node
        prev_1 = (*start)->prev;

        // Move start ahead
        *start = (*start)->next;

        // Adjust the pointers of prev_1 and start node
        prev_1->next = *start;
        (*start)->prev = prev_1;
        free(curr);
    }

    // check if it is the last node
    else if (curr->next == *start)
    {
        // Adjust the pointers of prev_1 and start node
        prev_1->next = *start;
        (*start)->prev = prev_1;
        free(curr);
    }
    else
    {
        // create new pointer, points to next of curr node
        struct Node *temp = curr->next;

        // Adjust the pointers of prev_1 and temp node
        prev_1->next = temp;
        temp->prev = prev_1;
        free(curr);
    }
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
            deleteNode(&head, name);
        }
        fgetc(pFile_input);
    }

    fclose(pFile_input);
    fclose(pFile_output);
    return 0;
}