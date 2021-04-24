#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "matrix.h"

int main(int argc, char *argv[])
{
    int N = atoi(argv[1]);
    int *A,*B;
    long *C;
    //rellenado de matrices
    A = alloc_matrix(N);
    B = alloc_matrix(N);
    C = alloc_matrixL(N);

    fill_matrix(A, N, rand()%1001+1000);
    fill_matrix(B, N, rand()%1001+1000);
    fill_matrixC(C, N, 0);

    clock_t start = clock();
    // Start measuring time
    struct timespec begin, end; 
    clock_gettime(CLOCK_REALTIME, &begin);
    
    multiply_matrix(A,B,C,N);
    // Stop measuring time and calculate the elapsed time
    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;

    clock_t fin = clock();
    double tiempo = (double)(fin - start);
    //print_matrix(C,N);
    printf("Tiempo de CPU: %.20f\n", tiempo/CLOCKS_PER_SEC);
    printf("Tiempo de Pared: %.20f seconds.\n", elapsed);
    return 0;
}
