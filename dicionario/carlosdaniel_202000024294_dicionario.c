#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LENGTH 32 // palavra(30) + 1\0
#define TOTAL_SINONIMOS 11
#define SINONIMO_LENGTH (WORD_LENGTH * TOTAL_SINONIMOS) // ((palavra) 30 + 1 (espaco)) x 10
#define TOTAL_LENGTH (WORD_LENGTH + SINONIMO_LENGTH)    // word_length + sinonimo_length

FILE *pOutput;
char linha[TOTAL_LENGTH];
char sinonimos[TOTAL_LENGTH];
char numero[TOTAL_LENGTH];

struct Node
{
    int height;
    int qnt_sinonimos;
    char palavra[TOTAL_LENGTH];
    char sinonimos[TOTAL_LENGTH];
    struct Node *left;
    struct Node *right;
};

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(struct Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

int getBalance(struct Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return height(node->left) - height(node->right);
}

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

struct Node *newNode(char data[])
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    strcpy(node->palavra, data);
    strcpy(node->sinonimos, sinonimos);
    node->qnt_sinonimos = atoi(numero);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct Node *insert(struct Node *node, char data[])
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
    {
        return (newNode(data));
    }
    if (strcmp(node->palavra, data) <= 0)
    {
        node->left = insert(node->left, data);
    }
    else if (strcmp(node->palavra, data) > 0)
    {
        node->right = insert(node->right, data);
    }

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), height(node->right));

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && strcmp(node->left->palavra, data) < 0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && strcmp(node->right->palavra, data) > 0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && strcmp(node->left->palavra, data) > 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && strcmp(node->right->palavra, data) < 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

struct Node *search(struct Node *node, char data[])
{
    if (node == NULL)
    {

        // ffprintf(pOutput,pOutput, "-\n");
        fprintf(pOutput, "?]\n-\n");
        return NULL;
    }
    if (strcmp(node->palavra, data) == 0)
    {
        fprintf(pOutput, "%s]", node->palavra);
        fprintf(pOutput, "\n");
        fprintf(pOutput, "%s\n", node->sinonimos);
        return node;
    }
    if (strcmp(node->palavra, data) < 0)
    {
        fprintf(pOutput, "%s->", node->palavra);
        node->left = search(node->left, data);
    }
    else if (strcmp(node->palavra, data) > 0)
    {
        fprintf(pOutput, "%s->", node->palavra);
        node->right = search(node->right, data);
    }
    return node;
}

void replace_spaces(char *str)
{
    while (*str)
    {
        if (*str == ' ')
            *str = ',';
        str++;
    }
}

int main(int argc, char const *argv[])
{
    int total_words;
    int total_searchs;
    char palavra[TOTAL_LENGTH];
    total_words = 0;
    total_searchs = 0;
    struct Node *root = NULL;
    FILE *pInput;
    // pOutput = fopen(argv[1], "r");
    pInput = fopen(argv[1], "r");
    if (pInput == NULL)
    {
        return 1;
    }
    // pOutput = fopen(argv[2], "w");
    pOutput = fopen(argv[2], "w");
    if (pOutput == NULL)
    {
        return 1;
    }

    // pega o total de palavras a serem adicionadas, faz um loop com a linha inteira,
    // Separa a primeira palavra, retira o número, coloca entre os sinonimos virgula."
    fscanf(pInput, "%i", &total_words);
    fgetc(pInput);
    for (int i = 0; i < total_words; i++)
    {
        fscanf(pInput, "%s %s", palavra, numero); 
        fscanf(pInput, "%[^\n]", sinonimos+1);
        replace_spaces(sinonimos);
        // inserção no node
        root = insert(root, palavra);
        // fgetc sempre fica por último
        fgetc(pInput);
    }

    fscanf(pInput, "%i", &total_searchs);
    fgetc(pInput);
    for (int i = 0; i < total_searchs; i++)
    {
        fscanf(pInput, "%s", linha);
        fprintf(pOutput, "[");
        search(root, linha);
        fgetc(pInput);
    }

    return 0;
}
