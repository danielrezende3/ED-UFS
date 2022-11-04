#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pessoa
{
    char nome_pessoa[51];
    unsigned int idade;
    int atendimento; // 0 convencional, 1 preferencial
    int prioridade;
} Pessoa;

typedef struct Orgao
{
    char nome_orgao[51];
    unsigned int qnt_atendentes;
    unsigned int tamanho;
    Pessoa *pessoa;
    int qnt_pessoas;
} Orgao;

int parent(int i)
{
    return (i - 1) / 2;
    // return i+1;
}
int left(int i)
{
    return (2 * i) + 1;
}

int right(int i)
{
    return (2 * i) + 2;
}

void swap(Pessoa *array, int a, int b)
{
    Pessoa temp = *(array + b);
    *(array + b) = *(array + a);
    *(array + a) = temp;
}

void heapify(Pessoa *array, int tamanho, int i)
{
    int pai = i, esquerda = left(i), direita = right(i);

    if (esquerda < tamanho &&
        array[esquerda].atendimento < array[pai].atendimento)
    // && array[esquerda].idade > array[pai].idade)
    {
        pai = esquerda;
    }
    if (direita < tamanho &&
        array[direita].atendimento < array[pai].atendimento)
    // && array[direita].idade > array[pai].idade)
    {
        pai = direita;
    }
    if (pai != i)
    {
        swap(array, i, pai);
        heapify(array, tamanho, pai);
    }
}

void insert(Pessoa *pessoa, unsigned int *tamanho)
{
    // Faz if-else, checa condicao se for o primeiro numero, pois
    // nao e necessario fazer heapify
    int pai = parent(*tamanho);
    if (*tamanho == 0)
    {
        (*tamanho)++;
    }
    else
    {
        (*tamanho)++;
        for (int i = pai; i >= 0; i--)
        {
            heapify(pessoa, *tamanho, i);
        }
    }
}

void deleteroot(Orgao *orgao)
{
    // Esta fora do for porque eu preciso guardar essa informacao
    // Encontra o numero e guarda a posicao na variavel i
    // Percebi que nunca vai ser nulo pois o malloc ja foi feito
    if (&(orgao->pessoa[0]) != NULL)
    {
        swap(orgao->pessoa, 0, orgao->tamanho - 1);
        orgao->tamanho--;
        int pai = parent(orgao->tamanho);
        for (int i = pai; i >= 0; i--)
        {
            heapify(orgao->pessoa, orgao->tamanho, i);
        }
    }
}
int main(int argc, char const *argv[])
{
    FILE *input;
    FILE *output;
    int qnt_orgaos;
    int qnt_pessoas;
    // Buffer that captures the entire string
    char line[110];

    // Leitura dos arquivos
    // input = fopen(argv[1], "r");
    input = fopen("controledesenha.input", "r");
    if (input == NULL)
    {
        return 1;
    }

    // Escrita dos arquivos
    // output = fopen(argv[2], "w");
    output = fopen("meu.output", "w");
    if (output == NULL)
    {
        return 1;
    }
    // Leitura qnt de orgaos
    fscanf(input, "%i", &qnt_orgaos);

    // Alocacao de memoria pra orgaos
    Orgao *orgao = (Orgao *)malloc(qnt_orgaos * sizeof(struct Orgao));

    // Faz a leitura e armazenamento de dados dos orgaos,
    // inicializa orgao[i].tamanho = 0
    for (int i = 0; i < qnt_orgaos; i++)
    {
        fscanf(input, "%s %i", orgao[i].nome_orgao, &orgao[i].qnt_atendentes);
        orgao[i].tamanho = 0;
    }

    // Ler qnt_pessoas e malloc dentro da struct
    fscanf(input, "%i", &qnt_pessoas);
    for (int i = 0; i < qnt_orgaos; i++)
    {
        orgao[i].pessoa = (Pessoa *)malloc(qnt_pessoas * sizeof(struct Pessoa));
    }

    // pula para a proxima linha
    fgetc(input);

    for (int i = 0; i < qnt_pessoas; i++)
    {
        // Capture the entire line
        fscanf(input, "%[^\n]", line);

        // separate until "|"
        char *token = strtok(line, "|");

        // Faz separacao da string in teira e faz o heapify
        for (int j = 0; j < qnt_orgaos; j++)
        {
            // Compare token with name orgao, to input to correct
            // orgao
            int ret = strcmp(token, orgao[j].nome_orgao);
            if (ret == 0)
            {
                int size = orgao[j].tamanho;
                // separate until "|"
                token = strtok(NULL, "|");
                // Copia e cola token para nome_pessoa
                strcpy(orgao[j].pessoa[size].nome_pessoa, token);
                // separate until "|"
                token = strtok(NULL, "|");
                // transforma string token em int e assimila a idade
                orgao[j].pessoa[size].idade = atoi(token);
                // Checa idade para gerar preferencial
                if (orgao[j].pessoa[size].idade < 60)
                {
                    orgao[j].pessoa[size].atendimento = (size+1)*101;
                }
                else
                {
                    orgao[j].pessoa[size].atendimento = (size+1);
                }

                // heapify struct
                insert(orgao[j].pessoa, &orgao[j].tamanho);
            }
        }
        // pula para a proxima linha
        fgetc(input);
    }
    int flag = 1;
    while (flag)
    {
        flag = 0;
        for (int i = 0; i < qnt_orgaos; i++)
        {
            if (orgao[i].tamanho > 0)
            {
                printf("%s:", orgao[i].nome_orgao);
            }
            for (unsigned int j = 0; j < orgao[i].qnt_atendentes; j++)
            {
                if (orgao[i].tamanho > 1 && (orgao[i].qnt_atendentes - 1) != j)
                {
                    flag = 1;
                    printf("%s,", orgao[i].pessoa->nome_pessoa);
                    deleteroot(&orgao[i]);
                }
                else if (orgao[i].tamanho > 0 && (orgao[i].qnt_atendentes - 1) == j)
                {
                    flag = 1;
                    printf("%s", orgao[i].pessoa->nome_pessoa);
                    deleteroot(&orgao[i]);
                }
                else
                {
                    flag = 0;
                }
            }
            if (orgao[i].tamanho >= 0 && flag == 1)
            {
                printf("\n");
            }
        }
    }
    return 0;
}
// 77 64 35 22 61
// 33 22