#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node
{
    // Vetor de chaves
    int *C;
    // Vetor de filhos
    struct Node **P;
    // quantidade utilizada
    int n;
};

int main(int argc, char const *argv[])
{
    int ordem_da_arvore;
    int qnt_de_arquivos;
    int num_de_operacoes;
    int tamanho;
    char nome[31];
    char hash[33];
    // 6(comando)_30(nome)_32(hash)_ = 71
    char linha[71];
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
        fscanf(pInput, "%[^\n]", linha);
        teste = strstr(linha, "INSERT");
        if (teste)
        {
            // insert();
        }
        teste = strstr(linha, "SELECT");
        if (teste)
        {
            // select();
        }
        fgetc(pInput);
    }

    return 0;
}