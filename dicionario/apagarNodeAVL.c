#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int height;
    int data;
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

struct Node *minValueNode(struct Node *node)
{
    struct Node *current = node;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

struct Node *newNode(int number)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = number;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

struct Node *insert(struct Node *node, int data)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
    {
        return (newNode(data));
    }
    if (data < node->data)
    {
        node->left = insert(node->left, data);
    }
    else if (data > node->data)
    {
        node->right = insert(node->right, data);
    }
    else // Equal datas are not allowed in BST
    {
        return node;
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
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && data > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

struct Node *delete (struct Node *node, int data)
{

    // STEP 1: PERFORM STANDARD BST DELETE
    if (node == NULL)
        return node;

    // If the data to be deleted is smaller
    // than the node's data, then it lies
    // in left subtree
    if (data < node->data)
        node->left = delete (node->left, data);

    // If the data to be deleted is greater
    // than the node's data, then it lies
    // in right subtree
    else if (data > node->data)
        node->right = delete (node->right, data);

    // if data is same as node's data, then
    // This is the node to be deleted
    else
    {
        // node with only one child or no child
        if ((node->left == NULL) || (node->right == NULL))
        {
            struct Node *temp = node->left ? node->left : node->right;

            // No child case
            if (temp == NULL)
            {
                temp = node;
                node = NULL;
            }
            else
            {                  // the non-empty child
                *node = *temp; // Copy the contents of
            }                  // One child case

            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct Node *temp = minValueNode(node->right);

            // Copy the inorder successor's
            // data to this node
            node->data = temp->data;

            // Delete the inorder successor
            node->right = delete (node->right, temp->data);
        }
    }

    if (node == NULL)
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // If this node becomes unbalanced,
    // then there are 4 cases
    // Left Left Case
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    // Left Right Case
    if (balance > 1 && getBalance(node->left) < 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    // Right Left Case
    if (balance < -1 && getBalance(node->right) > 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void preOrder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%i ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }

}

int main(int argc, char const *argv[])
{
    int total_numbers;
    int number;
    int total_deletes;
    struct Node *root = NULL;

    FILE *pInput;
    FILE *pOutput;
    // TODO: Trocar "teste.input" por argv[1]
    pInput = fopen("apagarNodeAVL.input", "r");
    if (pInput == NULL)
    {
        return 1;
    }
    // TODO: Trocar "meu.output" por "argv[2]"
    pOutput = fopen("apagarNodeAVL.output", "w");
    if (pOutput == NULL)
    {
        return 1;
    }

    fscanf(pInput, "%i", &total_numbers);
    fgetc(pInput);
    for (int i = 0; i < total_numbers; i++)
    {
        fscanf(pInput, "%i", &number);
        root = insert(root, number);
        fgetc(pInput);
    }
    preOrder(root);
    printf("\n");

    fscanf(pInput, "%i", &total_deletes);
    fgetc(pInput);
    for (int i = 0; i < total_deletes; i++)
    {
        fscanf(pInput, "%i", &number);
        delete (root, number);
        fgetc(pInput);
    }
    preOrder(root);
    printf("\n");

    return 0;
}
