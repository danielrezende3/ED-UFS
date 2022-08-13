#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *ponteiro;
    ponteiro = fopen("arquivo.txt", "r");
    if (ponteiro == NULL)
    {
        printf("Erro na abertura do arquivo\n");
    }
    else
    {
        printf("Arquivo aberto!");
        fclose(ponteiro);
    }

    return 0;
}