#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *input;
    FILE *output;

    // Leitura e escrita dos arquivos
    input = fopen(argv[1], "r");
    // input = fopen("loteria.input", "r");
    if (input == NULL)
    {
        return 1;
    }
    output = fopen(argv[2], "w");
    // pOutput = fopen("meu.output", "w");
    if (output == NULL)
    {
        return 1;
    }



    return 0;
}
