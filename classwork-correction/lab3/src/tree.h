#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define MAX(a, b)               \
    (((a) > (b)) ? (a) : (b))   \

typedef struct _node node;
struct _node
{
    node* left;
    node* right;
    node* parent;
    int val;
};

typedef struct tree_t
{
    node* root;
} tree;

tree create();

tree insert(tree t, int val);

void insert_left(node* n, int val);

void insert_right(node* n, int val);

int height(node* t);

void print_order(node* t);

int find_min(node* t);

int find_max(node* t);

int find_succ(node* t);

int count_nodes(node* t);

int sum(node* t);

void free_tree(node* t);

#if defined(AVL)
    int bf(node* t);

    node* rotate_left(node* t);

    node* rotate_right(node* t);
#endif