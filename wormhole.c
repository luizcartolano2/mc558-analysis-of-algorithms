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

/* define the linked list struct that will be used to store the adj vertex */
typedef struct linked_list {
    struct node * no;
    struct linked_list *next;
    int weight;
}linked_list;

/* define the node struct that will represent the graph */
typedef struct node {
    int vert;
    linked_list *list;
}node;

/**
 * insert the node into the Adjacency List
 *
 * @param node *graph
 * @param int i
 * @param int j
 *
 * @return the function a pointer to the begining of the list
 */
void insertList(node *graph, int i, int j, int weight);

/* main code that read the entries and coord function calls*/
int main(int argc, char const *argv[]) {
    /*variables declaration*/
    int numb_elem;
    int num_arestas;
    int u,v,w;
    int i;
   	 
    int *dst;
    node *graph;

    /* here we gonna read the number of elements and create the pointers vector */
    scanf("%d %d",&numb_elem, &num_arestas);
    graph = malloc((numb_elem) * sizeof(node));
    dst = malloc((numb_elem) * sizeof(int));
    if((!graph) || (!dst))
        printf("Error in the graph allocation\n");

    /* here we initialize the graph vector with NULL */
    for(i = 0; i < numb_elem; i++){
        graph[i].vert = i;
    }

    /* Initialize the distance vector */
	for(i = 0; i < numb_elem; i++){
        dst[i] = 100000;
    }
    dst[0] = 0;

    /* here we read the graph edges and create them on the linked list (we are consideing
       an unoriented graph */
    for (i = 0; i < num_arestas; i++) {
        scanf("%d %d %d",&u,&v,&w);
        insertList(graph,u,v,w);
    }

 
    return 0;
}

void insertList(node *graph, int i, int j, int w){
    /* create an aux pointer that will represent the new node */
    linked_list *aux;
    aux = malloc(sizeof(linked_list));

    /* link two nodes */
    aux->no = &graph[j];
    aux->next = graph[i].list;
    aux->weight = w;
    graph[i].list = aux;

    return;
}