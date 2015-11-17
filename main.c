#include <stdio.h>
#include <string.h>

#include "prefixtree.h"

#define BUF_SIZE 1024

struct PrefixTree *loadTree(const char *fileName);

int main(int argc, char *argv[])
{
    if(1 >= argc)
        return 1;

    struct PrefixTree *tree = loadTree(argv[1]);

    char str[BUF_SIZE];
    while(1)
    {
        printf("Input string: ");
        scanf("%s", str);

        if(strcmp(str, "exit") == 0)
            break;

        if(1 == containsString(tree, str, strlen(str)))
            printf("YES\r\n");
        else
            printf("NO\r\n");

    }

    deletePrefixTree(tree);

    return 0;
}

void prefixTreeSample()
{
    struct PrefixTree *prefixTree = createPrefixTree(32, 127);
    insertString(prefixTree, "abcd", 4);
    insertString(prefixTree, "sadr", 4);
    insertString(prefixTree, "fved", 4);
    insertString(prefixTree, "vcefd", 5);

    if(1 == containsString(prefixTree, "abcd", 4))
        printf("Contain 'abcd'\r\n");
    else
        printf("NO 'abcd'\r\n");

    if(1 == containsString(prefixTree, "abc", 3))
        printf("Contain 'abc'\r\n");
    else
        printf("NO 'abc'\r\n");

    deletePrefixTree(prefixTree);
}

struct PrefixTree *loadTree(const char *fileName)
{
    struct PrefixTree *prefixTree = createPrefixTree(32, 127);

    FILE *file = fopen(fileName, "r");

    char str[BUF_SIZE];
    while(fgets(str, BUF_SIZE, file))
    {
        int strLength = strlen(str);

        if(str[strLength - 1] == '\n')
            strLength--;

        if(strLength == 0)
            continue;

        if(str[strLength - 1] == '\r')
            strLength--;

        if(strLength == 0)
            continue;

        insertString(prefixTree, str, strLength);
    }

    fclose(file);

    return prefixTree;
}
