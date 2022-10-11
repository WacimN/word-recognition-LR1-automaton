// ------------------* Nefzi Wacim *----------------- 
//-------------------* matrix.h *------------------

#ifndef _MATRIX_H
#define _MATRIX_H

typedef int** Matrix;

/*  @requires nothing
    @assigns nothing
    @ensures return a 2D array e*m
*/

Matrix create_Matrix(int e, int m);

/*  @requires nothing
    @assigns nothing
    @ensures return a 2D array e*m initialized to init 
*/
Matrix create_init_Matrix(int e, int m, int init);

/*  @requires nothing
    @assigns nothing
    @ensures frees the dynamically allocated memory when creating a matrix.
*/

void free_matrix(Matrix M, int e);


/*  @requires a Valid Matrix 
    @assigns nothing
    @ensures print Matrix M
*/
void print_Matrix(Matrix M, int e, int m);

#endif

// ------------------* Nefzi Wacim *----------------- 
//-------------------* matrix.h *------------------
