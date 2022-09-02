#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
    int value;
    char teste1[] = "te amo";
    char teste2[] = "Te amo";
    value = strcmp(teste1,teste2);
    return 0;
}