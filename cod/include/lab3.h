#ifndef LAB3_H
#define LAB3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node_3l {
    int data;
    struct Node_3l* next;
} Node_3l;

Node_3l* createNode(int value);
void append(Node_3l** head, int value);
int contains(Node_3l* head, int value);
Node_3l* difference(Node_3l* L1, Node_3l* L2);
void printList(Node_3l* head);
void deleteList(Node_3l** head);
Node_3l* createListFromString(const char* input);
int l3();

#endif 