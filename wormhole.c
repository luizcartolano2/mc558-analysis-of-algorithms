/**
 * @file puzzle.c
 * @author Luiz Eduardo Cartolano - 183012
 * @date 6 Dec 2019
 * @brief 
 *
 * 
 * 
 * 
 * 
 * 
 * 
 * @see https://susy.ic.unicamp.br:9999/mc558a/03/enunc.html
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

int main(int argc, char const *argv[]) {
    /*variables declaration*/
    int num_vertices;
    int num_arestas;
    int u, v, i, weight, j;
    struct Edge* edges;
    int *dst;
    int neg_edge = 0;

    /* here we gonna read the number of elements and create the pointers vector */
    scanf("%d %d",&num_vertices, &num_arestas);

    edges = (struct Edge*) malloc(num_arestas * sizeof(struct Edge));
    dst = malloc((num_vertices) * sizeof(int));

    for (i = 0; i < num_vertices; ++i)
    	dst[i] = 999999999;
    dst[0] = 0;

    /* here we read the graph edges and create them on the linked list (we are consideing
       an unoriented graph */
    for (i = 0; i < num_arestas; i++) {
        // printf("%d\n", i);
        scanf("%d %d %d",&u,&v,&weight);
        edges[i].u = u;
        edges[i].v = v;
        edges[i].weight = weight;

        if (weight < 0)
        	neg_edge = 1;
    }
    
    if (!neg_edge) {
    	printf("Impossivel\n");
    	return 0;
    }

    /* Exec Bellman-Ford */
    
    /* First we relax the vertex */
    for (i = 0; i < num_vertices; i++) {
    	for (j = 0; j < num_arestas; j++) {
    		u = edges[j].u;
    		v = edges[j].v;
    		weight = edges[j].weight;

    		if (dst[u] != 999999999 && dst[u] + weight < dst[v]) {
    			dst[v] = dst[u] + weight; 
    		}
    	}
    }

    /* now we check for neg cycles */
    for (j = 0; j < num_arestas; j++) {
		u = edges[j].u;
		v = edges[j].v;
		weight = edges[j].weight;

		if (dst[u] != 999999999 && dst[u] + weight < dst[v]) {
			printf("Possivel\n");
    		return 0;
		}
    }

    free(edges);
    free(dst);

    printf("Impossivel\n");
    return 0;
}