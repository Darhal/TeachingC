#include "graph.h"
#include <stdint.h>
#include <math.h>

gmat graph_init(int N)
{
    gmat g;
    g.n = N;
    g.mat = (int**)malloc(N * sizeof(int*));
    int* mem = calloc(N * N, sizeof(int));

    for (int i = 0; i < N; i++) {
        g.mat[i] = mem + i * N;
    }

    return g;
}

void graph_free(gmat* g)
{
    free(g->mat[0]);
    free(g->mat);
}

void graph_set_edge(gmat* g, int src, int dst, int val)
{
    g->mat[src][dst] = val;
}

void graph_print_mat(const gmat* g)
{
    printf("\t");

    for (int i = 0; i < g->n; i++) {
        printf("%d\t", i);
    }

    printf("\n");
    for (int i = 0; i < g->n; i++) {
        printf("%d\t", i);

        for (int j = 0; j < g->n; j++) {
            printf("%d\t", g->mat[i][j]);
        }

        printf("\n");
    }
}

static int prob_bool(double proba)
{
    int r = rand();
    int l = proba * ((double)RAND_MAX + 1.0);
    return r < l;
}

void graph_bin_rand(gmat* g, double p)
{
    srand(time(NULL));

    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            if (i == j)
                continue; // we forbid self loops
            
            if (prob_bool(p)) {
                // Undirected graph
                graph_set_edge(g, i, j, 1);
                graph_set_edge(g, j, i, 1);
            }
        }
    }
}

int* graph_bfs_itr(const gmat* g, int src)
{
    // breadth first seach
    int* result = malloc(sizeof(int) * g->n);
    int* toVisist = malloc(sizeof(int) * g->n * g->n);
    int* isVisited = calloc(g->n, sizeof(int));
    int resultCount = 0;
    int toVisistCount = 0;
    toVisist[toVisistCount++] = src;

    while (resultCount != g->n) {
        if (!toVisistCount) { // Traiter les graphes non-connexe
            for (int i = 0; i < g->n; i++){
                if (!isVisited[i]) {
                    toVisist[toVisistCount++] = i;
                    break;
                }
            }
        }

        int currentNode = toVisist[0];
        for (int i = toVisistCount - 1; i > 0; i--){
            toVisist[i - 1] = toVisist[i];
        }
        toVisistCount--;
        if (isVisited[currentNode])
            continue;
        isVisited[currentNode] = 1; // Colorer le sommet en rouge
        result[resultCount++] = currentNode;

        for (int i = 0; i < g->n; i++){
            if (i != currentNode && g->mat[currentNode][i] && !isVisited[i]) {
                toVisist[toVisistCount++] = i;
            }
        }
    }

    free(toVisist);
    free(isVisited);
    return result;
}

void graph_dfs_rec(const gmat* g, int current, int* count, int* result, int* isVisited)
{
    isVisited[current] = 1;
    result[*count] = current;
    *count = (*count) + 1;

    for (int i = 0; i < g->n; i++){
        if (i != current && g->mat[current][i] && !isVisited[i]) {
            graph_dfs_rec(g, i, count, result, isVisited);
        }
    }
}

int* graph_dfs(const gmat* g, int src)
{
    int* result = malloc(sizeof(int) * g->n);
    int* isVisited = calloc(g->n, sizeof(int));
    int count = 0;
    graph_dfs_rec(g, src, &count, result, isVisited);

    for (int i = 0; i < g->n; i++){
        if (!isVisited[i]) {
            graph_dfs_rec(g, i, &count, result, isVisited);
        }
    }

    free(isVisited);
    return result;
}

vector graph_dfs_paths(const gmat* g, int src, int dst)
{
    vector availablePaths = vec_init2(sizeof(path));
    vector pathQueue = vec_init2(sizeof(path));

    path initialPath;
    initialPath.cost = 0;
    initialPath.path = vec_init2(sizeof(int));

    vec_push_back(&initialPath.path, &src);
    vec_push_back(&pathQueue, &initialPath);

    while (vec_size(&pathQueue)) {
        path* last = vec_back(&pathQueue);
        path lastPath = *last;
        lastPath.path = last->path;
        vec_pop_back(&pathQueue);

        // Dernier sommet d'arrivé
        int lastPoint = *(int*)vec_back(&lastPath.path);

        if (lastPoint == dst) {
            path correctPath;
            correctPath.path = vec_copy(&lastPath.path);
            correctPath.cost = lastPath.cost;
            vec_push_back(&availablePaths, &correctPath);
        }

        for (int i = 0; i < g->n; i++) {
            if (g->mat[lastPoint][i] && !vec_find(&lastPath.path, &i))  {
                path newPath;
                newPath.path = vec_copy(&lastPath.path);
                newPath.cost = lastPath.cost + g->mat[lastPoint][i];
                vec_push_back(&newPath.path, &i);

                vec_push_front(&pathQueue, &newPath);
            }
        }

        vec_destroy(&lastPath.path);
    }

    vec_destroy(&pathQueue);
    return availablePaths;
}

vector graph_dfs_paths_shortest(const gmat* g, int src, int dst)
{
    vector paths = graph_dfs_paths(g, src, dst);
    vector shortestPaths = vec_init2(sizeof(path));
    int minScore = INT32_MAX;

    for (size_t i = 0; i < vec_size(&paths); i++){
        path* p = (path*)vec_get(&paths, i);
        minScore = MIN(minScore, p->cost);
    }

    for (size_t i = 0; i < vec_size(&paths); i++) {
        path* p = (path*)vec_get(&paths, i);
        
        if (p->cost == minScore) {
            vec_push_back(&shortestPaths, p);
        }else{
            vec_destroy(&p->path);
        }
    }

    vec_destroy(&paths);
    return shortestPaths;
}

int graph_count_paths_that_pass_by(const vector* paths, int v)
{
    int count = 0;

    for (int k = 0; k < vec_size(paths); k++){
        path* p = (path*)vec_get(paths, k);

        for (int l = 0; l < vec_size(&p->path); l++){
            if (*(int*)vec_get(&p->path, l) == v) {
                count++;
                break;
            }
        }
    }

    return count;
}

double graph_betweeness_centrality(const gmat* g, int v)
{
    double score = 0.0;

    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            if (i == j || v == i || v == j)
                continue;
            
            vector shortest = graph_dfs_paths_shortest(g, i, j);

            if (vec_size(&shortest)) {
                int count = graph_count_paths_that_pass_by(&shortest, v);
                score += (double)(count) / (double)(vec_size(&shortest));
            }

            for (int k = 0; k < vec_size(&shortest); k++){
                path* p = (path*)vec_get(&shortest, k);
                vec_destroy(&p->path);
            }

            vec_destroy(&shortest);
        }
    }

    return score;
}

int graph_get_highest_betweeness_centrality_node(const gmat* g)
{
    double maxScore = -INFINITY;
    int node = -1;

    for (int i = 0; i < g->n; i++) {
        double score = graph_betweeness_centrality(g, i);
        if (score > maxScore) {
            maxScore = score;
            node = i;
        }
    }

    return node;
}