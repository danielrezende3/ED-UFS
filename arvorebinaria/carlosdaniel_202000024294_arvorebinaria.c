#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

struct Node
{
    // 50 (até) caracteres + 1 ponto + 2 de leitura escrita + 1 espaço + 7 (até) bytes + 1 \0
    char *word;
    struct Node *left;
    struct Node *right;
};

struct Node *Insert(struct Node **root, char data)
{
    if (root == NULL)
    {
        BstNode *newNode = (BstNode *)malloc(sizeof(BstNode));
    }
    
}

int main(int argc, char *argv[])
{
    // Declaração de variáveis
    int total;
    char data[62];
    struct Node *root = NULL;
    // Abertura de arquivos
    FILE *pInput;
    FILE *pOutput;
    // TODO: Trocar "teste.input" por "argv[1]"
    pInput = fopen("casoteste.input", "r");
    if (pInput == NULL)
    {
        return 1;
    }
    // TODO: Trocar "meu.output" por "argv[2]"
    pOutput = fopen("meu.output", "w");
    if (pOutput == NULL)
    {
        return 1;
    }
    fscanf(pInput, "%i", &total);
    fgetc(pInput);
    for (int i = 0; i < total; i++)
    {
        fscanf(pInput, "%[^\n]", data);
        fgetc(pInput);
    }

    return 0;
}