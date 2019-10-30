/*
    Projeto 1 - MC558 - Projeto e análise de algortimos II
    Aluno: Luiz Eduardo Cartolano
    RA: 183012
    Profa. Christiane Neme Campos
*/

/* include default C libraries */
#include <stdio.h>
#include <stdlib.h>

/* define the linked list struct that will be used to store the adj vertex */
typedef struct linked_list {
    struct node * no;
    struct linked_list *next;
}linked_list;

/* define the node struct that will represent the graph */
typedef struct node {
    int vert;
    int color;
    int ti,tf;
    int bi_cor;
    linked_list *list;
}node;

/* global variables that store some kind of execution state */
int tim3;
int ciclica;
int *ordena_ti;
int ordena_ti_i;
int bi_colorivel;

/**
 * insert the node into the Adjacency List
 *
 * @param node *graph
 * @param int i
 * @param int j
 *
 * @return the function a pointer to the begining of the list
 */
void insertList(node *graph, int i, int j);

/**
 * function DFS
 *
 * @param node *graph
 * @param int size
 *
 * @return the function has no return
 */
int DFS(node *graph, int size);

/**
 * function DFS_Visit
 *
 * @param node *graph
 * @param int i
 * @param int size
 *
 * @return the function has no return
 */
int DFS_Visit(node *graph, int i, int size, int dad_color);


/* main code that read the entries and coord function calls*/
int main(int argc, char const *argv[]) {
    /*variables declaration*/
    int numb_elem;
    int num_arestas;
    int u;
    int v;
    int i;
    int k;
    node *graph;

    /* initialize the global variables */
    ciclica = 0;
    bi_colorivel = 1;
    ordena_ti_i = 0;

    /* here we gonna read the number of elements and create the pointers vector */
    scanf("%d %d",&numb_elem, &num_arestas);
    graph = malloc((numb_elem+1) * sizeof(node));
    ordena_ti = calloc(numb_elem,sizeof(int));
    if((!graph) || (!ordena_ti))
        printf("Error in the graph allocation\n");

    /* here we initialize the graph vector with NULL */
    for(k = 1; k <= numb_elem; k++){
        graph[k].vert = k;
        graph[k].list = NULL;
        graph[k].color = 0;
        graph[k].bi_cor = -1;
    }

    /* here we read the graph edges and create them on the linked list (we are consideing
       an unoriented graph */
    for (i = 0; i < num_arestas; i++) {
        scanf("%d %d",&u,&v);
        insertList(graph,u,v);
        insertList(graph,v,u);
    }

    /* call to DFS function */
    DFS(graph,numb_elem);

    /* if the graph isn't bi-colorable he certainly is a poison, c.c. we can't know */
    if (bi_colorivel == 0) {
        printf("dotutama\n");
    } else {
        printf("doturacu ou dotutama\n");
    }

    return 0;
}

void insertList(node *graph, int i, int j){
    /* create an aux pointer that will represent the new node */
    linked_list *aux;
    aux = malloc(sizeof(linked_list));

    /* link two nodes */
    aux->no = &graph[j];
    aux->next = graph[i].list;
    graph[i].list = aux;

    return;
}

int DFS(node *graph, int size){
    int i;

    tim3 = 0;
    /* main loop of DFS*/
    for(i = 1; i <= size; i++)
        if(!graph[i].color){
            /* give the first node color one */ 
            graph[i].bi_cor = 1;
            /* call the DFS Visit function */
            if (!DFS_Visit(graph,i,size, graph[i].bi_cor))
                return 1;
        }

    return 1;
}

int DFS_Visit(node *graph, int i, int size, int dad_color){
    linked_list *aux;

    /* set the initial atributes for the node (start time of search, and color (gray) and the bi colorable flag
    as one */
    ordena_ti[ordena_ti_i++] = i;
    tim3++;
    graph[i].ti = tim3;
    graph[i].color = 1;
    graph[i].bi_cor = dad_color ^ 1;
    
    /* get the adj vertex of the nodes */
    aux = graph[i].list;

    while (aux) {
        /* if the vertex is white, visit him */
        if(!aux->no->color)
            if (!DFS_Visit(graph,aux->no->vert,size, graph[i].bi_cor))
                return 0;
        /* check if we are in a cycle, which happens when you are gray and check another gray vertex */
        if(aux->no->color == 1) {
            ciclica = 1;
            /* if a vertex and an adj vertex has the same color, it can be bi colorable */
            if (aux->no->bi_cor == graph[i].bi_cor) {
                bi_colorivel = 0;
                return 0;
            }
        }
        aux = aux->next;
    }
    /* close the exploration */
    graph[i].color = 2;
    tim3++;
    graph[i].tf = tim3;

    return 1;
}
