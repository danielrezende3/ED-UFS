// C implementation of search and insert operations
// on Trie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALFABETO (26)

int max_length = 0;
char palavra[21];
int index_palavra = 0;
FILE *pInput;
FILE *pOutput;
char buffer[21 * 9000];

struct TrieNode
{
    struct TrieNode *children[ALFABETO];

    bool isEndOfWord;
};

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int char_to_index(char c)
{
    return (int)c - (int)'a';
}

struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = NULL;

    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));

  if (pNode) {
        pNode->isEndOfWord = false;

        for (int i = 0; i < ALFABETO; i++)
            pNode->children[i] = NULL;
    }

    return pNode;
}

bool isLastNode(struct TrieNode *root)
{
    for (int i = 0; i < ALFABETO; i++)
        if (root->children[i])
        {
            return 0;
        }
    return 1;
}

void insert(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    max_length = max(max_length, length);
    int index;

    struct TrieNode *cur = root;

    for (level = 0; level < length; level++)
    {
        index = char_to_index(key[level]);
        if (!cur->children[index])
        {

            cur->children[index] = getNode();
        }

        cur = cur->children[index];
    }

    cur->isEndOfWord = true;
}

char *appendCharToCharArray(const char *array, char a)
{
    size_t len = strlen(array);
    char *ret = (char *)malloc(2 * sizeof(len));

    strcpy(ret, array);
    ret[len] = a;
    ret[len + 1] = '\0';

    return ret;
}

void suggestionsRec(struct TrieNode *root, const char *currPrefix)
{
    // found a string in Trie with the given prefix
    if (root->isEndOfWord)
    {
        strcat(buffer, currPrefix);
        strcat(buffer, ",");
    }

    for (int i = 0; i < ALFABETO; i++)
        if (root->children[i])
        {
            // child node character value
            char child = 'a' + i;
            suggestionsRec(root->children[i], appendCharToCharArray(currPrefix, child));
        }
}
void search(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    index_palavra = 0;
    struct TrieNode *pCrawl = root;

    for (level = 0; level < length + 1; level++)
    {
        index = char_to_index(key[level]);

        if (!pCrawl->children[index])
        {
            if (palavra[0] == 0)
            {
                break;
            }
            else
            {
                suggestionsRec(pCrawl, palavra);
                break;
            }
        }
        palavra[index_palavra] = key[level];
        index_palavra++;
        pCrawl = pCrawl->children[index];
    }
    memset(palavra, 0, sizeof(palavra));
}

int main(int argc, char const *argv[])
{
    char linha[21];
    int qnt_termos, qnt_solicitacoes;
    struct TrieNode *root = getNode();

    pInput = fopen(argv[1], "r");
    // pInput = fopen("autocompletar.input", "r");
    if (pInput == NULL)
    {
        return 1;
    }
    pOutput = fopen(argv[2], "w");
    // pOutput = fopen("meu.output", "w");
    if (pOutput == NULL)
    {
        return 1;
    }

    fscanf(pInput, "%i", &qnt_termos);

    for (int i = 0; i < qnt_termos; i++)
    {
        fscanf(pInput, "%s", linha);
        insert(root, linha);
    }

    fscanf(pInput, "%i", &qnt_solicitacoes);
    for (int i = 0; i < qnt_solicitacoes; i++)
    {
        fscanf(pInput, "%s", linha);
        fprintf(pOutput, "%s:", linha);
        search(root, linha);
        buffer[strlen(buffer) - 1] = '\0';
        if (buffer[0] == '\0')
        {
            fprintf(pOutput, "-");
        }
        else
        {

            fprintf(pOutput, "%s", buffer);
        }

        memset(buffer, 0, sizeof(palavra));

        fprintf(pOutput, "\n");
    }

    return 0;
}
