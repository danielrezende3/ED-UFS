#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char nome_documento[51];
    int num_paginas;
    struct Node *prox;
};
typedef struct Node TipoNode;

struct Pilha
{
    TipoNode *topo;
    int tamanho;
};
typedef struct Pilha TipoPilha;

void IniciaPilha(TipoPilha *pilha)
{
    pilha->topo = NULL;
    pilha->tamanho = 0;
}

int Vazia(TipoPilha *pilha)
{
    return (pilha->topo == NULL);
}

void Empilha(int x, char nome[], TipoPilha *pilha)
{
    TipoNode *aux;
    aux = (TipoNode *)malloc(sizeof(TipoNode));
    memcpy(aux->nome_documento, nome, 51);
    aux->num_paginas = x;
    aux->prox = pilha->topo;
    pilha->topo = aux;
    pilha->tamanho++;
}

int Desempilha(TipoPilha *pilha)
{
    TipoNode *q;
    int v;
    if (Vazia(pilha))
    {
        printf("Lista vazia\n");
        return 0;
    }
    q = pilha->topo;
    pilha->topo = q->prox;
    v = q->num_paginas;
    free(q);
    pilha->tamanho--;
    return v;
}

int main(int argc, char *argv[])
{
    FILE *input;
    FILE *output;
    TipoPilha *pilha;
    int qnt_paginas;
    int total_paginas;
    int qnt_documentos;
    int qnt_impressoras;
    char nome_documento[51];
    char nome_impressora[51];
    pilha = (TipoPilha *)malloc(sizeof(TipoPilha));
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
    IniciaPilha(pilha);
    fscanf(input, "%i", &qnt_impressoras);
    fgetc(input);
    for (int i = 0; i < qnt_impressoras; i++)
    {
        fscanf(input, "%s", nome_impressora);
        fgetc(input);
    }
    fscanf(input, "%i", &qnt_documentos);
    fgetc(input);
    for (int i = 0; i < qnt_documentos; i++)
    {
        fscanf(input, "%s %i", nome_documento, &qnt_paginas);
        Empilha(qnt_paginas, nome_documento, pilha);
        total_paginas += qnt_paginas;
        fgetc(input);
    }
    printf("%i", pilha->tamanho);

    return 0;
}