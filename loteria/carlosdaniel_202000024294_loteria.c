#include <stdio.h>

FILE *pInput;
FILE *pOutput;

int main(int argc, char const *argv[])
{
    int premio;
    int qnt_apostas;
    int arr_sorteados[15];
    char letra[33];
    // pInput = fopen(argv[1], "r");
    pInput = fopen("loteria.input", "r");
    if (pInput == NULL)
    {
        return 1;
    }
    // pOutput = fopen(argv[2], "w");
    pOutput = fopen("meu.output", "w");
    if (pOutput == NULL)
    {
        return 1;
    }
    fscanf(pInput, "%i", &premio);
    fscanf(pInput, "%i", &qnt_apostas);
    for (int i = 0; i < 10; i++)
    {
        fscanf(pInput, "%i", &arr_sorteados[i]);
    }
    fscanf(pInput, "%s", letra);
    for (int i = 0; i < 15; i++)
    {
        fscanf(pInput, "%i", &arr_sorteados[i]);
    }

    return 0;
}
