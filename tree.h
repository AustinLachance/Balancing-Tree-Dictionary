// tree.h                                     Austin Lachance (2016/04/05)
//
// Define the abstract data type for a 2016 tree


#include <stdbool.h>

// External definition of Tree
typedef struct tnode *Tree;

// Datatype for Key
typedef char *Key;

// Set *T to the empty tree.  Return TRUE if successful, else FALSE.
bool create (Tree *t);

// Search for Key K in Tree *T and insert K in *T if not found.  Return
// TRUE if successful, else FALSE.  Set *T to root of updated tree.
bool searchInsert (Tree *t, Key k);

// Delete Key K from Tree *T.  Return TRUE if successful, else FALSE.  Set
// *T to root of updated tree.
bool delete (Tree *t, Key k);

// Perform an inorder traversal of Tree T, printing one Key per line.
void inorder (Tree t);

// Perform a preorder traversal of Tree T, printing one Key per line.
void preorder (Tree t);

// Change the value of the Improvement Factor
void change_IF(int new_IF);

// Prints the sum of all leaf weights and the wepl of the tree
void epl(Tree t);

