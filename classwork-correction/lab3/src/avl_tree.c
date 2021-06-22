#include "tree.h"

#if defined(AVL)

static node* insert_rec(node* currentNode, int val)
{
    // sous-arbre vide
    if (!currentNode) {
        currentNode = malloc(sizeof(node));
        currentNode->val = val;
        currentNode->left = NULL;
        currentNode->right = NULL;
        currentNode->parent = NULL;
        return currentNode;
    }

    if (val < currentNode->val) {
        node* nt = insert_rec(currentNode->left, val);
        currentNode->left = nt;
    }else {
        node* nt = insert_rec(currentNode->right, val);
        currentNode->right = nt;
    }

    int b = bf(currentNode);

    if (b > 1 && val < currentNode->left->val) {
        return rotate_right(currentNode);
    }

    if (b < -1 && val > currentNode->right->val) {
        return rotate_left(currentNode);
    }

    if (b > 1 && val > currentNode->left->val) {
        currentNode->left = rotate_left(currentNode->left);
        return rotate_right(currentNode);
    }

    if (b < -1 && val < currentNode->right->val) {
        currentNode->right = rotate_right(currentNode->right);
        return rotate_left(currentNode);
    }

    return currentNode;
}

tree insert(tree t, int val)
{
    tree nt = { insert_rec(t.root, val) };
    return nt;
}

int bf(node* t)
{
    if (!t)
        return 0;
    return height(t->left) - height(t->right);
}

node* rotate_left(node* t)
{
    if (!t)
        return NULL;
        
    node* z = t->right;
    t->right = z->left;

    if (z->left)
        z->left->parent = t;
    
    z->left = t;
    t->parent = z;
    return z;
}

node* rotate_right(node* t)
{
    if (!t)
        return NULL;
        
    node* z = t->left;
    t->left = z->right;

    if (z->right)
        z->right->parent = t;
    
    z->right = t;
    t->parent = z;
    return z;
}

#endif