#ifndef HEAP_H
#define HEAP_H

// Heap Node
struct HeapNode {
    int station_id;
    int distance;  // Distance from the source station
};

// MinHeap structure
struct MinHeap {
    int size;  // Number of heap nodes
    int capacity;  // Maximum capacity
    int *pos;  // Track the position of stations
    struct HeapNode **array;  // Array of heap nodes
};

// Function Prototypes
struct HeapNode* newHeapNode(int station_id, int distance);
struct MinHeap* createMinHeap(int capacity);
void swapHeapNode(struct HeapNode** a, struct HeapNode** b);
void minHeapify(struct MinHeap* minHeap, int idx);
struct HeapNode* extractMin(struct MinHeap* minHeap);
void decreaseKey(struct MinHeap* minHeap, int station_id, int distance);
int isInMinHeap(struct MinHeap* minHeap, int station_id);

#endif
