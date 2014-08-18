#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

#include <stdio.h>  //<cstdio>
#include <stdlib.h> //<cstdlib>
#include <assert.h> //<cassert>

#define SIZE 4

typedef struct Graph Graph;
typedef struct Stack Stack;
typedef struct Node Node;
typedef struct Queue Queue;

struct Graph {
//struct __attribute__((__packed__)) Graph {
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

struct Queue {
    Node *head;
    Node *tail;
    int size;
};

//////////////////// LINKED LIST METHODS /////////////

Node *initLinkedList(int val) {
    Node *head = (Node*) malloc(sizeof(Node));
    head->val = val;
    head->next = NULL;
    return head;
}

Node* addNodeStart(Node *head, int val) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->val = val;
    node->next = head;
    return node;
}

void addNodeEnd(Node *head, int val) {

    Node *temp;
    Node *node = (Node*) malloc(sizeof(Node));
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
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    stack->size = size;
    stack->top = NULL;
    return stack;
}

int isEmpty(Stack *stack) {
    if(stack->top == NULL) return 1;
    else return 0;
}

void push(Stack *stack, int val) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->val = val;
    node->next = stack->top;
    stack->top = node;
}

// assert: stack top is not NULL
int pop(Stack *stack) {
    int res;
    Node *temp;
    assert(stack->top != NULL);
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

///////////////////// QUEUE METHODS /////////////////

Queue* initQueue(int size) {
    Queue *queue = (Queue*) malloc(sizeof(Queue));
    queue->size = size;
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

//Return 1 if empty
int isEmptyQueue(Queue *queue) {
    assert(queue != NULL);
    if (queue->head == NULL) return 1;
    else return 0;
}

//Insert a node at the rear of the queue
void enqueue(Queue *queue, int val) {
    Node *node;
    assert(queue != NULL);

    node = (Node*) malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;

    //If enqueuing first element
    if(queue->head == NULL) {
        queue->head = node;
    } else {
        queue->tail->next = node;
    }
    //tail will change in any case
    queue->tail = node;
}

//Remove a node from the head of the queue
int dequeue(Queue *queue) {
    int res;
    Node *temp;

    assert(isEmptyQueue(queue) == 0);

    temp = queue->head;
    queue->head = temp->next;
    res = temp->val;

    free(temp);

    //check of removing last element
    if(queue->head == NULL) {
        queue->tail = NULL;
    }
    return res;
}

void releaseQueue(Queue *queue) {
    releaseList(queue->head);
    free(queue);
}

///////////////////// GRAPH METHODS //////////////////

Graph* initGraph(int vertices) {
    int i;
    Graph *graph = (Graph*) malloc(sizeof(Graph));
    graph->V = vertices;

    //allocate mem for graph
    graph->edgeMat = (int**) calloc(graph->V, sizeof(int*));
    for(i = 0; i < graph->V; i++) {
        graph->edgeMat[i] = (int*) calloc(graph->V, sizeof(int));
    }

    return graph;
}

//release memory
void releaseGraph(Graph *graph) {
    int i;
    for(i = 0; i < graph->V; i++) {
        free(graph->edgeMat[i]);
    }
    free(graph->edgeMat);
    free(graph);
}

void addEdge(Graph *graph, int source, int dest) {
    if(graph != NULL) {
        if(graph->edgeMat != NULL) {
            graph->edgeMat[source][dest] = 1;
        }
    }
}

//////////////// DEPTH FIRST SEARCH ////////////////

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

////////////// BREADTH FIRST SEARCH ///////////////////

void breadthFirstSearch(Graph *graph, int vertex) {
    int visited[SIZE];
    int i, currVertex;
    Queue *queue;
    for(i = 0; i < graph->V; i++) {
        visited[i] = 0;    
    }
    queue = initQueue(graph->V);
    enqueue(queue, vertex);
    
    while(!isEmptyQueue(queue)) {
        currVertex = dequeue(queue);
        visited[currVertex] = 1;
        printf(" %d", currVertex);

        for(i = 0; i < graph->V; i++) {
            //if there is an edge and that vertex is not visited
            if((graph->edgeMat[currVertex][i] == 1) && (visited[i] == 0)) {
                enqueue(queue, i);
            }
        }
    }

    releaseQueue(queue);
}


///////////////////////// MAIN /////////////////////////

int main(int argc, char **agv) {
    int i;
    int visited[SIZE];
    Graph *graph = initGraph(SIZE);

    printf("%d\n", sizeof(int **));
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

    printf("\n BFS non_rec");
    breadthFirstSearch(graph, 2);

    releaseGraph(graph);
    return 0;
}

#pragma GCC diagnostic pop 
