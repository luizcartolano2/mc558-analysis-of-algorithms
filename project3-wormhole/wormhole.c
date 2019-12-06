/**
 * @file wormhole.c
 * @author Luiz Eduardo Cartolano - 183012
 * @date 6 Dec 2019
 * @brief 
 *
 * All wormholes have a constant time difference between their input and output. 
 * For example, a given wormhole may cause the person passing through it to stop 15 years in the future. 
 * Ellie Arroway, a brilliant physicist living on Earth, wants to study the Big Bang using wormholes. 
 * The scientist wants to achieve a sequence of wormholes that allows her to go far enough in the past.
 * Your goal is to reach the beginning of the universe and see the Big Bang with your own eyes.
 * Write a program to find out if your venture will be successful.
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

    /* alocate the edges and distance vectors */
    edges = (struct Edge*) malloc(num_arestas * sizeof(struct Edge));
    dst = malloc((num_vertices) * sizeof(int));

    /* Initialize the distance vertex from source */
    for (i = 0; i < num_vertices; ++i)
    	dst[i] = 999999999;
    dst[0] = 0;

    /* here we read the graph edges and create them on the linked list (we are consideing
       an unoriented graph */
    for (i = 0; i < num_arestas; i++) {
        scanf("%d %d %d",&u,&v,&weight);
        edges[i].u = u;
        edges[i].v = v;
        edges[i].weight = weight;

        if (weight < 0)
        	neg_edge = 1;
    }
    
    /* If all edges are positive it's impossible to go back on time */
    if (!neg_edge) {
    	printf("Impossivel\n");
    	return 0;
    }

    /*********************/
    /* Exec Bellman-Ford */
    /*********************/
    /* First we relax the vertex V-1 times */
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

    /* If the code gets here doesn't have neg cycles, so its impossible */
    printf("Impossivel\n");

    /* Free the memory */
    free(edges);
    free(dst);

    return 0;
}
