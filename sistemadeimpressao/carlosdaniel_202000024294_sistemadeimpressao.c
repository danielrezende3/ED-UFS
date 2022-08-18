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
    int qnt_doc_impressos;
    int arr_id_documento[1000];
} Impressora;

// Declaracao de variaveis globais
int soma_paginas = 0;
int documento_atual = 0;
int counter_quem_terminou = 0;
int total_documentos;
FILE *pFile_output;
FILE *pFile_input;
Documento documentos[1000];
Impressora impressoras[1000];
int quem_terminou[1000];

// Processamento dos dados, ele vai alterando o estado de acorod com qual impressora esta livre,
// assim colocando um printf ao inicio da impressao
void processar(Impressora *impressora)
{
    if (impressora->ocupado == FALSE)
    {
        // Antes de alterar dados
        impressora->ocupado = TRUE;
        impressora->paginas_faltam = documentos[documento_atual].total_paginas;
        impressora->id_documento = documento_atual;
        impressora->arr_id_documento[impressora->qnt_doc_impressos] = impressora->id_documento;
        fprintf(pFile_output, "[%s] %s-%ip\n", impressora->nome_impressora, documentos[documento_atual].nome_documento, documentos[documento_atual].total_paginas);

        // Depois de alterar dados
        impressora->qnt_doc_impressos += 1;
        documento_atual += 1;
    }
    else
    {
        if (impressora->paginas_faltam > 1)
        {
            impressora->paginas_faltam -= 1;
            soma_paginas += 1;
        }
        else if (total_documentos > documento_atual)
        {
            // Antes de alterar dados
            quem_terminou[counter_quem_terminou] = impressora->id_documento;
            impressora->paginas_faltam = documentos[documento_atual].total_paginas;
            impressora->id_documento = documento_atual;
            impressora->arr_id_documento[impressora->qnt_doc_impressos] = impressora->id_documento;
            // Depois de alterar dados
            soma_paginas += 1;
            documento_atual += 1;
            counter_quem_terminou += 1;
            impressora->qnt_doc_impressos += 1;
            fprintf(pFile_output, "[%s] ", impressora->nome_impressora);
            for (int i = impressora->qnt_doc_impressos - 1; i >= 0; i--)
            {
                int valor = impressora->arr_id_documento[i];
                if (i == 0)
                {
                    fprintf(pFile_output, "%s-%ip", documentos[valor].nome_documento, documentos[valor].total_paginas);
                }
                else
                {
                    fprintf(pFile_output, "%s-%ip, ", documentos[valor].nome_documento, documentos[valor].total_paginas);
                }
            }
            fprintf(pFile_output, "\n");
        }
        else if (impressora->paginas_faltam > 0)
        {
            // Antes de alterar dados
            quem_terminou[counter_quem_terminou] = impressora->id_documento;

            // Depois de alterar dados
            counter_quem_terminou += 1;
            impressora->paginas_faltam -= 1;
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
    pFile_input = fopen(argv[1], "r");
    if (pFile_input == NULL)
    {
        return 1;
    }
    pFile_output = fopen(argv[2], "w");
    if (pFile_output == NULL)
    {
        return 1;
    }
    // Coletando dados
    fscanf(pFile_input, "%i", &total_impressoras);
    fgetc(pFile_input);
    for (int i = 0; i < total_impressoras; i++)
    {
        fscanf(pFile_input, "%s", impressoras[i].nome_impressora);
        impressoras[i].ocupado = FALSE;
        impressoras[i].id_impressora = i;
        fgetc(pFile_input);
    }
    fscanf(pFile_input, "%i", &total_documentos);
    fgetc(pFile_input);
    for (int i = 0; i < total_documentos; i++)
    {
        fscanf(pFile_input, "%s %i", documentos[i].nome_documento, &documentos[i].total_paginas);
        total_paginas += documentos[i].total_paginas;
        fgetc(pFile_input);
    }

    // Processamento dados
    while (soma_paginas < total_paginas)
    {
        for (int i = 0; i < total_impressoras; i++)
        {
            processar(&impressoras[i]);
        }
    }

    // Impressao dos dados
    fprintf(pFile_output, "%ip\n", total_paginas);
    for (int i = total_documentos - 1; i >= 0; i--)
    {
        if (i == 0)
        {
            fprintf(pFile_output, "%s-%ip", documentos[quem_terminou[i]].nome_documento, documentos[quem_terminou[i]].total_paginas);
        }
        else
        {
            fprintf(pFile_output, "%s-%ip\n", documentos[quem_terminou[i]].nome_documento, documentos[quem_terminou[i]].total_paginas);
        }
    }
    // Fechamento dos arquivos
    fclose(pFile_input);
    fclose(pFile_output);
    return 0;
}