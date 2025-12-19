#ifndef LAB2_H
#define LAB2_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quick(int arr[], int low, int high);
void selection(int arr[], int n);
void pr_arr(int arr[], int n);
int* from_file(const char* filename, int* size);
int* gen_rand(int size);
int l2();

#endif