/*
 * matmul_openmp.c
 * Matrix multiplication using OpenMP
 * Author : Thomas Sunghoon Heo
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
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

int NUM_THREADS = 4;

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

void matmul_omp_kernel(matrix_t *A, matrix_t *B, matrix_t *C)
{
        NUM_THREADS = omp_get_max_threads();
//	omp_set_num_threads(NUM_THREADS);
	double st, ed;
	st = omp_get_wtime();
#pragma omp parallel num_threads(NUM_THREADS)
{
	int tid = omp_get_thread_num();
	int row_chunk = A->rows / NUM_THREADS;
	int col_chunk = B->cols / NUM_THREADS;
	int row_start = tid * row_chunk;
	int row_end = (tid + 1) * row_chunk;
	int col_start = tid * col_chunk;
	int col_end = (tid + 1) * col_chunk;
	printf("[Thread -%d] Work start A[%d,%d] x B[%d,%d]\n", tid, row_start, row_end, col_start, col_end);
	
	int i,j,k;
	double sum, a_ik, b_kj;
	for(i = row_start; i < row_end; i++)
	{
		for(j = col_start; j < col_end; j++)
		{
			sum = 0.0;
			for(k = 0; k < B->rows; k++)
			{
				a_ik = matrix_at(A->elements, i, k, A->stride);
				b_kj = matrix_at(B->elements, k, j , B->stride);
				sum +=  (a_ik* b_kj);
			}
			set_elem_at(C->elements, i, j ,C->stride, sum);
		}
	}
} // end of parallel section
	ed = omp_get_wtime() - st;
	printf("%lf sec elapsed\n" , ed);
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

int main()
{
	matrix_t *A, *B, *C;
	A = init_matrix(ROWSA, COLSA); B= init_matrix(ROWSB, COLSB); C = init_matrix(ROWSA, COLSB);
	printf("matrix multiplication using OpenMP\n");
	int max_threads = omp_get_max_threads();
	printf("maximum %d threads are available\n" , max_threads);
	matmul_omp_kernel(A,B,C);
	print_10x10(C);
	free(A->elements); free(B->elements); free(C->elements);
    free(A); free(B); free(C);
}
