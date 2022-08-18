#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int counter = 1;

typedef struct
{
    char ISBN_string[14];
    unsigned int ISBN_number;
    char Autor[51];
    char Titulo[101];
} Livros;

typedef struct
{
    char ISBN_string[14];
    int resultado_bb;
    int counter_bb;
    int resultado_bi;
    int counter_bi;
} Resultado;

int bb(Livros *V, int n, int x)
{
    // Índices de partições
    counter = 1;
    int i = 0, j = n - 1;
    int p = (i + j) / 2;

    // Iterações de 1 -> k
    while (j >= i && V[p].ISBN_number != x)
    {

        if (V[p].ISBN_number > x)
            j = p - 1;
        else
            i = p + 1;
        p = (i + j) / 2;
        counter++;
    }
    return (V[p].ISBN_number == x) ? (p) : (-1);
}

int bi(Livros *V, int n, int x)
{
    // Índices de partições
    counter = 1;
    int i = 0;
    int j = n - 1;
    int p = abs(i + (V[j].ISBN_number - V[i].ISBN_number) % (j - i + 1));
    // Iterações de 1 -> k
    while (j >= i && V[p].ISBN_number != x)
    {
        if (V[p].ISBN_number > x)
        {
            j = p - 1;
            if (j < 0)
            {
                return (V[p].ISBN_number == x) ? (p) : (-1);
            }
        }
        else
        {
            i = p + 1;
            if (i < 0)
            {
                return (V[p].ISBN_number == x) ? (p) : (-1);
            }
        }

        p = abs(i + (V[j].ISBN_number - V[i].ISBN_number) % (j - i + 1));
        counter++;
    }
    return (V[p].ISBN_number == x) ? (p) : (-1);
}
int main(int argc, char *argv[])
{
    // Abrindo os arquivos
    FILE *pFile_input;
    FILE *pFile_output;
    Resultado resultado[99];
    Livros livros[99];
    char line[164];
    char compare_string[14];
    int compare_int;
    int num_livros;
    int consultas = 1;
    int valor;
    int media_bb;
    int media_bi;
    int i = -1;
    int j = 0;
    int vitoria_bb = 0;
    int vitoria_bi = 0;
    int soma_bi = 0;
    int soma_bb = 0;

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

    // Leitura dos arquivos
    fscanf(pFile_input, "%i", &num_livros);
    while ((fscanf(pFile_input, "%[^\n]", line)) != EOF)
    {
        if (i < 0)
        {
            i += 1;
            fgetc(pFile_input);
            continue;
        }
        else if (i >= 0 && i < num_livros)
        {
            memcpy(livros[i].ISBN_string, line, 13);
            livros[i].ISBN_number = atoi(livros[i].ISBN_string);
            livros[i].ISBN_number = livros[i].ISBN_number % 2011;
            memcpy(livros[i].Autor, line + 14, strcspn(line + 14, "&"));
            memcpy(livros[i].Titulo, line + strlen(livros[i].Autor) + 15, 101);
            fgetc(pFile_input);
            i += 1;
        }
        else if (i == num_livros)
        {
            consultas = line[0] - 48;
            fgetc(pFile_input);
            i += 1;
        }
        else if (i > num_livros && i <= num_livros + consultas)
        {

            memcpy(compare_string, line, 13);
            compare_int = atoi(compare_string);
            compare_int = compare_int % 2011;
            strcpy(resultado[j].ISBN_string, compare_string);
            resultado[j].resultado_bb = bb(livros, num_livros, compare_int);
            resultado[j].counter_bb = counter;
            resultado[j].resultado_bi = bi(livros, num_livros, compare_int);
            resultado[j].counter_bi = counter;
            i += 1;
            j += 1;
            fgetc(pFile_input);
        }
    }
    for (int i = 0; i < consultas; i++)
    {
        fprintf(pFile_output, "[%s]B=%i,I=%i", resultado[i].ISBN_string, resultado[i].counter_bb, resultado[i].counter_bi);
        if (resultado[i].counter_bi <= resultado[i].counter_bb)
        {
            vitoria_bi += 1;
        }
        else
        {
            vitoria_bb += 1;
        }
        valor = resultado[i].resultado_bb;
        soma_bb += resultado[i].counter_bb;
        soma_bi += resultado[i].counter_bi;
        if (valor >= 0)
        {
            fprintf(pFile_output, ":Author:%s,Title:%s\n", livros[valor].Autor, livros[valor].Titulo);
        }
        else
        {
            fprintf(pFile_output, ":ISBN_NOT_FOUND\n");
        }
    }
    media_bb = soma_bb / consultas;
    media_bi = soma_bb / consultas;
    fprintf(pFile_output, "BINARY=%i:%i\n", vitoria_bb, media_bb);
    fprintf(pFile_output, "INTERPOLATION=%i:%i", vitoria_bi, media_bi);

    // fechando os arquivos
    fclose(pFile_input);
    fclose(pFile_output);
    return 0;
}