// C implementation of search and insert operations
// on Trie
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALFABETO (26)
#define MAX 9999
#define WORD_LENGTH 21
/* Its used to record the max length of the autocomplete */
int max_length = 0;
/* function insert utilizes this*/
char palavra[WORD_LENGTH];
char buffer[MAX];
int index_palavra;
struct TrieNode {
  struct TrieNode *children[ALFABETO];
  int level;
  bool isEndOfWord;
};

/* Cria uma referencia para pNode, verifica se malloc foi criado,
entao define pnode->IsEndOfword como falso e seus filhos como nulo */
struct TrieNode *getNode(void) {
  struct TrieNode *pNode = NULL;

  pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));

  if (pNode) {
    pNode->isEndOfWord = false;
    for (int i = 0; i < ALFABETO; i++) {
      pNode->children[i] = NULL;
    }
  }

  return pNode;
}
/* Retorna o valor max entre a e b*/
int max(int a, int b) { return (a > b) ? a : b; }
/* Recebe char c e retorna o seu valor int*/
int charToIndex(char c) { return (int)c - (int)'a'; }
/* Recebe node, e atravessa toda a array para verificar se
   de fato é o ultimo node, se checar uma crianca, retorna 0
   Assim constatando que nao é ultimo node. */
bool isLastNode(struct TrieNode *root) {
  for (int i = 0; i < ALFABETO; i++)
    if (root->children[i]) {
      return 0;
    }
  return 1;
}
/* Recebe dois valores, o node root, e um char key,
   é convertido key em int para descobrir a altura dela
   como max_lenght é valor global, é feito a avalicao se
   length é o maior */
void insert(struct TrieNode *root, const char *key) {
  int length = strlen(key);
  max_length = max(max_length, length);
  int index;
  int level;

  struct TrieNode *cur = root;

  for (level = 0; level < length; level++) {
    index = charToIndex(key[level]);
    if (!cur->children[index]) {
      cur->children[index] = getNode();
    }
    cur->level = level;
    cur = cur->children[index];
  }
  cur->isEndOfWord = true;
}
/* Append last char to array
   ? why use size_t? */
char *appendCharToCharArray(const char *array, char a) {
  int len = strlen(array);
  char *ret = (char *)malloc(sizeof(len));

  strcpy(ret, array);
  ret[len] = a;
  ret[len + 1] = '\0';

  return ret;
}
/** TODO: Definir uma descricao sobre essa funcao*/
void suggestionsRec(struct TrieNode *root, const char *currPrefix) {
  // found a string in Trie with the given prefix
  if (root == NULL) {
    return;
  }

  if (root->isEndOfWord) {
    strcat(buffer, currPrefix);
    strcat(buffer, ",");
  }
  for (int i = 0; i < ALFABETO; i++)
    if (root->children[i] && root->level < index_palavra + 2) {
      // child node character value
      char child = 'a' + i;
      suggestionsRec(root->children[i],
                     appendCharToCharArray(currPrefix, child));
    }
}

/** TODO: Preciso fazer com que palavras com pelo menos length 3, sejam
 * sugeridas */
void search(struct TrieNode *root, const char *key) {
  int index, level;
  // Define the length to run on a for loop
  int length = strlen(key);
  /* Define index_palavra, but its used only here?*/
  index_palavra = 0;
  /* Crio uma copia do root para poder fazer a travessia*/
  struct TrieNode *pCrawl = root;

  for (level = 0; level < length + 1; level++) {
    index = charToIndex(key[level]);

    if (level > 1) {
      suggestionsRec(pCrawl, palavra);
    }
    if (pCrawl == NULL) {
      break;
    }

    palavra[index_palavra] = key[level];
    index_palavra++;
    pCrawl = pCrawl->children[index];
  }
  /* Reseto a apalvra porque ela vai ser usada denovo futuras vezes*/
  memset(palavra, 0, WORD_LENGTH);
}

int main(int argc, char const *argv[]) {
  char linha[21];
  int qnt_termos, qnt_solicitacoes;
  /* getNode acts like constructor*/
  struct TrieNode *root = getNode();
  FILE *Input;
  FILE *Output;
  Input = fopen(argv[1], "r");
  // Input = fopen("autocompletarlarge.input", "r");
  if (Input == NULL) {
    return 1;
  }
  Output = fopen(argv[2], "w");
  // Output = fopen("meu.output", "w");
  if (Output == NULL) {
    return 1;
  }
  /* input of qnt_termos*/
  fscanf(Input, "%i", &qnt_termos);
  /* input of each term and insert in the node */
  for (int i = 0; i < qnt_termos; i++) {
    fscanf(Input, "%s", linha);
    insert(root, linha);
  }
  /* input of qnt_solicitations*/
  fscanf(Input, "%i", &qnt_solicitacoes);
  /* read all the solicitatiosn and process then*/
  for (int i = 0; i < qnt_solicitacoes; i++) {
    /* read the line and print the whole word*/
    fscanf(Input, "%s", linha);
    fprintf(Output, "%s:", linha);
    /* search and find the suggestions, if buffer is null
       print "-", else, print buffer to output
       ? Why I put null to buffer?
       * because if strlen equals to 0 it will give "-" as output
       * And remove the last ","*/
    search(root, linha);
    buffer[strlen(buffer) - 1] = '\0';
    if (buffer[0] == '\0') {
      fprintf(Output, "-");
    } else {
      fprintf(Output, "%s", buffer);
    }
    memset(buffer, 0, MAX);

    fprintf(Output, "\n");
  }

  return 0;
}
