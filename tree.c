/****************************************************************
Name: Austin Lachance
Email: austin.lachance@yale.edu

CPSC223
Implemenation of a "2016" weight balanacing tree
****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

//Improvement Factor. Based on this number rotations will or will not occur
static int IF = 0;
int count = 0;

//Preform a Right or Left Rotation on Tree t
static void rotateRight(Tree *t);
static void rotateLeft(Tree *t);

//alter the value of the static global IF
void change_IF(int new_IF) {
	IF = new_IF;
}

struct tnode {
    Key key;						
    int weight;						
    int wepl;
    Tree left, right;
}tnode;


// Set *T to the empty tree.  Return TRUE if successful, else FALSE.
bool create (Tree *t)
{
    *t = NULL;
    return true;
}

// Set *T to a one-node tree containing Key K. 
static bool makeNode (Tree *t, Key k)
{
		char* copy = malloc(strlen(k) + 1);
    	strcpy(copy, k);
    	*t = malloc(sizeof(tnode));
    	(*t)->key = copy;
    	(*t)->weight = 1;
    	(*t)->wepl = 0;
    	(*t)->left = NULL; 
    	(*t)->right = NULL;
    	return true;
}

// Search for Key K in Tree *T and insert K in *T if not found.  Set *T to
// root of updated tree.  Return TRUE if successful, else FALSE.
bool searchInsert (Tree *t, Key k)
{
	//Is the tree empty? If so make node
    if (*t == NULL) {
    	return makeNode (t, k);
    }
    //insert in the left branch
    else if (strcmp (k, (*t)->key) < 0) {
    	if((*t)->left == NULL) {
    		Tree old_t;
    		old_t = *t;
    		makeNode(t, k);

    		Tree temp;
    		makeNode(&temp, k);

    		(*t)->left = temp;
    		(*t)->right = old_t;
    		(*t)->weight = ((*t)->left)->weight + ((*t)->right)->weight;
    		(*t)->wepl = ((*t)->left)->wepl + ((*t)->right)->wepl\
             + (*t)->weight;
    		return true;
    	}
    	searchInsert (&(*t)->left, k);
    	(*t)->weight = ((*t)->left)->weight + ((*t)->right)->weight;
    	(*t)->wepl = ((*t)->left)->wepl + ((*t)->right)->wepl + (*t)->weight;

    	//check if rotation is needed
    	Tree LEFT = (*t)->left;
    	Tree RIGHT = (*t)->right;
    	Tree LEFT_LEFT = LEFT->left;
    	if(LEFT != NULL) {
    		if(LEFT_LEFT != NULL) {
    			if((LEFT_LEFT->weight - RIGHT->weight) > IF) {
    				rotateRight(t);
    			}
    		}
    	}
		return false;     	
    }
    //insert in the right branch
    else if (strcmp (k, (*t)->key) > 0) {
    	
    	if((*t)->right == NULL) {

    		Tree temp;
    		makeNode(&temp, k);
    		(*t)->right = temp;
 
    		makeNode(&temp, (*t)->key);
    		temp->weight = (*t)->weight;
    		(*t)->left = temp;
    		(*t)->weight = ((*t)->left)->weight + ((*t)->right)->weight;
    		(*t)->wepl = ((*t)->left)->wepl + ((*t)->right)->wepl\
             + (*t)->weight;
    		return true;
    	}
    	searchInsert (&(*t)->right, k);
    	(*t)->weight = ((*t)->left)->weight + ((*t)->right)->weight;
    	(*t)->wepl = ((*t)->left)->wepl + ((*t)->right)->wepl + (*t)->weight;

    	//Check if rotation is needed
    	Tree LEFT = (*t)->left;
    	Tree RIGHT = (*t)->right;
    	Tree RIGHT_RIGHT = RIGHT->right;
    	if(RIGHT != NULL) {
    		if(RIGHT_RIGHT != NULL) {
    			if((RIGHT_RIGHT->weight - LEFT->weight) > IF) {
    				rotateLeft(t);
    			}
    		}
    	}
    	return false;
    }
 	//Node already exists. Increase weight of leaf with cooresponding key
    else if (strcmp (k, (*t)->key) == 0) {
    	if((*t)->left == NULL) {
    		(*t)->weight++;
    		return false;
    	}
    	else {
    		searchInsert (&(*t)->left, k);
    		(*t)->weight = ((*t)->left)->weight + ((*t)->right)->weight;
    		(*t)->wepl = ((*t)->left)->wepl + ((*t)->right)->wepl\
             + (*t)->weight;

    		//Check if rotation is needed
	    	if((*t)->left != NULL) {
	    		if(((*t)->left)->left != NULL) {
	    			if(((((*t)->left)->left)->weight\
                     - ((*t)->right)->weight) > IF) {
	    				rotateRight(t);
	    			}
	    		}
	    	}
    		return false; 
    	}
    }
    return false;
}

//Perform a Right Rotation
static void rotateRight(Tree *t) {

	Tree new_right = *t;
	Tree old_left = (*t)->left;
	*t = old_left;
	new_right->left = old_left->right;
	(*t)->right = new_right;

	//Calculate WEIGHT and WEPL of the new RIGHT tree
	((*t)->right)->weight = (((*t)->right)->left)->weight
	 + (((*t)->right)->right)->weight;

	((*t)->right)->wepl = (((*t)->right)->left)->wepl
	 + (((*t)->right)->right)->wepl + ((*t)->right)->weight;

	//Calculate WEIGHT and WEPL of the new ROOT tree
	(*t)->weight = ((*t)->left)->weight + ((*t)->right)->weight;
	(*t)->wepl = ((*t)->left)->wepl + ((*t)->right)->wepl + (*t)->weight;
}

//Perform a Left Rotation 
static void rotateLeft(Tree *t) {
	Tree new_left = *t;
	Tree old_right = (*t)->right;
	*t = old_right;
	new_left->right = old_right->left;
	(*t)->left = new_left;

	//Calculate WEIGHT and WEPL of the new LEFT tree
	((*t)->left)->weight = (((*t)->left)->left)->weight
	 + (((*t)->left)->right)->weight;

	((*t)->left)->wepl = (((*t)->left)->left)->wepl
	 + (((*t)->left)->right)->wepl + ((*t)->left)->weight;

	//Calculate WEIGHT and WEPL of the new ROOT tree
	(*t)->weight = ((*t)->left)->weight + ((*t)->right)->weight;
	(*t)->wepl = ((*t)->left)->wepl + ((*t)->right)->wepl + (*t)->weight;
}


// Delete Key K from Tree *T and set *T to root of updated tree.  Return
// TRUE if successful, FALSE otherwise.
bool delete (Tree *t, Key k)
{
    if (*t == NULL) {
    	return false;
    }
    else if(((*t)->left == NULL) && (strcmp((*t)->key, k) == 0))  {
      	free((*t)->key);
    	free(*t);
    	*t = NULL;
    	return true;
    }
    else if (strcmp (k, (*t)->key) <= 0) {
    	if((*t)->left == NULL) {
    		return false;
    	}

     	if(delete (&(*t)->left, k)) {
    		Tree freethis = *t;
    		*t = (*t)->right;
     		free(freethis->key);
    		free(freethis);
    		return false;
    	}
    	else {

    		(*t)->weight = ((*t)->left)->weight + ((*t)->right)->weight;
    		(*t)->wepl = ((*t)->left)->wepl + ((*t)->right)->wepl\
             + (*t)->weight;

    		if((*t)->right != NULL) {
	    		if(((*t)->right)->right != NULL) {
	    			if(((((*t)->right)->right)->weight\
                     - ((*t)->left)->weight) > IF) {
	    				rotateLeft(t);
	    				count++;
	    			}
	    		}
	    	}
    	}
    	return false;

    }
    else if (strcmp ((*t)->key, k) < 0) {
    	if((*t)->left == NULL) {
    		return false;
    	}
    	if(delete (&(*t)->right, k)) {
     		Tree freethis = *t;
    		*t = (*t)->left;
    		free(freethis->key);
    		free(freethis);
    		return false;
    	}
    	else {

    		(*t)->weight = ((*t)->left)->weight + ((*t)->right)->weight;
    		(*t)->wepl = ((*t)->left)->wepl + ((*t)->right)->wepl\
             + (*t)->weight;

    		if((*t)->left != NULL) {
	    		if(((*t)->left)->left != NULL) {
	    			if(((((*t)->left)->left)->weight\
                     - ((*t)->right)->weight) > IF) {
	    				rotateRight(t);
	    				count++;
	    			}
	    		}
	    	}
		}
    	return false;
    }
    else {

		return false;
    }
    return false;
}


// Perform an inorder traversal of Tree T, printing one Key per line.
void inorder (Tree t) {
    if(t == NULL) {
    	return;
    }
    inorder(t->left);
    if(t->left == NULL) {
    	printf("%3d %s\n", t->weight, t->key);
    	return;
	}
    inorder(t->right);
}


// Perform a preorder traversal of Tree T, printing one Key per line.
void preorder (Tree t) {	
    if(t == NULL) {
    	return;
    }
	printf("%s\n", t->key);
	preorder(t->left);
	preorder(t->right);
	return;
}

//Calculates the total weight of the leaves of the tree
static int leaf_weight(Tree t) {
	int sum_weights = 0;
	if(t->left == NULL) {`
		sum_weights += t->weight;
		return sum_weights;
	}
	sum_weights += leaf_weight(t->left);
	sum_weights += leaf_weight(t->right);
	return sum_weights;
}

//Prints the total leaf weight of tree and the tree epl
void epl(Tree t) {
	if(t == NULL) {
		printf("0, 0\n");
	}
	else {
		printf("%d, %d\n", t->weight, t->wepl);
	}
	
}

