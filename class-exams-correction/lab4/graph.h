#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "vector.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct gmat_t
{
    int** mat;  // matrice d'adjacence
    int n;      // nb de sommet
} gmat;

typedef struct path_t
{
    vector path;
    int    cost;
} path;


gmat graph_init(int N);

void graph_free(gmat* g);

void graph_set_edge(gmat* g, int src, int dst, int val);

void graph_print_mat(const gmat* g);

void graph_bin_rand(gmat* g, double p);

int* graph_bfs_itr(const gmat* g, int src);

void graph_dfs_rec(const gmat* g, int current, int* count, int* result, int* isVisited);

int* graph_dfs(const gmat* g, int src);

vector graph_dfs_paths(const gmat* g, int src, int dst);

vector graph_dfs_paths_shortest(const gmat* g, int src, int dst);

int graph_count_paths_that_pass_by(const vector* paths, int v);

double graph_betweeness_centrality(const gmat* g, int v);

int graph_get_highest_betweeness_centrality_node(const gmat* g);
