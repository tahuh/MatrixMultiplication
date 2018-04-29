/*
 * matmul_serial.c
 * Serial (single-threaded) matrix multiplication
 * Author : Thomas Sunghoon Heo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

matrix_t *init_matrix(int rows, int cols)
{
    matrix_t *matrix = (matrix_t *)malloc(sizeof(matrix_t));
    size_t allocs = rows * cols * sizeof(double);
    matrix->elements = (double *)malloc(allocs);
    int i;
    for(i = 0; i < rows * cols; i++)
    {
        matrix->elements[i] = sin((double)i) + cos((double)(i+1));
		//matrix->elements[i] = (double)(i);
    }
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->stride = cols;
    return matrix;
}

matrix_t* matmul_kernel(matrix_t *A, matrix_t *B)
{
     matrix_t *C = (matrix_t *)malloc(sizeof(matrix_t));
     C->elements = (double *)malloc(sizeof(double) * ROWSA * COLSB);
     memset(C->elements, 0.0f, sizeof(double) * ROWSA * COLSB);
	 C->stride = B->cols;
     int i,j,k;
     double sum, a_ik, b_kj;
     for(i = 0; i < A->rows; i++)
     {
         for(j = 0; j < B->cols; j++)
         {
             sum = 0.0;
             for(k = 0; k < B->rows; k++)
             {
                 a_ik = A->elements[i * A->stride + k];
                 b_kj = B->elements[k * B->stride + j];
		//		 printf("%lf %lf\n" , a_ik, b_kj);
                 sum += (a_ik * b_kj);
			//	 printf("[%d][%d][%d] %lf x %lf = %lf. Sum = %lf\n",i,j,k,a_ik,b_kj, a_ik * b_kj,sum);
             }
             //set_elem_at(C->elements, i, j , C->stride, sum);
			 C->elements[i * C->stride + j] = sum;
         }
     }
	 C->rows = A->rows;
	 C->cols = B->cols;
     return C;
}

int main()
{
     matrix_t *A = init_matrix(ROWSA, COLSA);
     matrix_t *B = init_matrix(ROWSB, COLSB);
     int i , j; double v;
	 printf("initial matrix -- A\n");
	 for(i = 0; i < 3; i++)
     {
         for(j = 0; j <3; j++)
         {
              printf("%.2lf ", matrix_at(A->elements, i, j, A->stride));
         }
         printf("\n");
     }
	 
	 	 printf("initial matrix -- B\n");
	 for(i = 0; i < 3; i++)
     {
         for(j = 0; j <3; j++)
         {
              printf("%.2lf ", matrix_at(B->elements, i, j, B->stride));
         }
         printf("\n");
     }
	 
     start = clock();
     printf("matrix multiplication in serial way\n");
     matrix_t *C = matmul_kernel(A,B);
     end = clock() - start;
     printf("Showing 10 x 10 elements\n");
     for(i = 0; i < 10; i++)
     {
         for(j = 0; j < 10; j++)
         {
              printf("%.2lf ", matrix_at(C->elements, i, j, C->stride));
         }
         printf("\n");
     }
     printf("Elapsed %lf sec\n" , (double)end / CLOCKS_PER_SEC);
     free(A->elements); free(B->elements); free(C->elements);
     free(A); free(B); free(C);
}
