#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *input;
    FILE *output;
    input = fopen(argv[1], "r");
    if (input == NULL)
    {
        return 1;
    }
    output = fopen(argv[2], "w");
    if (output == NULL)
    {
        return 1;
    }
    return 0;
}