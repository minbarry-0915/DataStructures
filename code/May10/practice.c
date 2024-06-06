#include <stdlib.h>
#include <stdio.h>
#include "bintree.h"

bintree_t * 
bintree_create (char data) 
{
	node_t* root;
    root = (node_t*)malloc(sizeof(node_t));
    root->data = data;
    root->left = NULL;
    root->right = NULL;
    return root;
}

bintree_t *
bintree_add_left (bintree_t * parent, bintree_t * child)
{
	parent->left = child ;
}

bintree_t *
bintree_add_right (bintree_t * parent, bintree_t * child)
{
	parent->right = child ;
}

bintree_t *
bintree_search (bintree_t * t, char key)
{
    if(t->data == key)
        return t;

    bintree_t* r;
	r = bintree_search(t->left, key);
    if(r != NULL)
        return r;
    r = bintree_search(t->right, key);
    if(r != NULL)
        return r;

    return NULL;
}

int
bintree_is_ancestor (bintree_t * t1 /*parent*/, bintree_t * t2/*child*/)
{
	if(t1->left == t2 || t1->right == t2)
        return 1;

    if(t1->left != NULL){
        if(bintree_is_ancestor(t1->left, t2))
            return 1;
    }
    if(t2->right != NULL){
        if(bintree_is_ancestor(t1->right, t2))
            return 1;
    }
    return 0;
}

void
bintree_delete (bintree_t * t)
{
    if(t->left)
        bintree_delete(t->left);
    if(t->right)
        bintree_delete(t->right);
    free(t);
}


int
bintree_height(bintree_t * t) 
{	
	int max_height = 0;

    if(t->left){
        int height = bintree_height(t->left);
        if(height > max_height)
            max_height = height;
    }
    if(t->right){
        int height = bintree_height(t->right);
        if(height > max_height)
            max_height = height;
    }

    return max_height + 1;
}


void
bintree_print (bintree_t * t)
// L V R
{
    printf("(");
    if(t->left)
        bintree_print(t->left);
    printf(",");
    printf("%c", t->data);
    printf(",");
    if(t->right)
        bintree_print(t->right);
    printf(")");


}