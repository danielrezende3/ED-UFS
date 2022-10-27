#include <stdio.h>

#define TAMANHO_SORTEADO 10
#define TAMANHO_APOSTA 15
#define TAMANHO_HASH 33

typedef struct Ticket
{
    int qnt_acertos;
    char identificador[TAMANHO_HASH];
    int num_apostados[TAMANHO_APOSTA];
    int tamanho;
    int flag;
} Ticket;

int parent(int i)
{
    return (i - 1) / 2;
}
int left(int i)
{
    return (2 * i) + 1;
}

int right(int i)
{
    return (2 * i) + 2;
}

void swap(int *array, int a, int b)
{
    int temp = array[b];
    array[b] = array[a];
    array[a] = temp;
}

void heapify(int *array, int tamanho, int i)
{
    int pai = i, esquerda = left(i), direita = right(i);

    if (esquerda < tamanho && array[esquerda] > array[pai])
    {
        pai = esquerda;
    }
    if (direita < tamanho && array[direita] > array[pai])
    {
        pai = direita;
    }
    if (pai != i)
    {
        swap(array, i, pai);
        heapify(array, tamanho, pai);
    }
}

void insert(Ticket *ticket, int num)
{
    // Faz if-else, checa condicao se for o primeiro numero, pois
    // nao e necessario fazer heapify
    if (ticket->tamanho == 0)
    {
        ticket->num_apostados[ticket->tamanho] = num;
        ticket->tamanho++;
    }
    else
    {
        ticket->num_apostados[ticket->tamanho] = num;
        ticket->tamanho++;
        int pai = parent(ticket->tamanho);
        for (int i = pai; i >= 0; i--)
        {
            heapify(ticket->num_apostados, ticket->tamanho, i);
        }
    }
}
void deleteRoot(Ticket *root, int num)
{
    // Esta fora do for porque eu preciso guardar essa informacao
    // Encontra o numero e guarda a posicao na variavel i
    int i;
    for (i = 0; i < root->tamanho; i++)
    {
        if (num = root->num_apostados[i])
        {
            break;
        }
    }
    // faz a troca sempre do ultimo valor para o primeiro, como
    // diz a regra, diminui o tamanho em um, e reorganiza a heap
    swap(root->num_apostados, i, root->tamanho - 1);
    root->tamanho--;
    int pai = parent(root->tamanho);
    for (int i = pai; i >= 0; i--)
    {
        heapify(root->num_apostados, root->tamanho, i);
    }
}
int main(int argc, char const *argv[])
{
    int premio;
    int numero;
    FILE *pInput;
    FILE *pOutput;
    int qnt_apostas;

    // Leitura e escrita dos arquivos
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
    Ticket sorteado;
    Ticket apostas[qnt_apostas];
    sorteado.tamanho = 0;
    // Coleta os numeros da loteria e faz uma arvore heap
    for (int i = 0; i < TAMANHO_SORTEADO; i++)
    {
        fscanf(pInput, "%i", &numero);
        insert(&sorteado, numero);
    }
    // sempre repete a nova estrutura apostas com tamanho e qnt_acertos 0
    // Faz a coleta dos numeros e faz uma arvora heap
    for (int i = 0; i < qnt_apostas; i++)
    {
        apostas[i].tamanho = 0;
        apostas[i].qnt_acertos = 0;
        fscanf(pInput, "%s", apostas[i].identificador);
        for (int j = 0; j < TAMANHO_APOSTA; j++)
        {
            fscanf(pInput, "%i", &numero);
            insert(&apostas[i], numero);
        }
    }

    
    return 0;
}