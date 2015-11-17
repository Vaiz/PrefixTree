#ifndef PREFIXTREE_H
#define PREFIXTREE_H

struct TreeNode
{
    struct TreeNode **childrens;
    int childrensCount;

    char isWord;
};

struct PrefixTree
{
    int minValue;
    int maxValue;

    struct TreeNode *treeNode;
};

struct PrefixTree *createPrefixTree(int minValue, int maxValue);
void deletePrefixTree(struct PrefixTree *tree);
void insertString(struct PrefixTree *tree, const char *str, int strLength);
char contaisString(struct PrefixTree *tree, const char *str, int strLength);

#endif // PREFIXTREE_H
