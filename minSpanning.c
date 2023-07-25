#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for the DSU
struct Subset {
    int parent;
    int rank;
};

// Function prototypes
int find(struct Subset subsets[], int i);
void unionSets(struct Subset subsets[], int x, int y);
int compareEdges(const void* a, const void* b);
void kruskalMST(struct Edge edges[], int V, int E);

int main() {
    int V, E; // V: number of vertices, E: number of edges
    printf("Enter the number of vertices and edges: ");
    scanf("%d%d", &V, &E);

    struct Edge* edges = (struct Edge*)malloc(E * sizeof(struct Edge));

    printf("Enter source, destination, and weight of each edge:\n");
    for (int i = 0; i < E; i++) {
        scanf("%d%d%d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    kruskalMST(edges, V, E);

    free(edges);
    return 0;
}

// Find the set of an element (uses path compression)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Perform union of two sets (uses rank to optimize)
void unionSets(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare function for sorting edges based on weight
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Kruskal's algorithm to find the Minimum Spanning Tree
void kruskalMST(struct Edge edges[], int V, int E) {
    // Step 1: Sort the edges in non-decreasing order of their weights
    qsort(edges, E, sizeof(struct Edge), compareEdges);

    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));
    for (int i = 0; i < V; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    printf("Minimum Spanning Tree:\n");
    int mstWeight = 0;
    for (int i = 0; i < E; i++) {
        int x = find(subsets, edges[i].src);
        int y = find(subsets, edges[i].dest);

        if (x != y) {
            printf("%d - %d (%d)\n", edges[i].src, edges[i].dest, edges[i].weight);
            mstWeight += edges[i].weight;
            unionSets(subsets, x, y);
        }
    }
    printf("Total MST weight: %d\n", mstWeight);

    free(subsets);
}
