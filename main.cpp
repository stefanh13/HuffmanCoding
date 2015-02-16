#include <iostream>
#include <string>
#include <assert.h>
#include <cstdlib>
#include <cstring>
#include "HuffmanNode.h"
#include "HuffmanPriorityQueue.h"

using namespace std;

const int INDENT_SIZE = 2;

// Prints the Huffman tree 'root' to the standard output, indented by 'indent' spaces.
// The printed tree is labeled (i.e., prefixed) by the string 'prefix'.
void print_tree(NodePtr root, int indent = 0, string prefix = "")
{
    // External nodes are not printed.
    if(root == NULL) {
        return;
    }

    char letter = ' ';
    if(root->is_leaf()) {
        letter = root->letter;
    }

    cout << string(indent, ' ') << prefix << "(" << letter << " [" << root->frequency << "]";
    if(root->is_leaf()) {
        cout << ")" << endl;
    } else {
        cout << endl;
        // Print left and right subtrees with the appropriate prefix, and
        // increased indent (by INDENT_SIZE).
        print_tree(root->left, indent + INDENT_SIZE, "0");
        print_tree(root->right, indent + INDENT_SIZE, "1");
        cout << string(indent, ' ') << ")" << endl;
    }
}

// Reads a frequency table from standard input, builds the Huffman tree for that frequency table and
// returns (a pointer to the root of) the tree.
NodePtr build_tree()
{
    //declare variables
    int numb_letters;
    char huff_char;
    int huff_numb;

    //Get input, the number of letters
    cin >> numb_letters;

    HuffmanPriorityQueue queue;

    for(int i = 0; i < numb_letters; i++)
    {
        cin >> huff_char;
        cin >> huff_numb;
        //Create new Node with values from input
        NodePtr tmpPtr = new HuffmanNode(huff_numb, huff_char);
        //Push the new Node into the queue
        queue.push(tmpPtr);
    }

    NodePtr p = NULL;
    NodePtr a = NULL;
    NodePtr b = NULL;
    for(int i = 0; i < (numb_letters-1); i++)
    {
        //a points to the top of the queue
        a = queue.top();
        //pop the top Node
        queue.pop();
        //Same as above
        b = queue.top();
        queue.pop();
        //Create new Node with frequency equal to the sum of a and b frequency and set character as \0
        p = new HuffmanNode(a->frequency + b->frequency, '\0');
        //Set a as left child of p
        p->left = a;
        //Set b as right child of p
        p->right = b;
        //Push p into the queue
        queue.push(p);
    }

    if(numb_letters == 0)
    {
        return NULL;
    }
    return p;
}

// Returns the string obtained by decoding 'encoded_str' with the Huffman tree 'root' (or more
// specifically, the Huffman tree whose root is 'root').
string decode(NodePtr root, string encoded_str)
{
    //String that will contain
    string result = "";

    //int count_char = 0;
     int i = 0;
     int string_size = encoded_str.size();
     NodePtr tmpPtr = NULL;

    while(i < string_size)
    {
        tmpPtr = root;
        while (!tmpPtr->is_leaf())
        {
            if(encoded_str[i] == '0')
            {
                tmpPtr = tmpPtr->left;
            }
            if(encoded_str[i] == '1')
            {
                tmpPtr = tmpPtr->right;
            }

            i++;

        }

        result += tmpPtr->letter;
    }

    return result;
}

// * Optional, but recommended *
// Returns true if and only if the tree 'root', contains the node with the letter 'letter'.
bool contains(NodePtr root, char letter)
{
    //Check if the root is null, then return false
    if(root == NULL)
    {
        return false;
    }
    //if the inputed letter equals to the letter in the node, then return true
    if(letter == root->letter)
    {
        return true;
    }

    return contains(root->left, letter) || contains(root->right, letter);

}

// Returns the binary code obtained by encoding 'letter' with the Huffman tree 'root' (or more
// specifically, the Huffman tree whose root is 'root').
string encode(NodePtr root, char letter)
{
    //Declare an empty string
    string result = "";
    //Loop that goes through the tree until it reaches a leaf
    while(!root->is_leaf())
    {
        //If the left tree contains the letter then perform this
        if(contains(root->left, letter))
        {
            root = root->left;
            result += "0";
        }
        //If the right tree contains the letter then perform this
        else if(contains(root->right, letter))
        {
            root = root->right;
            result += "1";
        }
    }
    //Return the string result
    return result;
}

// Frees (deallocates) the memory allocated for the Huffman tree 'root' (or more
// specifically, the Huffman tree whose root is 'root').
void free_memory(NodePtr root)
{
    //Declare a temp pointer Node to root for deleting purposes later
    NodePtr tmpPtr = root;
    //This statement will run as lon as the root is not a leaf
    if(!root->is_leaf())
    {
        //Calling free_memory recusively to visit every Node of the tree
        free_memory(root->left);

        free_memory(root->right);
    }
    //Set the left child of root as NULL
    root->left = NULL;
    //Set the right child of root as NULL
    root->right = NULL;
    //Delete the temp pointer Node, preventing memory leak
    delete tmpPtr;
}

int main()
{
    // Read frequency table and build Huffman tree.
    NodePtr huffman = build_tree();
    //Declare a string to decode
    string decode_string;
    //Declare a string that takes encoded strings from the encode function
    string result;
    //Declare an integer that says how many encodes are performed
    int number_encodes;
    cin >> number_encodes;
    //Loop that performs number of encodings
    for(int i = 0; i < number_encodes; i++)
    {
        cin >> decode_string;
        //Set result to empty string to get an empty string between encodings
        result = "";
        //Loop that goes through every character in the string
        for(unsigned int j = 0; j < decode_string.size(); j++)
        {
            result += encode(huffman, decode_string[j]);
        }
        //Printing the result from the encoded string
        cout << result << endl;
    }

    //Destroying the tree
    free_memory(huffman);

    return 0;
}

