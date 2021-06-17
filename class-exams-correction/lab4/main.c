#include "graph.h"

void graph_bfs_print(gmat* graph, int src)
{
    int* nodes = graph_bfs_itr(graph, src);
    printf("BFS from %d : ", src);

    for (int i = 0; i < graph->n; i++) {
        printf("%d %c", nodes[i], " \n"[i == graph->n - 1]);
    }

    free(nodes);
}


void graph_dfs_print(gmat* graph, int src)
{
    int* nodes = graph_dfs(graph, src);
    printf("DFS from %d : ", src);

    for (int i = 0; i < graph->n; i++) {
        printf("%d %c", nodes[i], " \n"[i == graph->n - 1]);
    }

    free(nodes);
}

void graph_print_path(const gmat* graph, int src, int dst)
{
    vector paths = graph_dfs_paths(graph, src, dst);
    printf("Paths from %d to %d ", src, dst);

    if (!vec_size(&paths)){
        printf(": No path was found\n");
    }else{
        printf(" :\n");
    }

    for (size_t j = 0; j < vec_size(&paths); j++) {
        path* p = vec_get(&paths, j);
        printf("\t* (cost:%d) : ", p->cost);

        for (size_t i = 0; i < vec_size(&p->path); i++){
            printf("%d %c", *(int*)vec_get(&p->path, i), " \n"[i == vec_size(&p->path) - 1]);
        }

        vec_destroy(&p->path);
    }

    for (size_t j = 0; j < vec_size(&paths); j++) {
        path* p = vec_get(&paths, j);
        vec_destroy(&p->path);
    }

    vec_destroy(&paths);
}

void graph_print_shortest_path(const gmat* graph, int src, int dst)
{
    vector paths = graph_dfs_paths_shortest(graph, src, dst);
    printf("Shortest Paths from %d to %d ", src, dst);

    if (!vec_size(&paths)){
        printf(": No path was found\n");
    }else{
        printf(" :\n");
    }

    for (size_t j = 0; j < vec_size(&paths); j++) {
        path* p = vec_get(&paths, j);
        printf("\t* (cost:%d) : ", p->cost);

        for (size_t i = 0; i < vec_size(&p->path); i++){
            printf("%d %c", *(int*)vec_get(&p->path, i), " \n"[i == vec_size(&p->path) - 1]);
        }

        vec_destroy(&p->path);
    }

    for (size_t j = 0; j < vec_size(&paths); j++) {
        path* p = vec_get(&paths, j);
        vec_destroy(&p->path);
    }

    vec_destroy(&paths);
}


int main()
{
    gmat g = graph_init(5);
    graph_bin_rand(&g, 0.3);
    graph_print_mat(&g);

    graph_bfs_print(&g, 0);
    graph_dfs_print(&g, 0);
    graph_print_path(&g, 0, 4);
    graph_print_shortest_path(&g, 0, 4);

    int node = 3;
    double betweenness = graph_betweeness_centrality(&g, node);
    printf("Betweenness centrality of %d is : %lf\n", node, betweenness);

    node = graph_get_highest_betweeness_centrality_node(&g);
    if (node != -1){
        betweenness = graph_betweeness_centrality(&g, node);
        printf("The node that have a maximum betweeness centrality is node '%d' with a score = %lf\n", node, betweenness);
    }else{
        printf("A node with a highest betweeness centraliy doesn't exist in this graph. \n");
    }

    graph_free(&g);
    return 0;
}
