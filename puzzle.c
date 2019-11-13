/**
 * @file puzzle.c
 * @author Luiz Eduardo Cartolano - 183012
 * @date 9 Nov 2019
 * @brief File containing the function to solve project 2 of the MC558 subject.
 *
 * Given a related graph. To move from area x to area y, and vice versa, a guinea 
 * pig must solve a difficulty puzzle w (x, y). The goal of guinea pigs is to get 
 * out of your home area s and reach another area t. As higher difficulty levels 
 * imply a higher risk of neurointoxication, guinea pigs will try to traverse the 
 * graph in order to avoid more difficult puzzles, ie, among all paths from s to t, 
 * they will choose the one that minimizes the maximum difficulty puzzle along the way.
 * @see https://susy.ic.unicamp.br:9999/mc558a/02/enunc.html
 */

/**
 *include default C libraries 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

/**
 * @brief edge structure
 *
 * Struct that aims to store usefull information about the graph edges,
 * like, where the edge start, where it ends and how much it weight.
 */
struct Edge  { 
    /* start vertex */
    int u;
    /* end vertex */      
    int v;
    /* vertex weight */
    int weight; 
};

/**
 * utility function to find in which set the vertex is contained
 * 
 * @code
 *     parent --> vector of sets
 *     find_set(parent, 0)
 * @endcode
 *
 * @param int[] parent
 * @param int index
 *
 * @return index of the parent
 */
int find_set(int parent[], int index) { 
    if (parent[index] == -1) 
        return index; 
    
    return find_set(parent, parent[index]); 
}

/**
 * A utility function to do union of two subsets
 * 
 * @code
 *     parent --> vector of sets
 *     union_set(parent, 0, 1)
 * @endcode
 *
 * @param int[] parent
 * @param int x
 * @param int y
 *
 * @return nothing
 */
void union_set(int parent[], int x, int y) { 
    if(find_set(parent, x) != find_set(parent, y))
       parent[find_set(parent, x)] = find_set(parent, y); 
} 

/**
 * Function that choose the one edge that minimizes the maximum difficulty 
 * puzzle along the way
 * 
 * @code
 *     union_set(edges, 5, 0, 2)
 * @endcode
 *
 * @param struct Edge* edge
 * @param int num_vertices
 * @param int u
 * @param int v
 *
 * @return weight of the edge that minimize the max edge
 */
int minMaxEdge(struct Edge* edge, int num_vertices, int u, int v) {

    /* Allocate memory for creating V subsets */
    int *parent = (int*) malloc(num_vertices * sizeof(int));
    /* declare the edge counter as zero */
    int i_edge = 0;
    /* initialize counter for edge weight */ 
    int max_edge = 0;
    /* auxiliar var */
    int i, x, y;
    
    /* Initialize all subsets as single element sets */
    for (i = 0; i < num_vertices; i++) {
        parent[i] = -1;
    }
    /* while both nodes aren't on the same set we keep adding edges */
    while (find_set(parent, u) != find_set(parent, v)) {
        /* we are going to go through the ordered edges in order keeping where
         * they start, end and their weight
         */
        x = edge[i_edge].u;
        y = edge[i_edge].v;
        max_edge = edge[i_edge].weight;
        /* go to the next edge */
        i_edge++;

        /* join both sets into one */
        union_set(parent, x, y);
    }

    /* free the memory */
    free(parent);

    return max_edge;
}

/**
 * Function used by the quicksort to see how two number relate
 *
 * @param const void * a
 * @param const void * b
 *
 * @return if the val a is greater, equal or under val b
 */
int cmpfunc (const void * a, const void * b) {
    
    struct Edge *edgeA = (struct Edge *)a;
    struct Edge *edgeB = (struct Edge *)b;
    
    return (edgeA->weight - edgeB->weight);
}

int main(int argc, char const *argv[]) {
    /*variables declaration*/
    int num_vertices;
    int num_arestas, num_pairs;
    int u, v, i, weight;
    struct Edge* edges;
    
    /* here we gonna read the number of elements and create the pointers vector */
    scanf("%d %d",&num_vertices, &num_arestas);

    edges = (struct Edge*) malloc(num_arestas * sizeof(struct Edge));
    
    /* here we read the graph edges and create them on the linked list (we are consideing
       an unoriented graph */
    for (i = 0; i < num_arestas; i++) {
        // printf("%d\n", i);
        scanf("%d %d %d",&u,&v,&weight);
        edges[i].u = u;
        edges[i].v = v;
        edges[i].weight = weight;
    }
    
    /* sort the graph edges by their weight */
    qsort(edges, num_arestas, sizeof(struct Edge), cmpfunc);
    
    /* here we read the pair for which we have to call the minMaxEdge function */
    scanf("%d", &num_pairs);
    for (i = 0; i < num_pairs; i++) {
        scanf("%d %d",&u,&v);
        printf("%d\n", minMaxEdge(edges, num_vertices, u, v));
    }

    free(edges);

    return 0;
}
