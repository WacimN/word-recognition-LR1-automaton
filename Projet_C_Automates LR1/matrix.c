// ------------------* Nefzi Wacim *----------------- 
//-------------------* Module Matrix *------------------

#include<stdio.h>
#include<stdlib.h> 
#include "matrix.h"


// création d'une matrice de Taille (e,m) = (lignes, colonnes) 

/*  @requires nothing
    @assigns nothing
    @ensures return a 2D array e*m
*/

Matrix create_Matrix(int e, int m){ //e le nombre d'état de l'automate 
    Matrix M=(Matrix)malloc(e*sizeof(int*));
    int i;
    for(i=0; i<e; i++)
        M[i]=calloc(m,sizeof(int)); //initalise à 0
    return M;
}

/*  @requires nothing
    @assigns nothing
    @ensures return a 2D array e*m initialized to init
*/

Matrix create_init_Matrix(int e, int m, int init){ //init la valeur avec laquel on initialise
    Matrix M=(Matrix)malloc(e*sizeof(int*));
    int i,j;
    for(i=0; i<e; i++)
        M[i]=calloc(m,sizeof(int)); //initalise à 0
    for(i=0; i<e; i++){
        for(j=0; j<m; j++){
            M[i][j]=init;
        }
    }
    return M;
}


/*  @requires nothing
    @assigns nothing
    @ensures frees the dynamically allocated memory when creating a matrix.
*/

void free_matrix(Matrix M, int e){
    for(int i=0; i<e;i++){
        free(M[i]);
    }
    free(M);
}


/*  @requires a Valid Matrix 
    @assigns nothing
    @ensures print Matrix M
*/

void print_Matrix(Matrix M, int e, int m){ // e : nombre d'états de l'automate 
int i,j;
for(i=0; i<e;i++){
    printf("| ");
    for(j=0;j<m;j++){
        printf("%3d,",M[i][j]);

        }   
    printf(" |\n\n");
    }
}

 
/*
int main(){
    return 0;
}
*/

/*
int main(){
    int i;
    printf("veuillez entrer la taille de la matrice:" );
    scanf("%i",&i);
    Matrix M = create_Matrix(i,i);
    print_Matrix(M,i,i);
    free_matrix(M,i,i);
    return 0;
}
*/

// ------------------* Nefzi Wacim *----------------- 
//-------------------* Module Matrix *------------------