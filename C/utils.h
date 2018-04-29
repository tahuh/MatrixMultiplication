/*
 * utils.h
 * utility functions for matrix multiplication
 * Author : Thomas Sunghoon Heo
 */

#ifndef _UTILS_H
#define _UTILS_H

#ifdef __cplusplus
extern "C"
{
#endif

double matrix_at(double *matrix, int row, int col, int stride);
void set_elem_at(double *matrix, int row, int col, int stride, double v);

#ifdef __cplusplus
}
#endif
#endif
