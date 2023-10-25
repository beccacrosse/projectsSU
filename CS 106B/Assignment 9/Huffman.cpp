#include "Huffman.h"
#include "GUI/SimpleTest.h"
#include "hashmap.h"
#include "vector.h"
#include "priorityqueue.h"
#include <string>
using namespace std;

EncodingTreeNode* decodeTreeRec(Queue<Bit>& bits, Queue<char>& leaves, EncodingTreeNode* tree);
HashMap<char, Vector<Bit>> encodingTableCreator(EncodingTreeNode* tree, HashMap<char, Vector<Bit>> encodingTable, Vector<Bit> path);

/**
 * Deallocates all nodes in a Huffman tree. We've provided this helper function
 * to you since we also use it in our test driver and figured you might want
 * to make use of it.
 */
void deleteTree(EncodingTreeNode* tree) {
    if (tree != nullptr) {
        deleteTree(tree->zero);
        deleteTree(tree->one);
        delete tree;
    }
}

/**
 * Constructs a Huffman coding tree for the given string, using the algorithm
 * described in lecture.
 *
 * If the input string does not contain at least two different characters,
 * this function should report an error.
 *
 * When assembling larger trees out of smaller ones, make sure to set the first
 * tree dequeued from the queue to be the zero subtree of the new tree and the
 * second tree as the one subtree.
 */
/*
EncodingTreeNode* huffmanTreeFor(const string& str) {
    //find frequency of every char and store in a map
    HashMap<char, int> leaves = {};
    for(char letter: str){
        if(!leaves.containsKey(letter)){
            leaves[letter] = 0;
        }
        leaves[letter] ++;
    }
    //if there's less than 2 different chars report error
    if(leaves.size() < 2)
        error("Invalid input");

    //make a queue for the different chars
    PriorityQueue<EncodingTreeNode*> treeQ;
    //enqueue every char as pointer to a node
    for(char letter: leaves){
        EncodingTreeNode* leaf = new EncodingTreeNode{letter, nullptr, nullptr};
        treeQ.enqueue(leaf, leaves[letter]);
    }
    //while queue isnt empty
    while(treeQ.size() >= 2){
        //create new parent tree
         EncodingTreeNode* branch = new EncodingTreeNode;

        //take weight of child 0
        int weight = treeQ.peekPriority();
        //remove child from queue and add it to parent tree
        branch->zero = treeQ.dequeue();

        //take weight of child 1
        weight += treeQ.peekPriority();
        //remove child from queue and add it to parent tree
        branch->one = treeQ.dequeue();

        //add parent tree with combined weight of children
        treeQ.enqueue(branch, weight);
    }
    //return final element
    return treeQ.dequeue();
}*/

/**
 * Given a Queue<Bit> containing a compressed message and a tree that was used
 * to encode those bits, decodes the bits back to the original message.
 *
 * You can assume the input tree is not null and is not a single character;
 * those are edge cases you don't need to handle.
 *
 * You can assume the input Queue<Bit> is well-formed in that every character
 * was encoded correctly, there are no stray bits in the Queue, etc.

string decodeText(Queue<Bit>& bits, EncodingTreeNode* tree) {
    (void) bits;
    (void) tree;
    return "";
}*/

/*
 * This function is a recursive wrapper for decodeTree that builds up and returns a complete
 * Huffman tree from the Queues bits and leaves.
 *
 * param: Queue<Bit>& bits:
 * param: Queue<char>& leaves:
 * param EncodingTreeNode*: the pointer to the root of Huffman tree we are building
 * return EncodingTreeNode*: pointer to root of Huffman tree
 */
/*
 * Given a string and a Huffman encoding tree, encodes that text using the tree
 * and outputs a Queue<Bit> corresponding to the encoded representation.
 *
 * The input tree will not be null and will not consist of a single node; these
 * are edge cases you don't have to handle. The input tree will contain all
 * characters that make up the input string.
Queue<Bit> encodeText(const string& str, EncodingTreeNode* tree) {
    (void) str;
    (void) tree;
    return {};
}*/


/**
 * Decodes the given Queue<Bit> and Queue<char> into a Huffman coding tree.
 *
 * You can assume that the input Queues are structured properly in that they
 * represent a legal encoding of a tree, that there aren't stray characters
 * or bits in them, etc.
EncodingTreeNode* decodeTree(Queue<Bit>& bits, Queue<char>& leaves) {

    (void) bits;
    (void) leaves;
    return nullptr;
}*/


/**
 * Encodes the given Huffman tree as a Queue<Bit> and Queue<char> in the manner
 * specified in the assignment handout.
 *
 * You can assume the input Queues are empty on entry to this function.
 *
 * You can assume that the Huffman tree provided to you is properly structured,
 * in that each internal node will have two children and only the characters in
 * the leaves matter, etc.

void encodeTree(EncodingTreeNode* tree, Queue<Bit>& bits, Queue<char>& leaves) {
    (void) tree;
    (void) bits;
    (void) leaves;
}*/


/**
 * Compresses the given text string using Huffman coding, producing as output
 * a HuffmanResult containing the encoded tree and message.
 *
 * Your implementation of this function should report an error if there are
 * fewer than two distinct characters in the input string.

HuffmanResult compress(const string& text) {
    (void) text;
    return {};
}*/

/**
 * Decompresses the given HuffmanResult and returns the string it represents.
 *
 * Your implementation may change the file parameter however it sees fit. There
 * are no requirements about what it should look like after this function
 * returns.
 *
 * You can assume the input file is well-formed and was created by a correct
 * implementation of compress.

string decompress(HuffmanResult& file) {
    (void) file;
    return "";
}*/

EncodingTreeNode* huffmanTreeFor(const string& str) {
    // build HashMap that keeps track of frequency
    HashMap<char, int> bits = {};
    for (char ch : str) {
        if (!bits.containsKey(ch))
            bits[ch] = 0;
        bits[ch]++;
    }

    // if there are less than 2 unique characters in the passed in str
    if (bits.size() <= 1)
        error("String isn't long enough.");

    // PriorityQueue used to keep track of smaller Huffman trees
    PriorityQueue<EncodingTreeNode*> order;

    // creates every EncodingTreeNode that is a part of the final Huffman tree
    for (char bit: bits) {
        // builds up every variable in newNode
        EncodingTreeNode* leaf = new EncodingTreeNode{bit, nullptr, nullptr};
        // enqueues it based on its frequency, bits[bit], which was found earlier
        order.enqueue(leaf, bits[bit]);
    }
// tracker for priority needed later
    int parentPriority = 0;

    // runs until there is 1 Huffman tree left
    while(order.size() >= 2) {
        // creates parentNode, the pointer to the EncodingTreeNode that is the parent Node
        // for the two soon-to-be dequeued EncodingTreeNodes*
        EncodingTreeNode* parentNode = new EncodingTreeNode;
        // parentPriority is sum of its children's priority
        parentPriority += order.peekPriority();
        // removes the lowest priority EncodingTreeNode* and assigns it as the zero child of parentNode
        parentNode->zero = order.dequeue();
        // parentPriority is sum of its children's priority
        parentPriority += order.peekPriority();
        // removes the lowest priority EncodingTreeNode* and assigns it as the one child of parentNode
        parentNode->one = order.dequeue();
        // parentNode is built and is ready to be enqueued back into order
        order.enqueue(parentNode, parentPriority);
        // reset value of parentPriority for next loop
        parentPriority = 0;
    }
    // final Huffman tree is returned
    return order.dequeue();
}

string decodeText(Queue<Bit>& bits, EncodingTreeNode* tree) {
    // compiled is decoded message we need to build from passed in bits
    string compiled = "";

    // reset pointer for tree;
    EncodingTreeNode* beginning = tree;

    // run through entire sequence of bits
    while (!bits.isEmpty()) {
        // while there is no char in the Node we are currently at in the tree
        // NOTE: bits is being destroyed because dequeue() removes every time
        while (tree->zero != nullptr && tree->one != nullptr) {
            if (bits.dequeue() == 0)
                tree = tree->zero;
            else
                tree = tree->one;
        }
        // once we have reached a Node with a char associated with it, add the char
        // to the string we are eventually returning
        compiled += tree->ch;
        // reset tree
        tree = beginning;
    }

    // the string is fully compiled
    return compiled;
}

Queue<Bit> encodeText(const string& str, EncodingTreeNode* tree) {
    // creates encoding table, that'll make navigating through the passed in Huffman tree much easier
    HashMap<char, Vector<Bit>> encodingTable = encodingTableCreator(tree, {}, {});

    // bits is the encoded sequence we need to build from passed in str
    Queue<Bit> bits;

    // runs through every char in the string
    for (char ch : str) {
        // runs through every step needed to reach the char in the Huffman tree
        for (Bit step : encodingTable[ch]) {
            bits.enqueue(step);
        }
    }

    // the encoded sequence is fully compiled
    return bits;
}

HashMap<char, Vector<Bit>> encodingTableCreator(EncodingTreeNode* tree, HashMap<char, Vector<Bit>> encodingTable, Vector<Bit> path) {
    // base case
    if (tree->zero == nullptr && tree->one == nullptr) {
        encodingTable[tree->ch] = path;
        return encodingTable;
    }
    // recursive step
    else {
        // go down zero path
        path.add(0);
        encodingTable += encodingTableCreator(tree->zero, encodingTable, path);
        // go down one path
        path.remove(path.size() - 1);
        path.add(1);
        encodingTable += encodingTableCreator(tree->one, encodingTable, path);
    }
    return encodingTable;
}

EncodingTreeNode* decodeTree(Queue<Bit>& bits, Queue<char>& leaves) {
    EncodingTreeNode* tree = new EncodingTreeNode;
    tree->zero = nullptr;
    tree->one = nullptr;
    return decodeTreeRec(bits, leaves, tree);
}
/*
 * This function is a recursive wrapper for decodeTree that builds up and returns a complete
 * Huffman tree from the Queues bits and leaves.
 *
 * param: Queue<Bit>& bits:
 * param: Queue<char>& leaves:
 * param EncodingTreeNode*: the pointer to the root of Huffman tree we are building
 * return EncodingTreeNode*: pointer to root of Huffman tree
 */
EncodingTreeNode* decodeTreeRec(Queue<Bit>& bits, Queue<char>& leaves, EncodingTreeNode* tree) {
    // base case/leaf Node
    if (bits.dequeue() == 0) {
        tree->ch = leaves.dequeue();
        return tree;
    }
    // recursive step/interior Node
    else {
        // create zero child
        EncodingTreeNode* zeroNode = new EncodingTreeNode;
        zeroNode->zero = nullptr;
        zeroNode->one = nullptr;
        // create one child
        EncodingTreeNode* oneNode = new EncodingTreeNode;
        oneNode->zero = nullptr;
        oneNode->one = nullptr;
        // go down zero path
        tree->zero = decodeTreeRec(bits, leaves, zeroNode);
        // go down one path
        tree->one = decodeTreeRec(bits, leaves, oneNode);
    }
    return tree;
}
void encodeTree(EncodingTreeNode* tree, Queue<Bit>& bits, Queue<char>& leaves) {
    // base case/leaf Node
   if (tree->zero == nullptr && tree->one == nullptr) {
       // b/c tree is leaf Node
       bits.enqueue(0);
       leaves.enqueue(tree->ch);
   }
   // recursive step/interior Node
   else {
       // b/c tree is interior Node
       bits.enqueue(1);
       // go down the zero path
       encodeTree(tree->zero, bits, leaves);
       // go down the one path
       encodeTree(tree->one, bits, leaves);
   }
}
HuffmanResult compress(const string& text) {
    // create Huffman tree via string
    EncodingTreeNode* root = huffmanTreeFor(text);

    // created encoded text sequence
    Queue<Bit> createdMessageBits = encodeText(text, root);

    // create encoded tree queues
    Queue<Bit> createdTreeBits = {};
    Queue<char> createdLeaves = {};
    encodeTree(root, createdTreeBits, createdLeaves);

    // create final product
    HuffmanResult result{createdTreeBits, createdLeaves, createdMessageBits};
    // de-allocate unneeded memory
    deleteTree(root);
    return result;
}
string decompress(HuffmanResult& file) {
    // create Huffman tree via tree queues
    EncodingTreeNode* root = decodeTree(file.treeBits, file.treeLeaves);
    // create decoded text sequence
    string result = decodeText(file.messageBits, root);
    // de-allocate unneeded memory
    deleteTree(root);
    return result;
}


/* * * * * * Test Cases Below This Point * * * * * */



//Milestone 1: works for sequences with equal frequency of all chharacters or strings in different orders produce same tree
STUDENT_TEST("huffmanTreeFor builds a tree when all characters have equal weight.") {
    /*
     *         *
     *       /   \
     *       a    *
     *          /  \
     *         c    b
    */

    //makes a tree shape of one of the possibilities of a tree with tied weights
    EncodingTreeNode* reference = new EncodingTreeNode {'*',
            new EncodingTreeNode {'a', nullptr, nullptr},
            new EncodingTreeNode {'*', new EncodingTreeNode{ 'c', nullptr, nullptr},
                                        new EncodingTreeNode{'b', nullptr, nullptr}}
    };
    //makes a tree using our huffmanTreeFor function
    EncodingTreeNode* tree = huffmanTreeFor("aaabbbccc");

    //sets variables to find height of reference
    int heightR = 0;
    EncodingTreeNode* tempR = reference;
    //traverses reference, updating height
    while(tempR->one != nullptr){
        heightR ++;
        tempR = tempR->one;
    }
    //sets variables to find height of tree
    int heightT = 0;
    EncodingTreeNode* tempT = tree;
    while(tempT->one != nullptr){
        heightT ++;
        tempT = tempT->one;
    }
    //compares the height of reference and tree. Since ties can be broken randomly
    //randomly, multiple arrangements could be correct but the height must be correct.
    EXPECT(areEqual(heightR, heightT));

    deleteTree(reference);
    deleteTree(tree);
}

//Milestone 2 decode: Works for larger sample
PROVIDED_TEST("decodeText works on larger sample.") {
    /* This tree:
     *                 *0
     *                /   \
     *               *1        *2
     *             /   \     /  \
     *             X    O    *3     *4
     *                      / \    / \
     *                     N   Y   *5  *6
     *                            /\   /\
     *                           ?  !  S M
     */

     EncodingTreeNode* tree = new EncodingTreeNode {
             '*',
             //node 1
             new EncodingTreeNode{ '*',
                 new EncodingTreeNode{'X', nullptr, nullptr},
                 new EncodingTreeNode{'O', nullptr, nullptr}
             },
             //node 2
             new EncodingTreeNode{ '*',
                 //node 3
                 new EncodingTreeNode{'*',
                       new EncodingTreeNode{'N', nullptr, nullptr},
                       new EncodingTreeNode{'Y', nullptr, nullptr}
                    },
                 //node 4
                 new EncodingTreeNode{'*',
                    //node 5
                     new EncodingTreeNode{'*',
                            new EncodingTreeNode{'?', nullptr, nullptr},
                            new EncodingTreeNode{'!', nullptr, nullptr}
                    }, //node6 VV
                     new EncodingTreeNode{ '*',
                         new EncodingTreeNode{'S', nullptr, nullptr},
                         new EncodingTreeNode{'M', nullptr, nullptr}
                    }
                }

             }

};

    /* What you get if you encode XXYYMONSOON!? with this tree. */
    Queue<Bit> bits = { 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0,1, 1, 0, 1, 1, 1, 0, 0 };

    EXPECT_EQUAL(decodeText(bits, tree), "XXYYMONSOON!?");

    deleteTree(tree);
}

//milestine 2 encode: Works for larger sample
PROVIDED_TEST("encodeText works larger sample.") {
        /* This tree:
         *                 *0
         *                /   \
         *               *1        *2
         *             /   \     /  \
         *             X    O    *3     *4
         *                      / \    / \
         *                     N   Y   *5  *6
         *                            /\   /\
         *                           ?  !  S M
         */

         EncodingTreeNode* tree = new EncodingTreeNode {
                 '*',
                 //node 1
                 new EncodingTreeNode{ '*',
                     new EncodingTreeNode{'X', nullptr, nullptr},
                     new EncodingTreeNode{'O', nullptr, nullptr}
                 },
                 //node 2
                 new EncodingTreeNode{ '*',
                     //node 3
                     new EncodingTreeNode{'*',
                           new EncodingTreeNode{'N', nullptr, nullptr},
                           new EncodingTreeNode{'Y', nullptr, nullptr}
                        },
                     //node 4
                     new EncodingTreeNode{'*',
                        //node 5
                         new EncodingTreeNode{'*',
                                new EncodingTreeNode{'?', nullptr, nullptr},
                                new EncodingTreeNode{'!', nullptr, nullptr}
                        }, //node6 VV
                         new EncodingTreeNode{ '*',
                             new EncodingTreeNode{'S', nullptr, nullptr},
                             new EncodingTreeNode{'M', nullptr, nullptr}
                        }
                    }

                 }

    };

    /* What you get if you encode XXYYMONSOON!? with this tree. */
    Queue<Bit> expected = { 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0,1, 1, 0, 1, 1, 1, 0, 0 };

    EXPECT_EQUAL(encodeText("XXYYMONSOON!?", tree), expected);

    deleteTree(tree);
}

//Milestone 3 decode: Works for smallest valid sample
STUDENT_TEST("decodeText works on smallest valid sample.") {
                /* This tree:
                 *                 *
                 *                / \
                 *               H   I
                 */
                EncodingTreeNode* tree = new EncodingTreeNode {
                    '*',
                        new EncodingTreeNode { 'H', nullptr, nullptr },
                        new EncodingTreeNode { 'I', nullptr, nullptr}
                };

                /* What you get if you encode MONSOON with this tree. */
                Queue<Bit> bits = { 0, 1};

                EXPECT_EQUAL(decodeText(bits, tree), "HI");

                deleteTree(tree);
            }

//Milestone 3 encode: Works for smallest valid sample

STUDENT_TEST("encodeText works on smallest valid sample.") {
    /* This tree:
     *                 *
     *                / \
     *               N   O
     */
    EncodingTreeNode* tree = new EncodingTreeNode {
           '*',
           new EncodingTreeNode { 'N', nullptr, nullptr },
            new EncodingTreeNode{ 'O', nullptr, nullptr }
    };

    /* What you get if you encode NO with this tree. */
    Queue<Bit> expected = { 0, 1 };

    EXPECT_EQUAL(encodeText("NO", tree), expected);

    deleteTree(tree);
}

//Milestone 4: compress reports error if the input string is less than two distinct characters

STUDENT_TEST("compress reports error if the input string is less than two distinct characters") {
            EXPECT_ERROR(compress(""));    // No characters
            EXPECT_ERROR(compress("b"));   // One character
            EXPECT_ERROR(compress("bbb")); // One character
}








/* * * * * Provided Tests Below This Point * * * * */
#include <limits>

/* Utility function to test if a purported Huffman tree is indeed a Huffman tree.
 * Specifically, this checks that each internal node has either zero or two
 * children. There are other ways you could produce an invalid Huffman tree - for
 * example, by having uninitialized pointers or by linking in a cycle - but we
 * don't test for that here.
 */
bool isEncodingTree(EncodingTreeNode* tree) {
    /* The empty tree is not a Huffman tree. */
    if (tree == nullptr) return false;

    /* If we have one missing child, we should have two missing children. */
    if ((tree->zero == nullptr) != (tree->one == nullptr)) return false;

    /* If we have children at all, they need to be Huffman trees. */
    return tree->zero == nullptr || (isEncodingTree(tree->zero) && isEncodingTree(tree->one));
}

/* Utility function to test if two trees are equal. This is adapted from Section
 * Handout 8 and particularized to Huffman trees.
 */
bool areEqual(EncodingTreeNode* lhs, EncodingTreeNode* rhs) {
    /* Base case: If either is a leaf, both should be. */
    bool lhsLeaf = lhs->zero == nullptr && lhs->one == nullptr;
    bool rhsLeaf = rhs->zero == nullptr && rhs->one == nullptr;
    if (lhsLeaf || rhsLeaf) {
        return lhs->ch == rhs->ch && lhsLeaf == rhsLeaf;
    }

    /* Otherwise, they're both internal nodes. Check that they match. */
    return areEqual(lhs->zero, rhs->zero) && areEqual(lhs->one, rhs->one);
}

/* Utility function to return a string of all possible characters. */
string pangrammaticString() {
    string result;

    char ch = numeric_limits<char>::min();
    result += ch;
    do {
        ch++;
        result += ch;
    } while (ch != numeric_limits<char>::max());

    return result;
}

/* Utility function that makes an inefficient but still valid encoding tree
 * for the given characters.
 */
EncodingTreeNode* strandTreeFor(const string& text, size_t index = 0) {
    if (index == text.size()) error("No characters provided to strandTreeFor.");

    /* We always get a leaf node. */
    EncodingTreeNode* leaf = new EncodingTreeNode {
        text[index], nullptr, nullptr
    };

    /* Last character? If so, that's all. */
    if (index + 1 == text.size()) return leaf;

    /* Otherwise, build a larger tree. */
    else return new EncodingTreeNode {
        ' ', leaf, strandTreeFor(text, index + 1)
    };
}

PROVIDED_TEST("huffmanTreeFor reports errors on invalid inputs.") {
    EXPECT_ERROR(huffmanTreeFor(""));    // No characters
    EXPECT_ERROR(huffmanTreeFor("a"));   // One character
    EXPECT_ERROR(huffmanTreeFor("aaa")); // One character
}

PROVIDED_TEST("huffmanTreeFor builds tree for two characters.") {
    EncodingTreeNode* reference = new EncodingTreeNode {
        ' ', new EncodingTreeNode {'a', nullptr, nullptr}, new EncodingTreeNode {'b', nullptr, nullptr}
    };

    EncodingTreeNode* tree = huffmanTreeFor("aaabbbb");
    EXPECT(isEncodingTree(tree));
    EXPECT(areEqual(tree, reference));

    deleteTree(reference);
    deleteTree(tree);
}

PROVIDED_TEST("huffmanTreeFor works on the full range of characters.") {
    /* Get a string of all possible characters, then pair them off and see what we find. */
    string allChars = pangrammaticString();
    for (size_t i = 0; i < allChars.size(); i += 2) {
        string toEncode;
        toEncode += allChars[i];
        toEncode += allChars[i + 1];
        toEncode += allChars[i + 1];

        EncodingTreeNode* reference = new EncodingTreeNode {
            ' ',
            new EncodingTreeNode {allChars[i], nullptr, nullptr},
            new EncodingTreeNode {allChars[i + 1], nullptr, nullptr}
        };

        EncodingTreeNode* tree = huffmanTreeFor(toEncode);
        EXPECT(isEncodingTree(tree));
        EXPECT(areEqual(tree, reference));

        deleteTree(reference);
        deleteTree(tree);
    }
}

PROVIDED_TEST("huffmanTreeFor uses cumulative weights (v1).") {
    /* This tree:
     *                 *
     *                / \
     *               *   D
     *              / \
     *             C   *
     *                / \
     *               A   B
     */
    EncodingTreeNode* reference = new EncodingTreeNode {
        '*',
            new EncodingTreeNode { '!',
                new EncodingTreeNode { 'C', nullptr, nullptr },
                new EncodingTreeNode { '?',
                    new EncodingTreeNode { 'A', nullptr, nullptr },
                    new EncodingTreeNode { 'B', nullptr, nullptr }
                }
            },
            new EncodingTreeNode { 'D', nullptr, nullptr }
    };

    /* Ax2, Bx3, Cx4, Dx10 */
    EncodingTreeNode* tree = huffmanTreeFor("AABBBCCCCDDDDDDDDDD");
    EXPECT(isEncodingTree(tree));
    EXPECT(areEqual(tree, reference));

    deleteTree(reference);
    deleteTree(tree);
}

PROVIDED_TEST("huffmanTreeFor uses cumulative weights (v2).") {
    /*
     *          *
     *       /     \
     *      *       *
     *     / \     / \
     *    D   E   F   *
     *               / \
     *              C   *
     *                 / \
     *                A   B
     */
    EncodingTreeNode* reference =new EncodingTreeNode {
        ' ',
        new EncodingTreeNode {
            ' ',
            new EncodingTreeNode{ 'D', nullptr, nullptr },
            new EncodingTreeNode{ 'E', nullptr, nullptr }
        },
        new EncodingTreeNode {
            ' ',
            new EncodingTreeNode{ 'F', nullptr, nullptr },
            new EncodingTreeNode {
                ' ',
                new EncodingTreeNode{ 'C', nullptr, nullptr },
                new EncodingTreeNode{
                    ' ',
                    new EncodingTreeNode{ 'A', nullptr, nullptr },
                    new EncodingTreeNode{ 'B', nullptr, nullptr },
                }
            }
        }
    };

    /* Ax2, Bx3, Cx4, Dx6, Ex7, Fx8 */
    EncodingTreeNode* tree = huffmanTreeFor("AABBBCCCCDDDDDDEEEEEEEFFFFFFFF");
    EXPECT(isEncodingTree(tree));

    EXPECT(areEqual(tree, reference));

    deleteTree(reference);
    deleteTree(tree);
}

PROVIDED_TEST("decodeText works on small sample.") {
    /* This tree:
     *                 *
     *                / \
     *               O   *
     *                  / \
     *                 *   N
     *                / \
     *               M   S
     */
    EncodingTreeNode* tree = new EncodingTreeNode {
        '*',
            new EncodingTreeNode { 'O', nullptr, nullptr },
            new EncodingTreeNode { '*',
                new EncodingTreeNode{ '*',
                    new EncodingTreeNode { 'M', nullptr, nullptr },
                    new EncodingTreeNode { 'S', nullptr, nullptr }
                },
                new EncodingTreeNode{ 'N', nullptr, nullptr }
            }
    };

    /* What you get if you encode MONSOON with this tree. */
    Queue<Bit> bits = { 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1 };

    EXPECT_EQUAL(decodeText(bits, tree), "MONSOON");

    deleteTree(tree);
}

PROVIDED_TEST("Can decode all char values.") {
    /* All possible characters. */
    string allChars = pangrammaticString();

    /* Try decoding all pairs of adjacent characters. */
    for (size_t i = 0; i < allChars.size(); i += 2) {
        string expected;
        expected += allChars[i];
        expected += allChars[i + 1];
        expected += allChars[i + 1];

        EncodingTreeNode* tree = new EncodingTreeNode {
            ' ',
            new EncodingTreeNode {allChars[i], nullptr, nullptr},
            new EncodingTreeNode {allChars[i + 1], nullptr, nullptr}
        };

        /* Decode the bitstream 011, which should map back to the expected
         * string.
         */
        Queue<Bit> bits = { 0, 1, 1 };
        EXPECT_EQUAL(decodeText(bits, tree), expected);

        deleteTree(tree);
    }
}

PROVIDED_TEST("encodeText works on small sample.") {
    /* This tree:
     *                 *
     *                / \
     *               O   *
     *                  / \
     *                 *   N
     *                / \
     *               M   S
     */
    EncodingTreeNode* tree = new EncodingTreeNode {
           '*',
           new EncodingTreeNode { 'O', nullptr, nullptr },
               new EncodingTreeNode { '*',
               new EncodingTreeNode{ '*',
               new EncodingTreeNode { 'M', nullptr, nullptr },
               new EncodingTreeNode { 'S', nullptr, nullptr }
            },
            new EncodingTreeNode{ 'N', nullptr, nullptr }
        }
    };

    /* What you get if you encode MONSOON with this tree. */
    Queue<Bit> expected = { 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1 };

    EXPECT_EQUAL(encodeText("MONSOON", tree), expected);

    deleteTree(tree);
}

PROVIDED_TEST("Can encode all char values.") {
    /* All possible characters. */
    string allChars = pangrammaticString();

    /* Try encoding all pairs of adjacent characters. */
    for (size_t i = 0; i < allChars.size(); i += 2) {
        string toEncode;
        toEncode += allChars[i];
        toEncode += allChars[i + 1];
        toEncode += allChars[i + 1];

        EncodingTreeNode* tree = new EncodingTreeNode {
                ' ',
                new EncodingTreeNode {allChars[i], nullptr, nullptr},
                new EncodingTreeNode {allChars[i + 1], nullptr, nullptr}
        };

        /* See what bits we get back. We should get 011, since the first
         * character has code 0 and the second has code 1.
         */
        Queue<Bit> bits = encodeText(toEncode, tree);
        Queue<Bit> expected = { 0, 1, 1 };

        EXPECT_EQUAL(bits, expected);

        deleteTree(tree);
    }
}

PROVIDED_TEST("decodeText undoes encodeText on range of sample strings.") {
    Vector<string> testCases = {
        "THAT THAT IS IS THAT THAT IS NOT IS NOT IS THAT IT IT IS",
        "AABAAABBABAAABAAAA",
        ":-) :-D XD <(^_^)>",
        pangrammaticString(),
    };

    for (string test: testCases) {
        /* Use a silly encoding scheme, but one that works regardless of what
         * characters are provided.
         */
        EncodingTreeNode* tree = strandTreeFor(test);
        EXPECT(isEncodingTree(tree));

        Queue<Bit> bits = encodeText(test, tree);
        string result = decodeText(bits, tree);

        EXPECT_EQUAL(test.size(), result.size());
        EXPECT_EQUAL(test, result);

        deleteTree(tree);
    }
}

PROVIDED_TEST("Can decode an example tree.") {
    /* This encodes this tree:
     *
     *                 *
     *                / \
     *               *   C
     *              / \
     *             A   B
     */
    Queue<Bit>  bits   = { 1, 1, 0, 0, 0 };
    Queue<char> leaves = { 'A', 'B', 'C' };

    EncodingTreeNode* tree = decodeTree(bits, leaves);
    EXPECT(isEncodingTree(tree));

    /* Confirm this is the right tree. */
    EncodingTreeNode* expected = new EncodingTreeNode {
        '*',
            new EncodingTreeNode {
                '*',
                new EncodingTreeNode { 'A', nullptr, nullptr },
                new EncodingTreeNode { 'B', nullptr, nullptr },
            },
            new EncodingTreeNode { 'C', nullptr, nullptr }
    };

    EXPECT(areEqual(tree, expected));

    deleteTree(tree);
    deleteTree(expected);
}

PROVIDED_TEST("Can decode trees using all possible char values.") {
    /* All possible characters. */
    string allChars = pangrammaticString();

    /* Try encoding all pairs of adjacent characters. */
    for (size_t i = 0; i < allChars.size(); i += 2) {
        EncodingTreeNode* expected = new EncodingTreeNode {
            ' ',
            new EncodingTreeNode {allChars[i], nullptr, nullptr},
            new EncodingTreeNode {allChars[i + 1], nullptr, nullptr}
        };
        Queue<Bit>  treeBits   = { 1, 0, 0 };
        Queue<char> treeLeaves = { allChars[i], allChars[i + 1] };

        EncodingTreeNode* tree = decodeTree(treeBits, treeLeaves);
        EXPECT(isEncodingTree(tree));
        EXPECT(areEqual(tree, expected));

        deleteTree(tree);
        deleteTree(expected);
    }
}

PROVIDED_TEST("Can encode an example tree.") {
    /* Build an encoding tree for "ABBCCCC." It should look like this:
     *
     *                 *
     *                / \
     *               *   C
     *              / \
     *             A   B
     *
     * This will compress down to
     *
     *        11000
     *        ABC
     */
    EncodingTreeNode* tree = huffmanTreeFor("ABBCCCC");

    Queue<Bit>  bits;
    Queue<char> leaves;

    encodeTree(tree, bits, leaves);

    Queue<Bit>  expectedBits   = { 1, 1, 0, 0, 0 };
    Queue<char> expectedLeaves = { 'A', 'B', 'C' };

    EXPECT_EQUAL(bits,   expectedBits);
    EXPECT_EQUAL(leaves, expectedLeaves);

    deleteTree(tree);
}

PROVIDED_TEST("Can encode trees using all possible char values.") {
    /* All possible characters. */
    string allChars = pangrammaticString();

    /* Try encoding all pairs of adjacent characters. */
    for (size_t i = 0; i < allChars.size(); i += 2) {
        EncodingTreeNode* tree = new EncodingTreeNode {
            ' ',
            new EncodingTreeNode {allChars[i], nullptr, nullptr},
            new EncodingTreeNode {allChars[i + 1], nullptr, nullptr}
        };

        /* See what we get back. It should be the bitstring 100 (root with
         * two children) and the two leaves, in order.
         */
        Queue<Bit>  treeBits;
        Queue<char> treeLeaves;

        Queue<Bit>  expectedBits = { 1, 0, 0 };
        Queue<char> expectedLeaves = { allChars[i], allChars[i + 1] };

        encodeTree(tree, treeBits, treeLeaves);
        EXPECT_EQUAL(treeBits, expectedBits);
        EXPECT_EQUAL(treeLeaves, expectedLeaves);

        deleteTree(tree);
    }
}

PROVIDED_TEST("decodeTree undoes encodeTree on sample strings.") {
    /* Make a Huffman tree for the string of all characters. */
    EncodingTreeNode* sourceTree = huffmanTreeFor(pangrammaticString());
    EXPECT(isEncodingTree(sourceTree));

    /* Encode, then decode it. */
    Queue<Bit>  bits;
    Queue<char> leaves;
    encodeTree(sourceTree, bits, leaves);

    EncodingTreeNode* resultTree = decodeTree(bits, leaves);
    EXPECT(isEncodingTree(resultTree));
    EXPECT(areEqual(sourceTree, resultTree));

    deleteTree(sourceTree);
    deleteTree(resultTree);
}

PROVIDED_TEST("Can decompress a small sample file.") {
    HuffmanResult file = {
        { 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0 },
        { 'u', 'k', 'p', 'n', 'a', 'm', 'h' },
        { 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1,
          0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0,
          0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0 }
    };

    EXPECT_EQUAL(decompress(file), "humuhumunukunukuapuaa");
}

PROVIDED_TEST("Compress reports errors on bad inputs.") {
    EXPECT_ERROR(compress(""));
    EXPECT_ERROR(compress("A"));
    EXPECT_ERROR(compress("AAAA"));
}

PROVIDED_TEST("Can compress a small sample file.") {
    HuffmanResult file = compress("ABANANAABANDANA");
    Queue<Bit>  treeBits    = { 1, 1, 1, 0, 0, 0, 0 };
    Queue<char> treeChars   = { 'D', 'B', 'N', 'A' };
    Queue<Bit>  messageBits = { 1, 0, 0, 1, 1, 0, 1, 1, 0,
                                1, 1, 1, 0, 0, 1, 1, 0, 1,
                                0, 0, 0, 1, 0, 1, 1 };

    EXPECT_EQUAL(file.treeBits, treeBits);
    EXPECT_EQUAL(file.treeLeaves, treeChars);
    EXPECT_EQUAL(file.messageBits, messageBits);
}

PROVIDED_TEST("Compress undoes decompress on a range of strings.") {
    Vector<string> testCases = {
        "THAT THAT IS IS THAT THAT IS NOT IS NOT IS THAT IT IT IS",
        "AABAAABBABAAABAAAA",
        ":-) :-D XD <(^_^)>",
        pangrammaticString(),
    };

    for (string test: testCases) {
        HuffmanResult file = compress(test);
        string result = decompress(file);

        EXPECT_EQUAL(result.size(), test.size());
        EXPECT_EQUAL(test, result);
    }
}
