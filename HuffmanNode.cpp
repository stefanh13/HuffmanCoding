#include <cstddef>
#include "HuffmanNode.h"

HuffmanNode::HuffmanNode(int frequency, char letter)
{
    this->frequency = frequency;
    this->letter = letter;
    left = NULL;
    right = NULL;
}

bool HuffmanNode::is_leaf()
{
    return left == NULL && right == NULL;
}
