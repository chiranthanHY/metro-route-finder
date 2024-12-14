#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "heap.h"

#define MAX 100
#define INF INT_MAX

struct Node {
    int station_id;
    int distance;
    struct Node* next;
};

struct Graph {
    int num_stations;
    struct Node** adj_list;
};

// Create a new adjacency list node
struct Node* newNode(int station_id, int distance) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->station_id = station_id;
    node->distance = distance;
    node->next = NULL;
    return node;
}

// Create a graph
struct Graph* createGraph(int num_stations) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->num_stations = num_stations;
    graph->adj_list = (struct Node**)malloc(num_stations * sizeof(struct Node*));
    
    for (int i = 0; i < num_stations; ++i)
        graph->adj_list[i] = NULL;

    return graph;
}

// Add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest, int distance) {
    struct Node* node = newNode(dest, distance);
    node->next = graph->adj_list[src];
    graph->adj_list[src] = node;

    node = newNode(src, distance);
    node->next = graph->adj_list[dest];
    graph->adj_list[dest] = node;
}

// Print the metro route
void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

// Dijkstra’s Algorithm
void dijkstra(struct Graph* graph, int src, int dest) {
    int V = graph->num_stations;
    int distance[V];
    int parent[V];

    struct MinHeap* minHeap = createMinHeap(V);

    for (int v = 0; v < V; ++v) {
        distance[v] = INF;
        parent[v] = -1;
        minHeap->array[v] = newHeapNode(v, distance[v]);
        minHeap->pos[v] = v;
    }

    distance[src] = 0;
    minHeap->array[src] = newHeapNode(src, distance[src]);
    decreaseKey(minHeap, src, distance[src]);
    minHeap->size = V;

    while (minHeap->size > 0) {
        struct HeapNode* minNode = extractMin(minHeap);
        int u = minNode->station_id;

        struct Node* adj = graph->adj_list[u];
        while (adj != NULL) {
            int v = adj->station_id;

            if (isInMinHeap(minHeap, v) && distance[u] != INF && adj->distance + distance[u] < distance[v]) {
                distance[v] = distance[u] + adj->distance;
                parent[v] = u;
                decreaseKey(minHeap, v, distance[v]);
            }
            adj = adj->next;
        }
    }

    printf("Shortest route from station %d to station %d:\n%d", src, dest, src);
    printPath(parent, dest);
    printf("\nTotal distance: %d km\n", distance[dest]);

    // Calculate fare (example: 2 units per distance)
    int fare = distance[dest] * 2;
    printf("Total fare: %d RS\n", fare);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }
    int source = atoi(argv[1]);
    int destination = atoi(argv[2]);
    
    int num_stations = 10; 
    struct Graph* graph = createGraph(num_stations);

    // Adding metro lines (edges) between stations (nodes)
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 2, 1);
    addEdge(graph, 2, 1, 2);
    addEdge(graph, 1, 3, 5);
    addEdge(graph, 2, 3, 8);
    addEdge(graph, 3, 4, 3);
    addEdge(graph, 4, 5, 6);
    addEdge(graph, 5, 6, 3);
    addEdge(graph, 6, 7, 4);
    addEdge(graph, 7, 8, 2);
    addEdge(graph, 8, 9, 5);
    addEdge(graph, 1, 8, 10); // Connect station 1 and 8 with a distance of 10 units

    dijkstra(graph, source, destination);

    return 0;
}
