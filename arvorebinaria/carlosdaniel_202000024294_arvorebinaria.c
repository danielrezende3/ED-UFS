#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

FILE *pOutput;
char copia_linhas[70];
char teste[] = " 1";
char linha[70];
int i = 0;

struct Node
{
    // 50 (até) caracteres + 1 ponto + 2 de leitura escrita + 1 espaço + 7 (até) bytes + 1 \0
    char data[70];
    int order;
    struct Node *left;
    struct Node *right;
};

struct Node *Insert(struct Node *root, char data[])
{
    if (root == NULL)
    {
        root = (struct Node *)malloc(sizeof(struct Node));
        memcpy(root->data, linha, 70);
        root->order = i;
        i++;
        root->left = NULL;
        root->right = NULL;
    }
    else if (memcmp(root->data, data, strlen(data)) <= 0)
    {
        root->right = Insert(root->right, data);
    }
    else
    {
        root->left = Insert(root->left, data);
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
        if ((strstr(root->data, "rw") != NULL) && (strstr(linha, "ro") != NULL))
        {
            memcpy(root->data, linha, 70);
            root->order = i;
            i++;
            return TRUE;
        }
        else if (strstr(root->data, "ro") != NULL)
        {
            return TRUE;
        }
        else if ((strstr(root->data, "rw") != NULL) && (strstr(linha, "rw") != NULL))
        {
            memcpy(root->data, linha, 70);
            root->order = i;
            i++;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
        
    }
    else if (memcmp(root->data, data, strlen(data)) >= 0)
    {
        return Search(root->left, data);
    }
    else
    {
        return Search(root->right, data);
    }
}

void Preorder(struct Node *root)
{
    // base condition for recursion
    // if tree/sub-tree is empty, return and exit
    if (root == NULL)
    {
        return;
    }
    if (strcmp(root->data + strlen(root->data) - 2, teste) == 0)
    {
        fprintf(pOutput, "%i %s byte\n", root->order, root->data); // Print data
    }
    else
    {
        fprintf(pOutput, "%i %s bytes\n", root->order, root->data); // Print data
    }                                                               // Print data
    Preorder(root->left);                                           // Visit left subtree
    Preorder(root->right);                                          // Visit right subtree
}

void Inorder(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }

    Inorder(root->left); // Visit left subtree
    if (strcmp(root->data + strlen(root->data) - 2, teste) == 0)
    {
        fprintf(pOutput, "%i %s byte\n", root->order, root->data); // Print data
    }
    else
    {
        fprintf(pOutput, "%i %s bytes\n", root->order, root->data); // Print data
    }
    Inorder(root->right); // Visit right subtree
}

void Postorder(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }

    Postorder(root->left);  // Visit left subtree
    Postorder(root->right); // Visit right subtree
    if (strcmp(root->data + strlen(root->data) - 2, teste) == 0)
    {
        fprintf(pOutput, "%i %s byte\n", root->order, root->data); // Print data
    }
    else
    {
        fprintf(pOutput, "%i %s bytes\n", root->order, root->data); // Print data
    }                                                               // Print data
}

int main(int argc, char *argv[])
{
    // Declaração de variáveis
    int total;
    int j;
    int avaliar;
    char seps[] = " ";
    char *next_token = NULL;
    struct Node *root = NULL;
    // Abertura de arquivos
    FILE *pInput;
    // TODO: Trocar "teste.input" por argv[1]
    pInput = fopen("meu.input", "r");
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

    for (j = 0; j < total; j++)
    {
        fscanf(pInput, "%[^\n]", linha);
        memcpy(copia_linhas, linha, 70);
        strtok_r(copia_linhas, seps, &next_token);
        avaliar = Search(root, copia_linhas);
        // teste
        if (avaliar == 1)
        {
            fgetc(pInput);
            continue;
        }

        root = Insert(root, copia_linhas);
        fgetc(pInput);
    }

    // Print Nodes 
    fprintf(pOutput, "EPD:\n");
    Inorder(root);
    fprintf(pOutput, "PED:\n");
    Preorder(root);
    fprintf(pOutput, "EDP:\n");
    Postorder(root);
    return 0;
}
