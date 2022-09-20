#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LENGTH 31 // palavra(30) + 1\0
#define TOTAL_SINONIMOS 10
#define SINONIMO_LENGTH (WORD_LENGTH*TOTAL_SINONIMOS) // ((palavra) 30 + 1 (espaco)) x 10
#define TOTAL_LENGTH (WORD_LENGTH+SINONIMO_LENGTH) // word_length + sinonimo_length

char linha[TOTAL_LENGTH];

struct Node
{
    int height;
    char palavra[WORD_LENGTH];
    char sinonimos[TOTAL_SINONIMOS][WORD_LENGTH];
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
    memcpy(node->palavra, data, WORD_LENGTH);
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
    if (memcmp(node->palavra, data, strlen(data)) < 0)
    {
        node->left = insert(node->left, data);
    }
    else if (memcmp(node->palavra, data, strlen(data)) > 0)
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
    if (balance > 1 && data < node->left->palavra)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->palavra)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && data > node->left->palavra)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->palavra)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

int main(int argc, char const *argv[])
{
    int total_words;
    int total_searchs;
    char espaco[] = " ";
    char palavra1[WORD_LENGTH];
    char *token = NULL;

    struct Node *root = NULL;

    FILE *pInput;
    FILE *pOutput;
    // TODO: Trocar "teste.input" por argv[1]
    pInput = fopen("slide.input", "r");
    if (pInput == NULL)
    {
        return 1;
    }
    // TODO: Trocar "meu.output" por "argv[2]"
    pOutput = fopen("meu.output", "w");
    if (pOutput == NULL)
    {
        return 1;
    }

    fscanf(pInput, "%i", &total_words);
    fgetc(pInput);
    // pega o total de palavras a serem adicionadas, faz um loop com a linha inteira,
    // Separa a primeira palavra, retira o número, e coloca em "sinonimo[]" 
    for (int i = 0; i < total_words; i++)
    {
        fscanf(pInput, "%[^\n]", linha);
        memcpy(palavra1, linha, WORD_LENGTH);
        strtok_r(palavra1, espaco, &token);
        root = insert(root, palavra1);
        // sempre fica por último
        fgetc(pInput);
    }
    fscanf(pInput, "%i", &total_searchs);
    fgetc(pInput);
    for (int i = 0; i < total_searchs; i++)
    {
        // TODO
    }
    
    
    return 0;
}

