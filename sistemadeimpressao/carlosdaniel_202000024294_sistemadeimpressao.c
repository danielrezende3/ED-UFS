#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

// Declarao de structs
typedef struct Documento
{
    char nome_documento[51];
    int total_paginas;
} Documento;

typedef struct Impressora
{
    char nome_impressora[51];
    int id_impressora;
    int ocupado;
    int paginas_faltam;
    int id_documento;
} Impressora;

// Declaracao de variaveis globais
int soma_paginas = 0;
int documento_atual = 0;
int counter_quem_terminou = 0;
int total_documentos;
FILE *pFile_output;
FILE *pFile_input;
// TODO: mudar para os valores originais (1000)
Documento documentos[1000];
Impressora impressoras[1000];
int quem_terminou[1000];

void processar(Impressora *impressora)
{
    if (impressora->ocupado == FALSE)
    {
        impressora->ocupado = TRUE;
        impressora->paginas_faltam = documentos[documento_atual].total_paginas;
        impressora->id_documento = documento_atual;
        documento_atual += 1;
    }
    else
    {
        if (impressora->paginas_faltam > 1)
        {
            impressora->paginas_faltam -= 1;
            soma_paginas += 1;
        }
        else if (total_documentos >= documento_atual)
        {
            // TODO: quando chegar no maximo de documentos, parar de fazer analise
            quem_terminou[counter_quem_terminou] = impressora->id_documento;
            impressora->paginas_faltam = documentos[documento_atual].total_paginas;
            impressora->id_documento = documento_atual;
            soma_paginas += 1;
            documento_atual += 1;
            counter_quem_terminou += 1;
        }
        else
        {
            quem_terminou[counter_quem_terminou] = impressora->id_documento;
            impressora->paginas_faltam = documentos[documento_atual].total_paginas;
            impressora->id_documento = documento_atual;
            soma_paginas += 1;
        }
    }
}

int main(int argc, char *argv[])
{
    // Declarando variaveis
    int total_impressoras;
    int total_paginas = 0;
    // Abertura de arquivos
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
    // Coletando dados
    fscanf(pFile_input, "%i", &total_impressoras);
    fgetc(pFile_input);
    for (int i = 0; i < total_impressoras; i++)
    {
        fscanf(pFile_input, "%s", &impressoras[i].nome_impressora);
        impressoras[i].ocupado = FALSE;
        impressoras[i].id_impressora = i;
        fgetc(pFile_input);
    }
    fscanf(pFile_input, "%i", &total_documentos);
    fgetc(pFile_input);
    for (int i = 0; i < total_documentos; i++)
    {
        fscanf(pFile_input, "%s %i", &documentos[i].nome_documento, &documentos[i].total_paginas);
        total_paginas += documentos[i].total_paginas;
        fgetc(pFile_input);
    }

    // Processamento dados,
    while (soma_paginas < total_paginas)
    {
        for (int i = 0; i < total_impressoras; i++)
        {
            processar(&impressoras[i]);
        }
    }

    // Impressao dos dados
    for (int i = total_documentos - 1; i >= 0; i--)
    {
        printf("%s\n", documentos[quem_terminou[i]].nome_documento);
    }
    // Fechamento dos arquivos
    fclose(pFile_input);
    fclose(pFile_output);
    return 0;
}