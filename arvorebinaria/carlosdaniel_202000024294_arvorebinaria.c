#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Declaração de variáveis
    int total;
    // Abertura de arquivos
    FILE *pFile_input;
    FILE *pFile_output;
    // TODO: Trocar "teste.input" por "argv[1]"
    pFile_input = fopen("teste.input", "r");
    if (pFile_input == NULL)
    {
        return 1;
    }
    // TODO: Trocar "meu.output" por "argv[2]"
    pFile_output = fopen("meu.output", "w");
    if (pFile_output == NULL)
    {
        return 1;
    }
    fscanf(pFile_input, "%i", &total);
    fgetc(pFile_input);
    for (int i = 0; i < total; i++)
    {
        
    }
    
    return 0;
}