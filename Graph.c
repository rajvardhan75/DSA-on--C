#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
};

struct Stack {
    int items[MAX_VERTICES];
    int top;
};

struct Graph {
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
};

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }
    return graph;
}

void enqueue(struct Queue* queue, int value) {
    if(queue->rear == MAX_VERTICES-1)
        return;
    if(queue->front == -1)
        queue->front = 0;
    queue->rear++;
    queue->items[queue->rear] = value;
}

int dequeue(struct Queue* queue) {
    if(queue->front == -1)
        return -1;
    int item = queue->items[queue->front];
    queue->front++;
    if(queue->front > queue->rear) {
        queue->front = queue->rear = -1;
    }
    return item;
}

void push(struct Stack* stack, int value) {
    if(stack->top == MAX_VERTICES-1)
        return;
    stack->items[++stack->top] = value;
}

int pop(struct Stack* stack) {
    if(stack->top == -1)
        return -1;
    return stack->items[stack->top--];
}

void addEdge(struct Graph* graph, int src, int dest) {
    graph->adjacencyMatrix[src][dest] = 1;
}

void bfs(struct Graph* graph, int startVertex) {
    bool visited[MAX_VERTICES] = {false};
    int level[MAX_VERTICES];
    for(int i = 0; i < graph->numVertices; i++) {
        level[i] = -1;
    }
    
    struct Queue* queue = createQueue();
    
    visited[startVertex] = true;
    level[startVertex] = 0;
    enqueue(queue, startVertex);
    
    printf("\nStarting BFS from vertex %d\n", startVertex);
    
    while(queue->front != -1) {
        int currentVertex = dequeue(queue);
        printf("Dequeued: %d (Level %d)\n", currentVertex, level[currentVertex]);
        
        for(int i = 0; i < graph->numVertices; i++) {
            if(graph->adjacencyMatrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                level[i] = level[currentVertex] + 1;
                enqueue(queue, i);
                printf("Enqueued: %d (Level %d)\n", i, level[i]);
            }
        }
    }
    
    printf("\nFinal levels from start vertex:\n");
    for(int i = 0; i < graph->numVertices; i++) {
        if(level[i] != -1) {
            printf("Vertex %d: Level %d\n", i, level[i]);
        }
    }
    
    free(queue);
}

void dfsUtil(struct Graph* graph, int vertex, bool visited[], int discovery[], 
             int finish[], int* time) {
    visited[vertex] = true;
    (*time)++;
    discovery[vertex] = *time;
    printf("Pushed: %d (Time: %d)\n", vertex, *time);
    
    for(int i = 0; i < graph->numVertices; i++) {
        if(graph->adjacencyMatrix[vertex][i] == 1 && !visited[i]) {
            dfsUtil(graph, i, visited, discovery, finish, time);
        }
    }
    
    (*time)++;
    finish[vertex] = *time;
    printf("Popped: %d (Time: %d)\n", vertex, *time);
}

void dfs(struct Graph* graph, int startVertex) {
    bool visited[MAX_VERTICES] = {false};
    int discovery[MAX_VERTICES];
    int finish[MAX_VERTICES];
    int time = 0;
    
    for(int i = 0; i < graph->numVertices; i++) {
        discovery[i] = -1;
        finish[i] = -1;
    }
    
    printf("\nStarting DFS from vertex %d\n", startVertex);
    dfsUtil(graph, startVertex, visited, discovery, finish, &time);
    
    printf("\nVertex timing information:\n");
    for(int i = 0; i < graph->numVertices; i++) {
        if(discovery[i] != -1) {
            printf("Vertex %d: Discovery time = %d, Finish time = %d\n", 
                   i, discovery[i], finish[i]);
        }
    }
}

int main() {
    int numVertices, numEdges;
    printf("Enter number of vertices: ");
    scanf("%d", &numVertices);
    
    struct Graph* graph = createGraph(numVertices);
    
    printf("Enter number of edges: ");
    scanf("%d", &numEdges);
    
    printf("\nEnter edges (format: source destination):\n");
    for(int i = 0; i < numEdges; i++) {
        int src, dest;
        printf("Edge %d: ", i + 1);
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
    
    int startVertex;
    printf("\nEnter starting vertex for traversals: ");
    scanf("%d", &startVertex);
    
    bfs(graph, startVertex);
    dfs(graph, startVertex);
    
    free(graph);
    return 0;
}