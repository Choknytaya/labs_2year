#include "../include/lab5.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Graph* createGraph(int vertices_count) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) return NULL;
    
    graph->vertices_count = vertices_count;
    graph->vertices = (Vertex*)malloc(vertices_count * sizeof(Vertex));
    
    if (!graph->vertices) {
        free(graph);
        return NULL;
    }
    
    for (int i = 0; i < vertices_count; i++) {
        graph->vertices[i].head = NULL;
    }
    
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    if (!graph || src < 0 || src >= graph->vertices_count || 
        dest < 0 || dest >= graph->vertices_count || weight <= 0) {
        return;
    }
    
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    if (!newEdge) return;
    
    newEdge->vertex = dest;
    newEdge->length = weight;
    newEdge->next = graph->vertices[src].head;
    graph->vertices[src].head = newEdge;
}

void freeGraph(Graph* graph) {
    if (!graph) return;
    
    for (int i = 0; i < graph->vertices_count; i++) {
        Edge* current = graph->vertices[i].head;
        while (current) {
            Edge* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->vertices);
    free(graph);
}

void printFloydMatrix(int** dist, int n) {
    printf("Матрица минимальных расстояний между всеми вершинами:\n");
    printf("   ");
    for (int i = 0; i < n; i++) {
        printf("%6d", i + 1);
    }
    printf("\n");
    
    for (int i = 0; i < n; i++) {
        printf("%2d: ", i + 1);
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) {
                printf("   INF");
            } else {
                printf("%5d ", dist[i][j]);
            }
        }
        printf("\n");
    }
}

int** floydWarshall(Graph* graph) {
    if (!graph) return NULL;
    
    int n = graph->vertices_count;
    int** dist = (int**)malloc(n * sizeof(int*));
    if (!dist) return NULL;
    
    for (int i = 0; i < n; i++) {
        dist[i] = (int*)malloc(n * sizeof(int));
        if (!dist[i]) {
            for (int j = 0; j < i; j++) free(dist[j]);
            free(dist);
            return NULL;
        }
        
        for (int j = 0; j < n; j++) {
            dist[i][j] = (i == j) ? 0 : INF;
        }
    }
    
    // Заполнение из списков смежности
    for (int i = 0; i < n; i++) {
        for (Edge* edge = graph->vertices[i].head; edge; edge = edge->next) {
            dist[i][edge->vertex] = edge->length;
        }
    }
    
    // Алгоритм Флойда-Уоршелла
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < n; j++) {
                if (dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    printf("\nФлойд-Уоршелл\n");
    printFloydMatrix(dist, n);
    
    return dist;
}

void dijkstra(Graph* graph, int start, int target) {
    if (!graph) return;
    
    int n = graph->vertices_count;
    int* dist = (int*)malloc(n * sizeof(int));
    bool* visited = (bool*)malloc(n * sizeof(bool));
    int* parent = (int*)malloc(n * sizeof(int));
    
    if (!dist || !visited || !parent) {
        free(dist);
        free(visited);
        free(parent);
        return;
    }
    
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }
    
    dist[start] = 0;
    
    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        int minDist = INF;
        
        for (int v = 0; v < n; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                u = v;
            }
        }
        
        if (u == -1 || minDist == INF) break;
        visited[u] = true;
        
        for (Edge* edge = graph->vertices[u].head; edge; edge = edge->next) {
            int v = edge->vertex;
            int weight = edge->length;
            
            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }
    
    printf("\nДейкстры\n");
    printf("Начальная вершина: %d, Конечная вершина: %d\n", start + 1, target + 1);
    
    printf("\nМинимальные расстояния от вершины %d:\n", start + 1);
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            printf("До вершины %d: Пути не существует\n", i + 1);
        } else {
            printf("До вершины %d: %d\n", i + 1, dist[i]);
        }
    }
    
    printf("\nМинимальный путь из %d в %d: ", start + 1, target + 1);
    if (dist[target] == INF) {
        printf("Пути не существует\n");
    } else {
        // Восстановление пути
        int path[n];
        int pathLength = 0;
        
        for (int v = target; v != -1; v = parent[v]) {
            path[pathLength++] = v;
        }
        
        printf("%d", path[pathLength-1] + 1);
        for (int i = pathLength-2; i >= 0; i--) {
            printf(" -> %d", path[i] + 1);
        }
        printf(" (длина: %d)\n", dist[target]);
    }
    
    free(dist);
    free(visited);
    free(parent);
}

Graph* readGraphFromFile(const char* filename, int* start_vertex, int* target_vertex) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка: не удалось открыть файл %s\n", filename);
        return NULL;
    }
    
    Graph* graph = NULL;
    *start_vertex = 0;
    *target_vertex = 4;
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        // Удаляем символ новой строки
        line[strcspn(line, "\n")] = '\0';
        
        if (line[0] == '\0') continue;
        
        int vertices_count;
        if (sscanf(line, "vertices_count: %d", &vertices_count) == 1) {
            graph = createGraph(vertices_count);
            continue;
        }
        
        if (sscanf(line, "start_vertex: %d", start_vertex) == 1) {
            (*start_vertex)--;
            continue;
        }
        
        if (sscanf(line, "target_vertex: %d", target_vertex) == 1) {
            (*target_vertex)--;
            continue;
        }
        
        if (graph) {
            int src, dest, weight;
            if (sscanf(line, "%d %d %d", &src, &dest, &weight) == 3) {
                addEdge(graph, src-1, dest-1, weight);
            }
        }
    }
    
    fclose(file);
    return graph;
}

int l5(void) {
    const char* filename = "graph.txt";     
    int start_vertex, target_vertex;
    
    Graph* graph = readGraphFromFile(filename, &start_vertex, &target_vertex);
    
    if (!graph) {
        printf("Не удалось загрузить граф из файла.\n");
        return 1;
    }
    
    printf("\nГраф загружен. Путь из вершины %d в вершину %d\n", 
           start_vertex + 1, target_vertex + 1);
    
    int** floydResult = floydWarshall(graph);
    
    if (floydResult) {
        printf("\nМинимальное расстояние (Флойд-Уоршелл): ");
        int distance = floydResult[start_vertex][target_vertex];
        printf(distance == INF ? "Пути не существует\n" : "%d\n", distance);
        
        for (int i = 0; i < graph->vertices_count; i++) {
            free(floydResult[i]);
        }
        free(floydResult);
    }
    
    dijkstra(graph, start_vertex, target_vertex);
    freeGraph(graph);
    
    return 0;
}