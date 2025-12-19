#ifndef LAB4_H
#define LAB4_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

struct Trunk {
    struct Trunk* prev;
    char* str;
};

struct PathResult {
    int minPath;
    int maxPath;
};

void showTrunks(struct Trunk* p);
void printTree(struct Node* root, struct Trunk* prev, int isLeft);
int max(int a, int b);
int min(int a, int b);
int height(struct Node* node);
int getBalance(struct Node* node);
struct Node* newNode(int key);
struct Node* rightRotate(struct Node* y);
struct Node* leftRotate(struct Node* x);
struct Node* balance(struct Node* p);
struct Node* insert(struct Node* node, int key);
struct Node* findMin(struct Node* p);
void freeTree(struct Node* node);
int diameter(struct Node* root, int* height);
int findMinLeafDistance(struct Node* root, int* minDepth);
void findMinMaxLeafPaths(struct Node* root, int* minPath, int* maxPath);
struct Node* readTreeFromFile(const char* filename);
int l4();

#endif