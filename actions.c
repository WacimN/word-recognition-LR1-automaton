// ------------------* Nefzi Wacim *----------------- 
//-------------------* Mondule Actions *------------------

//Le fichier .aut est parcouru qu'une seule fois
//La méthode utilisé est celle des fgetc au détriment de fgets excepté pour l'obtention du nombre d'état de l'automate

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "matrix.h"


/* ----------------* Matrice associé au Nombre d'état de l'automate *---------------- */

//Fonction opérationnel 

/*  @requires: a valid File f
    @assigns : nothing
    @ensures : return the number of states of the automaton 
*/

int nb_of_states(FILE *f){
    if(f == NULL){
        fprintf(stderr,"The file is empty or doesn't exist, please enter a valid file  \n");
        exit(1);
    }
    char buf[7]; // 7 est suffisant puisqu'il y a au plus 256 états dans l'automate soit au plus 3 octets codant le nombre d'états
    fgets(buf,7,f); 
    //printf("la position du curseur après avoir pris le nombre d'état est %li\n", ftell(f));
    return atoi(&buf[2]); //  permet de transformer une chaîne de caractères (%s), représentant une valeur entière, en une valeur numérique de type int
                          // buf[2] car buf[0]= a et buf[1] correspond à l'espace
}



/* ----------------* Matrice associé à Actions *---------------- */

// Les lignes correpondent aux lettres et les colonnes à l'état associé 
// le curseur est bien placé grâce au fgets de la fonction nb_of_states

//Fonction opérationnel 

/*  @requires: a valid File f
    @assigns : nothing
    @ensures : return the matrix of action defined as M[s][c]=action(s,c), s : the state and c : the letter
*/

Matrix actions_matrix(FILE *f, int n){
    Matrix M = create_Matrix(n,128); //Matrice n lignes et 128 colonnes
    if (f != NULL){
        int i=0;
        int current_char = 0; 
        // double boucle qui va ajouter les élements du fichier dans la matrice 
        while(i<n){       //Boucle while avec incrémention classique et majorant fixe donc se termine (n vaut au plus 256)
            int j=0;
            while(j<128){ //Boucle while avec incrémention classique et majorant fixe donc se termine
                current_char =fgetc(f);
                M[i][j]=current_char;
                j++;
            }
            i++;
        }
    }
    fseek(f, 1,SEEK_CUR); // Pour avoir la position du début de réduit pour la fonction réduit_matrix, 
                          //le 1 permet de sauter le 10 (= saut de ligne), équivaut à   fseek(f, 4+n*128 + 1,SEEK_SET);
    // printf("la position finale de actions_matrix : %ld\n",ftell(f));
    return M;
}

/* ----------------* Matrice associé à Réduit *---------------- */

// La ligne 1 correpond au nombre d'état à depiler pour un état donnée correspondant à la colonne associé à ce même état 
// La ligne 2 à la même architecture et correspond à A qui servira à la seconde variable de branchement

//Fonction opérationnel 

/*  @requires: a valid File f
    @assigns : nothing
    @ensures : return the matrix of reduction defined as M[i][s]=reduit(s), i = 0 or 1,  s : the state and c : the letter
*/

Matrix reduit_matrix(FILE *f, int n){ // Cette fonction est opérationnel
    Matrix M= create_Matrix(2, n);
    int current_char= 0 ; 
    if (f !=NULL){
        int j,i ;
        // printf("\nPostion réduit_matrix  : %ld\n", ftell(f)); //le curseur est bien placé grâce à actions_Matrix
        for(i=0;i<2;i++){
            if (i==0) { //première ligne correspond au nombre d'état à dépiler suivant l'état courrant 
                for(j=0; j<n; j++){
                current_char =fgetc(f);
                    M[i][j]=current_char;
                }
            }
            else { // deuxième ligne correspond à A 
                fseek(f,1,SEEK_CUR); // Afin d'éviter le saut de ligne, C'est la raison pour laquelle j'ai effectué un if , else 
                for(j=0; j<n; j++){
                    current_char =fgetc(f);
                    M[i][j]=current_char;
                }
            }
        }
    }
    fseek(f, 1,SEEK_CUR); //pour sauter le dernier saut de ligne 
    // printf("la position finale de  reduit_matrix (compté avec les 2 sauts de ligne) : %ld\n", ftell(f));
    return M;
}


/* ----------------* Matrice associé à Décale *---------------- */

/*  décale(s,c) = s' 
        s étant l'état
        c la lettre 
        s' le nouvel état 
    les lignes correpondent aux état s 


    Puisque le main va lire les lettre en entrée standart il vaut mieux avoir l'information directement 
    à travers les indices de la matrice quitte à allouer de la mémoire en grande quantité 
    (on considère qu'il y a au plus 128 lettres dans l'alphabet)
*/


//Fonction opérationnel 


/*  @requires: a valid File f
    @assigns : nothing
    @ensures : return the matrix of reduction defined as M[s][c]=s',  s : the state c : the letter, s'= new state
*/

Matrix decale_matrix(FILE *f, int n){
    // printf("la position initale de decale_matrix est %ld\n", ftell(f)); //le curseur est normalement bien placé grâce aux fonctions précédentes appellé dans l'ordre
    Matrix M= create_init_Matrix(n,128,-1); //ligne correspondent à s et les colonnes à c, rempli par s' 
                                            //Initalisation à -1 au lieu de 0 pour eviter la confusion avec l'état 0 si l'implémentation même
                                            // de l'automate contient des erreurs, il fera l'objet d'un printf(Warning) dans le main pour l'utilisateur 
    //Pour la première valeur :
    int s,c,sb;
    s = fgetc(f);
    c = fgetc(f);
    sb = fgetc(f);
    while(s!=173){ // 173 correspond à '/255' en décimal. La boucle se termine car le fichier .aut à forcément trois 173 en fin de décale
        M[s][c]=sb;
        s = fgetc(f);
        c = fgetc(f);
        sb = fgetc(f);
        // printf("s:%d  c:%d  sb:%d\n",s,c,sb); 
    }
    //inutile de faire un fseek car la fonction est allée jusqu'à (s,c,sb)=(173,173,173)
    // printf("la position finale de decale_matrix est %ld\n", ftell(f));
    return M;
}

/* ----------------* Matrice associé à Décale *---------------- */


//La fonction branchement_matrix est EXACTEMENT similaire à decale_matrix
//Mais pour plus de clarté j'ai préféré faire 2 fonction avec 2 nom différent.


/*  branchement(s',A) = s 
        s' étant l'état après les dépilement de Réduit
        A la deuxième composante de Réduit 
        s le nouvel état qui sera empilé dans la pile
    les lignes correpondent aux état s' 


    Puisque le main va lire les lettre en entrée standart il vaut mieux avoir l'information directement 
    à travers les indices de la matrice quitte à allouer de la mémoire en grande quantité 
    (on considère qu'il y a au plus 128 lettres dans l'alphabet)
*/

//Fonction opérationnel 

/*  @requires: a valid File f
    @assigns : nothing
    @ensures : return the matrix of reduction defined as M[s][c]=s',  s : the state c : the letter, s'= new state
*/

Matrix branchement_matrix(FILE *f, int n){
    // printf("la position initale de barnchement_matrix est %ld\n", ftell(f));
    Matrix M= create_init_Matrix(n,128,-1); //Initalisation à -1 au lieu de 0 pour eviter la confusion avec l'état 0 si l'implémentation même
                                            // de l'automate contient des erreur, il fera l'objet d'un printf(Warning) dans le main 
    int s,A,sb; // correspond respectivement à s, A et s' de l'enoncé 
    //Pour la première valeur :
    s = fgetc(f);
    A = fgetc(f); 
    sb = fgetc(f);
    while(s!=173){
        M[s][A]=sb;
        s = fgetc(f);
        A = fgetc(f);
        sb = fgetc(f);
    }
    // printf("la position finale de branchement matrice est %ld\n", ftell(f));
    return M;
}


/*

----------------* main permettant d'afficher uniquement les matrices des actions*--------------


int main(int argc, char* argv[]){
    FILE *f =fopen(argv[1],"r+");

    int n = nb_of_states(f);
    printf("Le nombre d'état de l'automate est de %i \n", n);
    Matrix A_m = actions_matrix(f, n);
    Matrix R_m = reduit_matrix(f,n);

    printf("\nla matrice action : \n");
    print_Matrix(A_m,n , 128); 
    printf("\n");

    printf("\nla matrice reduit : \n");
    print_Matrix(R_m,2,n);
    printf("\n");

    Matrix D_m=decale_matrix(f,n);
    printf("\nla matrice decale : \n");    
    print_Matrix(D_m,n,128);
    printf("\n");

    Matrix B_m = branchement_matrix(f,n);
    printf("\nla matrice Branchement : \n");    
    print_Matrix(B_m,n,128);
    printf("\n");

    fclose(f);
}

*/


// ------------------* Nefzi Wacim *----------------- 
//-------------------* Mondule Actions *------------------