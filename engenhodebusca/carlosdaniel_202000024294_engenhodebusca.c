#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checksum(char arr[])
{
    int length = strlen(arr);
    int ans = (int)arr[0];
    for (int i = 1; i < length; i++)
    {
        ans = (ans ^ (int)arr[i]);
    }

    return ans;
}

int main(int argc, char *argv[])
{
    // Declaracao de variaveis
    FILE *pFile_input;
    FILE *pFile_output;
    int n;
    int valor;
    int servidores;
    int capacidade_maxima;
    // Leitura de arquivos
    pFile_input = fopen("engenhodebusca.input", "r");
    if (pFile_input == NULL)
    {
        return 1;
    }
    pFile_output = fopen("teste.output", "w");
    if (pFile_output == NULL)
    {
        return 1;
    }

    fscanf(pFile_input, "%i %i", &servidores, &capacidade_maxima);
    fprintf(pFile_output, "%i %i\n", servidores, capacidade_maxima);
    fgetc(pFile_input);
    fscanf(pFile_input, "%i", &n);
    fgetc(pFile_input);
    for (int i = 0; i < n; i++)
    {
        fscanf(pFile_input, "%i", &n);
        fprintf(pFile_output, "%i\n", n);

        for (int j = 0; j < n; j++)
        {
            fscanf(pFile_input, "%i", &valor);
            fprintf(pFile_output, "%i ", valor);
            fgetc(pFile_input);
        }
        fprintf(pFile_output, "\n");
        fgetc(pFile_input);
    }

    // Fechando arquivos
    fclose(pFile_input);
    fclose(pFile_output);

    return 0;
}