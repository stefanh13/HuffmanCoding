#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H
#include <string>

using namespace std;

struct HuffmanNode
{
    HuffmanNode(int frequency, char letter);
    bool is_leaf();

    char letter;
    int frequency;
    HuffmanNode *left;
    HuffmanNode *right;
};

typedef HuffmanNode* NodePtr;

#endif // HUFFMANNODE_H
