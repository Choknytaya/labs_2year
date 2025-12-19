#ifndef LAB5_H
#define LAB5_H

#include <stdio.h>
#include <stdbool.h>

#define INF 999
#define MAX_LINE_LENGTH 100

typedef struct Edge {
    int length;
    int vertex;
    struct Edge* next; 
} Edge;

typedef struct Vertex {
    Edge* head;
} Vertex;

typedef struct Graph {
    Vertex* vertices;
    int vertices_count;
} Graph;

void printFloydMatrix(int** dist, int n);
Graph* createGraph(int vertices_count);
void addEdge(Graph* graph, int src, int dest, int weight);
void freeGraph(Graph* graph);
int** floydWarshall(Graph* graph);
void dijkstra(Graph* graph, int start, int target);
Graph* readGraphFromFile(const char* filename, int* start_vertex, int* target_vertex);
int l5(void);

#endif