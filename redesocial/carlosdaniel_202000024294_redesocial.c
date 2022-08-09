#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char data[51];
    struct Node *prev;
    struct Node *next;
} Node;

struct Node *head;
FILE *file_input;
FILE *file_output;
char buffer_in[256], buffer_out[256];

void insertion(char name[])
{
    struct Node *ptr, *temp;
    ptr = (struct Node *)malloc(sizeof(struct Node));
    if (ptr == NULL)
    {
        printf("\nList_Overflow");
    }
    else
    {
        strcpy(ptr->data, name);
        if (head == NULL)
        {
            head = ptr;
            ptr->next = head;
            ptr->prev = head;
        }
        else
        {
            temp = head;
            while (temp->next != head)
            {
                temp = temp->next;
            }
            temp->next = ptr;
            ptr->prev = temp;
            head->prev = ptr;
            ptr->next = head;
            head = ptr;
        }
        fprintf(file_output, "[ OK ] ADD %s\n", name);
    }
}

void srch(char name[])
{
    struct Node *ptr;
    int i = 0, flag = 1;
    ptr = head;
    if (ptr == NULL)
    {
        printf("\nBlank_all_elements.\n");
    }
    else
    {
        if (head->data == name)
        {
            printf("found_location_item %d", i + 1);
            flag = 0;
        }
        else
        {
            while (ptr->next != head)
                if (ptr->data == name)
                {
                    printf("element_at_location %d ", i + 1);
                    flag = 0;
                    break;
                }
                else
                {
                    flag = 1;
                }
            i++;
            ptr = ptr->next;
        }
    }
    if (flag != 0)
    {
        printf("Element_Not_found\n");
    }
}
int main()
{
    // Declaração de variável
    char command[6], name[51];
    char add[] = "ADD";
    char show[] = "SHOW";

    // Abertura arquivo de entrada
    file_input = fopen("entrada.txt", "r");
    if (file_input == NULL)
    {
        return 1;
    }
    // Abertura arquivo de saida
    file_output = fopen("saida.txt", "w");
    if (file_output == NULL)
    {
        return 1;
    }

    // Coletar comandos e nomes do arquivo de saida
    while (fgets(buffer_in, 256, file_input))
    {
        sscanf(buffer_in, "%s %[^\n]%*c", command, name);
        if (strstr(command, add) != NULL)
        {
            insertion(name);
        }
        if (strstr(command, show) != NULL)
        {
            srch(name);
        }
    }
    // Checagem do arquivo de saida
    size_t bytes_wrote = fwrite(buffer_out, sizeof(char), strlen(buffer_out), file_output);
    if (bytes_wrote != strlen(buffer_out))
    {
        return 1;
    }

    // Fechar arquivos
    fclose(file_input);
    fclose(file_output);
}