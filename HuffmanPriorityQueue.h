#ifndef HUFFMANPRIORITYQUEUE_H
#define HUFFMANPRIORITYQUEUE_H

#include <queue>
#include "HuffmanNode.h"

using namespace std;

struct HuffmanComparator
{
    bool operator() (const NodePtr& lhs, const NodePtr& rhs) const
    {
        NodePtr lhs_leftmost = lhs, rhs_leftmost = rhs;
        if(lhs->frequency == rhs->frequency)
        {
            // Ensure total ordering

            //  Find leftmost leaf of lhs
            while(!lhs_leftmost->is_leaf())
            {
                lhs_leftmost = lhs_leftmost->left;
            }

            //  Find leftmost leaf of rhs
            while(!rhs_leftmost->is_leaf())
            {
                rhs_leftmost = rhs_leftmost->left;
            }

            return lhs_leftmost->letter > rhs_leftmost->letter;
        }
        return lhs->frequency > rhs->frequency;
    }
};

typedef priority_queue<NodePtr, vector<NodePtr>, HuffmanComparator> HuffmanPriorityQueue;

#endif //HUFFMANPRIORITYQUEUE_H
