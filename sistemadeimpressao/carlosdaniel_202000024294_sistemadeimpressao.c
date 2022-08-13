#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Documento
{
    char nome[51];
    int paginas;
} Documento;

typedef struct Impressora
{
    char nome[51];
} Impressora;

typedef struct Stack
{
    int top;
    unsigned capacity;
    int *array;
} Stack;

struct Stack *createStack(unsigned capacity)
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isFull(struct Stack *stack)
{
    return stack->top == stack->capacity - 1;
}
void push(struct Stack *stack, int item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
    printf("%d pushed to stack\n", item);
}

int main(int argc, char *argv[])
{
    FILE *pFile_input;
    FILE *pFile_output;
    char line[256];
    char nome_impressora[51];
    int num_impressoras;
    int num_documentos;
    pFile_input = fopen("sistemadeimpressao.input", "r");
    if (pFile_input == NULL)
    {
        return 1;
    }
    pFile_output = fopen("teste.output", "w");
    if (pFile_output == NULL)
    {
        return 1;
    }

    fscanf(pFile_input, "%i", &num_impressoras);
    fgetc(pFile_input);
    Impressora impressoras[num_impressoras];
    for (int i = 0; i < num_impressoras; i++)
    {
        fscanf(pFile_input, "%s", &nome_impressora);
        fgetc(pFile_input);
        strcpy(impressoras[i].nome, nome_impressora);
    }
    fscanf(pFile_input, "%i", &num_documentos);
    fgetc(pFile_input);
    Stack *stack = createStack(num_documentos);
    // Documento documentos[num_documentos];
    // for (int i = 0; i < num_documentos; i++)
    // {
    //     fscanf(pFile_input, "%s %i", &documentos[i].nome, &documentos[i].paginas);
    //     fgetc(pFile_input);
    // }

    return 0;
}