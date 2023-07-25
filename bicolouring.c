#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    struct Node* adjList[MAX_VERTICES];
    bool visited[MAX_VERTICES];
    int color[MAX_VERTICES];
};

struct Node* createNode(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = false;
        graph->color[i] = -1;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

bool isBipartiteDFS(struct Graph* graph, int v, int c) {
    graph->visited[v] = true;
    graph->color[v] = c;

    struct Node* adjNode = graph->adjList[v];
    while (adjNode != NULL) {
        int adjVertex = adjNode->vertex;
        if (!graph->visited[adjVertex]) {
            if (!isBipartiteDFS(graph, adjVertex, 1 - c)) {
                return false;
            }
        } else if (graph->color[v] == graph->color[adjVertex]) {
            return false;
        }
        adjNode = adjNode->next;
    }
    return true;
}

bool isBipartite(struct Graph* graph, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        if (!graph->visited[i]) {
            if (!isBipartiteDFS(graph, i, 0)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int numVertices, numEdges;
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &numVertices, &numEdges);

    struct Graph* graph = createGraph();

    printf("Enter the edges (format: src dest):\n");
    for (int i = 0; i < numEdges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    if (isBipartite(graph, numVertices)) {
        printf("The graph is bipartite.\n");
    } else {
        printf("The graph is not bipartite.\n");
    }

    return 0;
}
