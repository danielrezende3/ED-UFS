#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

char copia_linhas[62];
char linha[62];
int i = 1;

struct Node
{
    // 50 (até) caracteres + 1 ponto + 2 de leitura escrita + 1 espaço + 7 (até) bytes + 1 \0
    char data[62];
    int order;
    struct Node *left;
    struct Node *right;
};

struct Node *Insert(struct Node *root, char data[])
{
    if (root == NULL)
    {
        root = (struct Node *)malloc(sizeof(struct Node));
        memcpy(root->data, data, 62);
        root->left = NULL;
        root->right = NULL;
    }
    else if (memcmp(root->data, data, strlen(data)) <= 0)
    {
        root->left = Insert(root->left, data);
    }
    else
    {
        root->right = Insert(root->right, data);
    }

    return root;
}

int Search(struct Node *root, char data[])
{
    // Atravessa a árvore em procura do arquivo, se nada for encontrado, retornar FALSE, se encontrar TRUE.
    // A adição dessa função é de que se o arquivo for do tipo "rw", deletar.
    if (root == NULL)
    {
        return FALSE;
    }
    else if (strstr(root->data, data) != NULL)
    {
        if (strstr(root->data, "rw") != NULL)
        {
            memcpy(copia_linhas, root->data, 62);
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else if (strcmp(root->data, linha) <= 0)
    {
        return Search(root->left, data);
    }
    else
    {
        return Search(root->right, data);
    }
}

struct Node *FindMin(struct Node *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

struct Node *Delete(struct Node *root, char data[])
{
    if (root == NULL)
        return root;
    else if (strcmp(root->data, data) < 0)
        root->left = Delete(root->left, data);
    else if (strcmp(root->data, data) > 0)
        root->right = Delete(root->right, data);
    else
    {
        // Case 1:  No child
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;
        }
        // Case 2: One child
        else if (root->left == NULL)
        {
            struct Node *temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL)
        {
            struct Node *temp = root;
            root = root->left;
            free(temp);
        }
        // case 3: 2 children
        else
        {
            struct Node *temp = FindMin(root->left);
            memcpy(root->data, temp->data, 62);
            root->left = Delete(root->left, temp->data);
        }
    }
    return root;
}

void Preorder(struct Node *root)
{
    // base condition for recursion
    // if tree/sub-tree is empty, return and exit
    if (root == NULL)
        return;
    Preorder(root->left);                       // Visit left subtree
    printf("%i %s\n", root->order, root->data); // Print data
    Preorder(root->right);                      // Visit right subtree
}

void Inorder(struct Node *root)
{
    if (root == NULL)
        return;

    Inorder(root->right);                       // Visit right subtree
    printf("%i %s\n", root->order, root->data); // Print data
    Inorder(root->left);                        // Visit left subtree
}

int main(int argc, char *argv[])
{
    // Declaração de variáveis
    int total;
    int avaliar;
    char seps[] = " ";
    char *token = NULL;
    char *next_token = NULL;
    struct Node *root = NULL;

    // Abertura de arquivos
    FILE *pInput;
    FILE *pOutput;
    // TODO: Trocar "teste.input" por "argv[1]"
    pInput = fopen("casoteste.input", "r");
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

    fscanf(pInput, "%i", &total);
    fgetc(pInput);
    // Pega a linha completa, realiza um token com apenas o arquivo (ex: "lista_ed.c") e procura na árvore
    // Se não encontrar, apenas inserir, sem problemas,
    // Se encontrar, procurar saber se é possivel deletar e inserir o novo arquivo, se não, cancela a operação.
    for (int i = 0; i < total; i++)
    {
        fscanf(pInput, "%[^\n]", linha);
        memcpy(copia_linhas, linha, 62);
        // token = strtok_r(copia_linhas, seps, &next_token);
        // avaliar = Search(root, copia_linhas);
        // if (avaliar == 1)
        // {
        //     root = Delete(root, copia_linhas);
        // }

        root = Insert(root, linha);
        fgetc(pInput);
    }
    
    // Print Nodes in Preorder.
    printf("Preorder:\n");
    Preorder(root);
    printf("\n");
    printf("Inorder:\n");
    Inorder(root);
    printf("\n");
    return 0;
}
