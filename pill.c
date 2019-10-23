#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list {
    struct node * no;
    struct linked_list *next;
}linked_list;

typedef struct node {
    int vert;
    int color;
    int ti,tf;
    int bi_cor;
    linked_list *list;
}node;


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
void DFS(node *graph, int size);
/**
 * function DFS_Visit
 *
 * @param node *graph
 * @param int i
 * @param int size
 *
 * @return the function has no return
 */
void DFS_Visit(node *graph, int i, int size, int dad_color);


int main(int argc, char const *argv[]) {
    /*variables declaration*/
    int numb_elem;
    int num_arestas;
    int u;
    int v;
    int i;
    int k;
    node *graph;

    ciclica = 0;
    bi_colorivel = 1;
    ordena_ti_i = 0;

    /*here we gonna read the number of elements and create the pointers vector*/
    scanf("%d %d",&numb_elem, &num_arestas);
    graph = malloc((numb_elem+1) * sizeof(node));
    ordena_ti = calloc(numb_elem,sizeof(int));
    if((!graph) || (!ordena_ti))
        printf("Error in the graph allocation\n");

    /*here we initialize the graph vector with NULL*/
    for(k = 1; k <= numb_elem; k++){
        graph[k].vert = k;
        graph[k].list = NULL;
        graph[k].color = 0;
        graph[k].bi_cor = -1;
    }

    for (i = 0; i < num_arestas; i++) {
        scanf("%d %d",&u,&v);
        insertList(graph,u,v);
        insertList(graph,v,u);
    }


    DFS(graph,numb_elem);

    /*
    for (int i = 0; i < numb_elem; i++)
        printf("%d [%d,%d] %d \n",graph[ordena_ti[i]].vert, graph[ordena_ti[i]].ti, graph[ordena_ti[i]].tf, graph[ordena_ti[i]].bi_cor);


    printf("%d\n", bi_colorivel);
    */

    if (bi_colorivel == 0) {
        printf("dotutama\n");
    } else {
        printf("doturacu ou dotutama\n");
    }

    return 0;

}

void insertList(node *graph, int i, int j){
    linked_list *aux;
    aux = malloc(sizeof(linked_list));

    aux->no = &graph[j];
    aux->next = graph[i].list;
    graph[i].list = aux;

    return;
}

void DFS(node *graph, int size){
    int i;

    tim3 = 0;
    for(i = 1; i <= size; i++)
        if(!graph[i].color){
            graph[i].bi_cor = 1;
            DFS_Visit(graph,i,size, graph[i].bi_cor);
        }
}

void DFS_Visit(node *graph, int i, int size, int dad_color){
    linked_list *aux;
    
    ordena_ti[ordena_ti_i++] = i;
    tim3++;
    graph[i].ti = tim3;
    graph[i].color = 1;
    graph[i].bi_cor = dad_color ^ 1;
  
    aux = graph[i].list;

    while (aux) {
        if(!aux->no->color)
            DFS_Visit(graph,aux->no->vert,size, graph[i].bi_cor);
        if(aux->no->color == 1) {
            ciclica = 1;
            if (aux->no->bi_cor == graph[i].bi_cor) {
                bi_colorivel = 0;
            }
        }
        aux = aux->next;
    }

  graph[i].color = 2;
  tim3++;
  graph[i].tf = tim3;
}
