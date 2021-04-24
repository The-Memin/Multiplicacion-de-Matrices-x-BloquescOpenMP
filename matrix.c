
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int* alloc_matrix(int size) {
    return (int*) malloc(size * size * sizeof(int));
}
long* alloc_matrixL(int size) {
    return (long*) malloc(size * size * sizeof(long));
}

void fill_matrix(int* matrix, int size, int fill_value) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            matrix[i*size + j] = fill_value;
        }
    }
}

void fill_matrixC(long* matrix, int size, int fill_value) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            matrix[i*size + j] = fill_value;
        }
    }
}


void print_matrix(int* matrix, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++)
            printf("%d ", matrix[i*size + j]);
        printf("\n");
    }
    printf("-------------------------------------------------------------------------\n");
}

void multiply_matrix(int* A, int* B, long* C, int N) {
    int i, j, k;

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                C[i*N + j] += A [i*N + k] * B[k*N + j];
            }
        }
}