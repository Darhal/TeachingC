#include "tree.h"

tree create()
{
    tree t = { NULL }; // arbre vide
    return t;
}

#if !defined(AVL)

tree insert(tree t, int val)
{
    // arbre vide
    if (!t.root) { // t.root == NULL
        t.root = malloc(sizeof(node));
        t.root->val = val;
        t.root->left = NULL;
        t.root->right = NULL;
        t.root->parent = NULL;
        return t;
    }

    node* n = t.root;
    while (n) { // n != NULL
        node* prev = n;

        if (n->val > val){
            n = n->left;
            if (!n) // n == null
                insert_left(prev, val); // insert à gauche
        }else{
            n = n->right;
            if (!n) // n == null
                insert_right(prev, val); // insert à droite
        }
    }

    return t;
}

#endif

void insert_left(node* n, int val)
{
    n->left = malloc(sizeof(node));
    n->left->val = val;
    n->left->parent = n;
    n->left->left = NULL;
    n->left->right = NULL;
}

void insert_right(node* n, int val)
{
    n->right = malloc(sizeof(node));
    n->right->val = val;
    n->right->parent = n;
    n->right->left = NULL;
    n->right->right = NULL;
}

int height(node* t)
{
    if (t)
        return MAX(height(t->right), height(t->left)) + 1;
    return 0;
}

void print_order(node* t)
{
    if (!t)
        return;
    
    print_order(t->left);
    printf("%d ", t->val);
    print_order(t->right);
}

int find_min(node* t)
{
    if (t) {
        if (t->left) {
            return find_min(t->left);
        }

        return t->val;
    }

    return INT32_MAX;
}

int find_max(node* t)
{
    if (t) {
        if (t->right) {
            return find_max(t->right);
        }

        return t->val;
    }

    return INT32_MIN;
}

int find_succ(node* t)
{
    if (!t)
        return INT32_MAX;
    
    if (t->right)
        return find_min(t->right);
    
    node* p = t->parent;

    while (p && t == p->right) {
        t = p;
        p = p->parent;
    }

    if (p)
        return p->val;
    
    return INT32_MAX;
}

int count_nodes(node* t)
{
    if (!t)
        return 0;
    return count_nodes(t->left) + count_nodes(t->right) + 1;    
}

int sum(node* t)
{
    if (!t)
        return 0;
    return sum(t->left) + sum(t->right) + t->val; 
}

void free_tree(node* t)
{
    if (t) {
        free_tree(t->left);
        free_tree(t->right);
        free(t);
    }
}
