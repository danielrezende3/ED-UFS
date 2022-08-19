#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *input;
    FILE *output;
    int qnt_paginas;
    int qnt_documentos;
    int qnt_impressoras;
    char nome_documento[51];
    char nome_impressora[51];
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
        fgetc(input);
    }

    return 0;
}