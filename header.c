#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct matrix {

    int rows;
    int columns;
    int assigned;
    float values[100][100];
    float detailed[3][1000];
    unsigned int detail_size;
    unsigned int sparse;
    unsigned int density;
    unsigned int sparsity;
    struct matrix *nextMatrix;



}matrix;

void add_matrix (struct matrix *matrix, int rows, int columns)
void add_random_matrix (struct matrix *matrix, int rows, int columns)
void add_matrix_values (struct matrix *matrix)
void show_all_matrix (struct matrix *matrix)
void show_number(struct matrix *matrix, unsigned int number)
void show_all_matrix_detailed (struct matrix *matrix)