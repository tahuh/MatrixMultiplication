/*
 * utils.c
 * source file for utils.c
 * Author : Thomas Sunghoon Heo
 */

#include "utils.h"

double matrix_at(double *ptr, int row, int col, int stride)
{
    return ptr[row * stride + col];
}

void set_elem_at(double *ptr, int row, int col, int stride, double v)
{
    ptr[row * stride + col] = v;
}
