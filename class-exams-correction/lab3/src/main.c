#include "tree.h"

int main()
{
    tree t = create();

    t = insert(t, 2);
    t = insert(t, 3);
    t = insert(t, 4);

    printf("min: %d\n", find_min(t.root));
    printf("max: %d\n", find_max(t.root));
    printf("count nodes: %d\n", count_nodes(t.root));
    printf("sum: %d\n", sum(t.root));
    printf("hauteur: %d\n", height(t.root));

    printf("Order : "); print_order(t.root); printf("\n");
    
    printf("succ de root (2): %d\n", find_succ(t.root));
    printf("succ de (3): %d\n", find_succ(t.root->right));
    printf("succ de (4): %d\n", find_succ(t.root->right->right));

    free_tree(t.root);
}