#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NOME_EXTENSAO 31 // nome+extensão (30) + nulo (1)
#define HASH 33          // 00000000000000000000000000000004 (32) + nulo (1)
#define LINHA 71         // 6(comando)_30(nome)_32(hash)

char nome[NOME_EXTENSAO];
char hash[HASH];
char linha[LINHA];
char comando[LINHA];
struct Node
{
    // Vetor de chaves
    int *C;
    // Vetor de filhos
    struct Node **P;
    // quantidade utilizada
    int ordem_da_arvore;
};
int main(int argc, char const *argv[])
{
    int ordem_da_arvore;
    int qnt_de_arquivos;
    int num_de_operacoes;
    int tamanho;
    FILE *pInput;
    FILE *pOutput;
    // TODO: Trocar "teste.input" por argv[1]
    pInput = fopen("slide.input", "r");
    if (pInput == NULL)
    {
        return 1;
    }
    // TODO: Trocar "meu.output" por argv[2]
    pOutput = fopen("meu.output", "w");
    if (pOutput == NULL)
    {
        return 1;
    }

    // Coleta de ordem da arvore, quantidade de arquivo
    fscanf(pInput, "%i", &ordem_da_arvore);
    fgetc(pInput);
    fscanf(pInput, "%i", &qnt_de_arquivos);
    fgetc(pInput);

    // coleta das strings
    for (int i = 0; i < qnt_de_arquivos; i++)
    {
        fscanf(pInput, "%s %i %s", nome, &tamanho, hash);
        // insert();
        fgetc(pInput);
    }
    fscanf(pInput, "%i", &num_de_operacoes);
    fgetc(pInput);
    for (int i = 0; i < num_de_operacoes; i++)
    {
        char *teste;
        fscanf(pInput, "%s", comando);
        teste = strstr(comando, "INSERT");
        if (teste)
        {
            fscanf(pInput, "%s %i %s", nome, &tamanho, hash);
            // insert();
        }
        teste = strstr(comando, "SELECT");
        if (teste)
        {
            fscanf(pInput,"%s", hash);
            // select();
        }
        fgetc(pInput);
    }

    return 0;
}