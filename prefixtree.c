#include "prefixtree.h"

#include <stdio.h>
#include <stdlib.h>

struct TreeNode *createTreeNode(int childrensCount)
{
    struct TreeNode *treeNode = malloc(sizeof(struct TreeNode));
    treeNode->childrensCount = childrensCount;
    treeNode->childrens = calloc(childrensCount, sizeof(struct TreeNode *));
    if(!treeNode->childrens)
        printf("calloc error");
    treeNode->isWord = 0;
    return treeNode;
}

void deleteTreeNode(struct TreeNode *treeNode)
{
    for(int i = 0; i < treeNode->childrensCount; ++i)
        if(treeNode->childrens[i])
            deleteTreeNode(treeNode->childrens[i]);

    free(treeNode->childrens);
    free(treeNode);
}

struct PrefixTree *createPrefixTree(int minValue, int maxValue)
{
    struct PrefixTree *prefixTree = malloc(sizeof(struct PrefixTree));
    prefixTree->minValue = minValue;
    prefixTree->maxValue = maxValue;
    prefixTree->treeNode = createTreeNode(maxValue - minValue + 1);
    return prefixTree;
}

void deletePrefixTree(struct PrefixTree *tree)
{
    deleteTreeNode(tree->treeNode);
    free(tree);
}

char *subtracFromString(const char *str, int strLength, int value)
{
    char *subtractedString = malloc(strLength);
    for(int i = 0; i < strLength; ++i)
        subtractedString[i] = str[i] - value;

    return subtractedString;
}

void _insertString(struct TreeNode *root, const char *str, int strLength)
{
    struct TreeNode *it = root;

    for(int i = 0; i < strLength; ++i)
    {
        unsigned char ch = str[i];
        if(!it->childrens[ch])
            it->childrens[ch] = createTreeNode(it->childrensCount);

        it = it->childrens[ch];
    }

    it->isWord = 1;
}

void insertString(struct PrefixTree *tree, const char *str, int strLength)
{
    char *subtractedString = subtracFromString(str, strLength, tree->minValue);
    _insertString(tree->treeNode, subtractedString, strLength);
    free(subtractedString);
}

char containsString(struct PrefixTree *tree, const char *str, int strLength)
{
    char *subtractedString = subtracFromString(str, strLength, tree->minValue);

    struct TreeNode *it = tree->treeNode;
    int i = 0;

    while(it && i < strLength)
    {
        unsigned char ch = (unsigned char) subtractedString[i];
        it = it->childrens[ch];
        ++i;
    }

    free(subtractedString);

    if(it)
        if(1 == it->isWord && i == strLength)
            return 1;
    return 0;
}
