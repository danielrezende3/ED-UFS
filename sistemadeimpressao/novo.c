#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

struct Impressora
{
    int isimprimindo;
    char nome_impressora[51];
    int autal_pags;
    struct Impressora *prox;
};
typedef struct Impressora Impressora;

struct Documento
{
    char nome_documento[51];
    int num_paginas;
    struct Documento *prox;
};
typedef struct Documento Documento;

struct Pilha
{
    Documento *topo;
    int tamanho;
};
typedef struct Pilha Pilha;

struct Impressora *addToEmpty(struct Impressora *last, char nome_impressora[])
{
    // This function is only for empty list
    if (last != NULL)
        return last;
    // Creating a node dynamically.
    struct Impressora *temp = (struct Impressora *)malloc(sizeof(struct Impressora));
    // Assigning the data.
    memcpy(temp->nome_impressora, nome_impressora, 51);
    temp->isimprimindo = 0;
    last = temp;
    // Creating the link.
    last->prox = last;
    return last;
}

struct Impressora *addBegin(struct Impressora *last, char nome_impressora[])
{
    if (last == NULL)
        return addToEmpty(last, nome_impressora);

    // Creating a node dynamically.
    struct Impressora *temp = (struct Impressora *)malloc(sizeof(struct Impressora));

    // Assigning the data.
    memcpy(temp->nome_impressora, nome_impressora, 51);
    temp->isimprimindo = 0;
    // Adjusting the links.
    temp->prox = last->prox;
    last->prox = temp;
    return last;
}
void traverse(struct Impressora *last)
{
    struct Impressora *p;
    // If list is empty, return.
    if (last == NULL)
    {
        printf("List is empty.");
        return;
    }
    // Pointing to first Node of the list.
    p = last->prox;
    // Traversing the list.
    do
    {
        printf("%s ", p->nome_impressora);
        p = p->prox;
    } while (p != last->prox);
}
void IniciaPilha(Pilha *pilha)
{
    pilha->topo = NULL;
    pilha->tamanho = 0;
}

int Vazia(Pilha *pilha)
{
    return (pilha->topo == NULL);
}

void Empilha(int x, char nome[], Pilha *pilha)
{
    Documento *aux;
    // Creating a node dynamically.
    aux = (Documento *)malloc(sizeof(Documento));
    memcpy(aux->nome_documento, nome, 51);
    aux->num_paginas = x;
    aux->prox = pilha->topo;
    pilha->topo = aux;
    pilha->tamanho++;
}

void Desempilha(Pilha *pilha)
{
    Documento *q;
    if (Vazia(pilha))
    {
        return;
    }
    q = pilha->topo;
    pilha->topo = q->prox;
    free(q);
    pilha->tamanho--;
}

int main(int argc, char *argv[])
{
    FILE *input;
    FILE *output;
    Pilha *pilha;
    int qnt_paginas;
    int total_paginas;
    int qnt_documentos;
    int qnt_impressoras;
    char nome_documento[51];
    char nome_impressora[51];
    pilha = (Pilha *)malloc(sizeof(Pilha));
    Impressora *last = NULL;
    IniciaPilha(pilha);
    // TODO: trocar nome do arquivo por argv[1]
    input = fopen("casoteste.input", "r");
    if (input == NULL)
    {
        return 1;
    }
    // TODO: trocar nome do arquivo por argv[2]
    output = fopen("meu.output", "w");
    if (output == NULL)
    {
        return 1;
    }
    // Coleta de dados
    fscanf(input, "%i", &qnt_impressoras);
    fgetc(input);
    for (int i = 0; i < qnt_impressoras; i++)
    {
        fscanf(input, "%s", nome_impressora);
        last = addBegin(last, nome_impressora);
        fgetc(input);
    }
    traverse(last);
    fscanf(input, "%i", &qnt_documentos);
    fgetc(input);
    for (int i = 0; i < qnt_documentos; i++)
    {
        fscanf(input, "%s %i", nome_documento, &qnt_paginas);
        Empilha(qnt_paginas, nome_documento, pilha);
        total_paginas += qnt_paginas;
        fgetc(input);
    }
    // Processamento de dados
    return 0;
}