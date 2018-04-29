/*
 * matmul_pthread.c
 * matrix multiplication using pthread library
 * Author : Thomas Sunghoon Heo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <math.h>
#include <pthread.h> // parallel execution
#include "utils.h"

typedef struct matrix_s
{
    int rows;
    int cols;
    int stride;
    double *elements;
}matrix_t;


// execution time check
clock_t start, end; 
const int ROWSA = 4096;
const int COLSA = 4096;
const int ROWSB = 4096;
const int COLSB = 4096;

const int NUM_THREADS = 4;


matrix_t *init_matrix(int rows, int cols)
{
    matrix_t *matrix = (matrix_t *)malloc(sizeof(matrix_t));
    size_t allocs = rows * cols * sizeof(double);
    matrix->elements = (double *)malloc(allocs);
    int i;
    for(i = 0; i < rows * cols; i++)
    {
        matrix->elements[i] = sin((double)i) + cos((double)(i+1));
    }
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->stride = cols;
    return matrix;
}

// thread defines
typedef struct thread_arg
{
    double *ptr_A;
    double *ptr_B;
    double *ptr_C;
    int rowA;
    int colA;
    int rowB;
    int colB;
    int rowC;
    int colC;
    int tid;
}targ;

// thread routine
void *process(void *arg)
{
    targ *fargs = (targ *)arg;
    double *ptr_A = fargs->ptr_A;
    double *ptr_B = fargs->ptr_B;
    double *write = fargs->ptr_C;
    int rowsA = fargs->rowA;
    int colsA = fargs->colA;
    int rowsB = fargs->rowB;
    int colsB = fargs->colB;
    int colsC = fargs->colC;
    int rowsC = fargs->rowC;
    int tid = fargs->tid;
    int i,j,k;
    double sum;
    // set-up number of elements to compute
    int per_rowsA = rowsA / NUM_THREADS;
    int per_colsA = colsA / NUM_THREADS;
    int per_rowsB = rowsB / NUM_THREADS;
    int per_colsB = colsB / NUM_THREADS;
    int row_startA = per_rowsA * tid;
    int row_endA = per_rowsA * (tid + 1);
    int row_startB = per_rowsB * tid;
    int row_endB = per_rowsB * tid;
    int col_startA = per_colsA * tid;
    int col_endA = per_colsA * (tid + 1);
    int col_startB = per_colsB * tid;
    int col_endB = per_colsB * ( tid + 1);
    // our algorithm
    for(i = row_startA; i < row_endA; i++)
    {
        for(j = col_startB; j < col_endB; j++)
        {
            sum = 0.0;
            for(k = 0; k < ROWSB; k++)
            {
                sum += (ptr_A[colsA * i + k] * ptr_B[colsB * k + j]);
            }
            write[i * colsC + j] = sum;
        } 
    }
}

void print_10x10(matrix_t *m)
{
	int i,j;
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 10; j++)
		{
			printf("%.2lf ", m->elements[i * m->cols + j]);
		}
		printf("\n");
	}
}
int main(int argc, char **argv)
{
	printf("Matrix multiplication using pthread\n");
	printf("Initialize matrices\n");
    matrix_t *A = init_matrix(ROWSA, COLSA);
    matrix_t *B = init_matrix(ROWSB, COLSB);
    matrix_t *C = init_matrix(ROWSA, COLSB); // junk matrix
    targ *ARGUMENT = (targ *)malloc(sizeof(targ) * NUM_THREADS);
    pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * NUM_THREADS);
    int i, j;
    start = clock();
    for(i = 0; i < NUM_THREADS; i++)
    {
printf("%d-th thread is spawned\n", i+1);
    ARGUMENT[i].ptr_A = A->elements;
    ARGUMENT[i].ptr_B = B->elements;
    ARGUMENT[i].ptr_C = C->elements;
    ARGUMENT[i].rowA = A->rows;
    ARGUMENT[i].rowB = B->rows;
    ARGUMENT[i].colA = A->cols;
    ARGUMENT[i].colB = B->cols;
    ARGUMENT[i].colC = C->cols;
    ARGUMENT[i].rowC = C->rows;
    ARGUMENT[i].tid = i;
    pthread_create(&(threads[i]), NULL, process, ARGUMENT + i);
    }
    for(i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    end = clock() - start;
    printf("showing 10 x 10 elements\n");
    print_10x10(C);
    free(A->elements); free(B->elements); free(C->elements);
    free(A); free(B); free(C);
    free(ARGUMENT); free(threads);
    printf("%lf sec elapsed\n" , (double)(end) / CLOCKS_PER_SEC);

    return 0;
}
