// Comecei a estudar 0514
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *GetNewNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *Insert(Node *root, int data)
{
    if (root == NULL)
    {
        root = GetNewNode(data);
        return root;
    }
    else if (data <= root->data)
    {
        root->left = Insert(root->left, data);
    }
    else
    {
        root->right = Insert(root->right, data);
    }

    return root;
}

Node *FindMin(Node *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

int Search(Node *root, int data)
{
    if (root == NULL)
    {
        return FALSE;
    }
    else if (root->data == data)
    {
        return TRUE;
    }
    else if (data <= root->data)
    {
        return Search(root->left, data);
    }
    else
    {
        return Search(root->right, data);
    }
}

struct Node *Delete(struct Node *root, int data)
{
    if (root == NULL)
        return root;
    else if (data < root->data)
        root->left = Delete(root->left, data);
    else if (data > root->data)
        root->right = Delete(root->right, data);
    // Wohoo... I found you, Get ready to be deleted
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
            struct Node *temp = FindMin(root->right);
            root->data = temp->data;
            root->right = Delete(root->right, temp->data);
        }
    }
    return root;
}

int main(int argc, char *argv[])
{
    int total_numbers, value_of_node, total_deletes;
    Node *root = NULL;
    FILE *pInput;
    pInput = fopen("professor.input", "r");
    if (pInput == NULL)
    {
        return 1;
    }
    fscanf(pInput, "%i", &total_numbers);
    fgetc(pInput);
    for (int i = 0; i < total_numbers; i++)
    {
        fscanf(pInput, "%i", &value_of_node);
        root = Insert(root, value_of_node);
    }
    fscanf(pInput, "%i", &total_deletes);
    fgetc(pInput);
    for (int i = 0; i < total_deletes; i++)
    {
        fscanf(pInput, "%i", &value_of_node);
        root = Delete(root, value_of_node);
    }

    return 0;
}