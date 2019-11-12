/*
    Projeto 1 - MC558 - Projeto e análise de algortimos II
    Aluno: Luiz Eduardo Cartolano
    RA: 183012
    Profa. Christiane Neme Campos
*/

/* include default C libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

/* a structure to represent an edge in graph */
struct Edge  { 
    int src, dest; 
    int weight;
};

/* A utility function to do union of two subsets */
int find_set(int parent[], int i) { 
    if (parent[i] == -1) 
        return i; 
    
    return find_set(parent, parent[i]); 
}

/* A utility function to do union of two subsets */
void union_set(int parent[], int x, int y) { 
    int xset = find_set(parent, x); 
    int yset = find_set(parent, y); 
    if(xset != yset){ 
       parent[xset] = yset; 
    } 
} 


int minMaxEdge(struct Edge* edge, int num_vertices, int u, int v) {

    /* Allocate memory for creating V subsets */
    int *parent = (int*) malloc(num_vertices * sizeof(int));
    /* declare the edge counter as zero */
    int i_edge = 0;
    /* initialize counter for edge weight */ 
    int max_edge = 0;
    /* auxiliar var */
    int x,y;
    /* Initialize all subsets as single element sets */
    memset(parent, -1, sizeof(int) * num_vertices); 

    while (find_set(parent, u) != find_set(parent, v)) {
        x = edge[i_edge].src;
        y = edge[i_edge].dest;
        max_edge = edge[i_edge].weight;

        union_set(parent, x, y);
    }

    return max_edge;

}

int main(int argc, char const *argv[]) {
    /*variables declaration*/
    int num_vertices;
    int num_arestas;
    int u, v, i, weight;
    struct Edge* edges;

    /* here we gonna read the number of elements and create the pointers vector */
    scanf("%d %d",&num_vertices, &num_arestas);

    edges = (struct Edge*) malloc(num_arestas * sizeof(struct Edge));
    
    /* here we read the graph edges and create them on the linked list (we are consideing
       an unoriented graph */
    for (i = 0; i < num_arestas; i++) {
        scanf("%d %d %d",&u,&v,&weight);
        edges[i].src = u;
        edges[i].dest = v;
        edges[i].weight = weight;
    }

    for (i = 0; i < num_arestas; i++) {
        printf("%d %d %d \n", edges[i].src, edges[i].dest, edges[i].weight);
    }


}
