#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <stdio.h>
#include <stdlib.h>
typedef struct Graph Graph;
typedef struct Stack Stack;
typedef struct Node Node;

struct Graph {
    int V; //vertices
    int **edgeMat; //pointer to 2-d array (adjacency matrix)
};

struct Node {
    int val;
    Node *next;
};

struct Stack {
    Node *top;
    int size;
};

//////////////////// LINKED LIST METHODS /////////////

Node *initLinkedList(int val) {
    Node *head = malloc(sizeof(Node));
    head->val = val;
    head->next = NULL;
    return head;
}

Node* addNodeStart(Node *head, int val) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = head;
    return node;
}

void addNodeEnd(Node *head, int val) {

    Node *temp;
    Node *node = malloc(sizeof(Node));
    node->val = val;
    
    temp = head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = node;
}

void releaseList(Node *head) {
    //release memory from the list
    Node *runner, *temp;
    runner = head;

    while(runner != NULL) {
        temp = runner->next;
        free(runner);
        runner = temp;
    }
}

////////////////// STACK METHODS ////////////////////

Stack * initStack(int size) {
    Stack *stack = malloc(sizeof(Stack));
    stack->size = size;
    stack->top = NULL;
    return stack;
}

int isEmpty(Stack *stack) {
    if(stack->top == NULL) return 1;
    else return 0;
}

void push(Stack *stack, int val) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = stack->top;
    stack->top = node;
}

int pop(Stack *stack) {
    int res;
    Node *temp;
    if(stack->top == NULL) return 0;
    res = stack->top->val;
    temp = stack->top;    
    stack->top = temp->next;
    free(temp);
    return res;
}

void releaseStack(Stack *stack) {
    releaseList(stack->top);
    free(stack);
}

///////////////////// GRAPH METHODS //////////////////

Graph* initGraph(int vertices) {
    int i, j;
    Graph *graph = malloc(sizeof(Graph));
    graph->V = vertices;

    //allocate mem for graph
    graph->edgeMat = malloc(sizeof(int*) * graph->V);
    for(i = 0; i < graph->V; i++) {
        graph->edgeMat[i] = malloc(sizeof(int) * graph->V);
    }

    for(i = 0; i < graph->V; i++)
        for(j = 0; j < graph->V; j++) {
            graph->edgeMat[i][j] = 0;
        }

    return graph;
}

void addEdge(Graph *graph, int source, int dest) {
    if(graph != NULL) {
        if(graph->edgeMat != NULL) {
            graph->edgeMat[source][dest] = 1;
        }
    }
}

void depthFirstSearch(Graph *graph, int visited[], int vertex) {
    int i;
    visited[vertex] = 1;
    printf(" %d", vertex);
    for(i = 0; i < graph->V; i++) {
        if(graph->edgeMat[vertex][i] == 1) {
            if(visited[i] != 1) {
                depthFirstSearch(graph, visited, i);
            }
        }
    }
}

void depthFirstSearchNonRec(Graph *graph, int visited[], int vertex) {
//mark it as visited
    int i, currVertex;
    Stack *stack;
    visited[vertex] = 1;

    stack = initStack(graph->V);
    push(stack, vertex);

    //push vertex on stack
    while(!isEmpty(stack)) { //stack not empty
        //pop node from top of stack
        currVertex = pop(stack);

        visited[currVertex] = 1;
        printf(" %d,", currVertex);

        //visit all its neighbours
        for(i = graph->V - 1; i >=0 ; i--) {
            //if neighbour is not visited then
            if((graph->edgeMat[currVertex][i] == 1) && (visited[i] == 0)) {
                 //push it on top of the stack
                 push(stack, i);
            }
            //do for all vertices
        }
    }
    releaseStack(stack);
}

//release memory
void releaseGraph(Graph *graph) {
    int i;
    for(i = 0; i < graph->V; i++) {
        free(graph->edgeMat[i]);
    }
    free(graph->edgeMat);
}

int main(int argc, char **agv) {
    int i;
    int visited[4];
    Graph *graph = initGraph(4);

    graph->edgeMat[0][1] = 1;
    graph->edgeMat[0][2] = 1;
    graph->edgeMat[1][2] = 1;
    graph->edgeMat[2][0] = 1;
    graph->edgeMat[2][3] = 1;
    graph->edgeMat[3][3] = 1;

    for(i = 0; i < graph->V; i++) {
        visited[i] = 0;
    }
    printf("DFS rec ");
    depthFirstSearch(graph, visited, 2);
    
    for(i = 0; i < graph->V; i++) {
        visited[i] = 0;
    }

    printf("\n DFS non_rec ");
    depthFirstSearchNonRec(graph, visited, 2);

    releaseGraph(graph);
    return 0;
}

#pragma GCC diagnostic pop 
