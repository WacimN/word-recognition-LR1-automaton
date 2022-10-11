// ------------------* Nefzi Wacim *----------------- 
//-------------------* Module main *------------------

#include <stdlib.h>
#include <stdio.h>
#include "actions.h"
#include "matrix.h"
#include "stack.h"

int main(int argc, char *argv[]){
    FILE *f = fopen(argv[1], "r");// word.aut word_bis.aut  dyck.aut  arith.aut
    printf("File %s correctly read.\n",argv[1]); //Comme dan sl'exemple de l'enoncé
    
    int n = nb_of_states(f); //Le nombre d'état de l'automate
    // printf("There are %i states in the automaton\n",n);
    
    //l'ordre d'appel des Matrices ci dessous est fondamentale pour être cohérent sur l'emplacement des curseurs (d'après mon implémentation)
    Matrix A_m = actions_matrix(f, n);
    Matrix R_m = reduit_matrix(f, n);
    Matrix D_m = decale_matrix(f, n);
    Matrix B_m = branchement_matrix(f, n);

/*
    int user_choice=0; //Booléen qui va demander si l'utilisateur veut quitter l'executable 

    while(user_choice!=1){
        char yes_or_no; //Choix de l'utilisateur s'il veut continuer sur le même fichier ou non 
*/

        char buf[256]; //buffer pour l'entrée standart 
        //Permet de se saisir de l'entrée standart
        printf("Please enter your inputs.\n");
        fgets(buf,  256,stdin); //On suppose que les mots n'ont pas une taille supérieur à 256, dans la cas contraire
                                // l'executable ne va considérer qu eles 256 premiers caractères
        // sscanf(buf,"%[^\n]"); // n'as pas d'utilité ici + Créer un warning : warning: format ‘%s’ expects a matching ‘char *’ argument [-Wformat=]

        //Création de la pile d'état 
        stack s= new();
        push(0,&s); // la pile contient Q0 (équivaut a l'état 0)
        


        int k=0; // indice de la lettre de l'entrée standart, permet d'avancer dans l'entrée standart
        int current_state=0; //L'état courrant, ici 0 car l'état initiale est Q0 = 0
        int current_letter = buf[k]; //première lettre de l'entrée standart, initialement on a buf[0], k=0    

        int act = 0; // La valeur de action(s,c) s:état c:lettre, la valeur de débat n'a pas d'importance car act=A_m[current_state][current_letter]; dans le While
        int nb_of_unstacking, A; //Pour la fonction Réduit : nombre de dépilement et A
        int stop_condition; //Condition d'arrêt du while qui s'arrête quand stop_condition=1 qui s'avère vrai pour Accepted/Rejected and Default du switch 


        while(stop_condition!=1){
            act=A_m[current_state][current_letter];
            // printf("l'action est désormais %i avec l'état %i \n",act, current_state);
            switch (act){
            
            case 0: // Rejected 
                printf("Rejected\n");
                printf("The error occurred to the letter %i\n",k+1); //k+1 et non k car la première lettre de l'entrée est d'indice 0 
                stop_condition=1;
                break;

            case 1: // Accepted 
                printf("Accepted\n");
                stop_condition=1;
                break;

            case 2: // Décale
                current_state = D_m[current_state][current_letter]; //s' = decale(s,c)
                if (current_state == -1){ //Dans l'optique où le fichier serait mal implémenter, ma matrice décale contient des -1 pour les lettre et état non définis pour décale
                    fprintf(stderr, "the automaton is poorly implemented regarding 'décale'");
                    exit(1);
                }
                push(current_state,&s); // on empile s'
                // Puis on avance dans l'entrée:
                k++;
                current_letter=buf[k]; 
                break;
            
            case 3: //Réduit
                nb_of_unstacking = R_m[0][current_state]; //nombre de dépilement, au plus 256
                A = R_m[1][current_state];                // Même notation que l'énoncé
                for(int i=0; i<nb_of_unstacking ;i++){ 
                    pop(&s);
                }
                if (B_m[s.content[s.length]][A] == -1){ //Dans l'optique où le fichier serait mal implémenter, ma matrice décale contient des -1 pour les lettre et état non définis pour décale
                    fprintf(stderr, "the automaton is poorly implemented regarding 'branchement'");
                    exit(2);
                }
                push(B_m[s.content[s.length]][A],&s); // on empile Branchement(s',A)=s , s' etant s.content[s.length] qui est le sommet de la pile
                current_state=s.content[s.length]; // On accède au nouveau sommet de la pile. NE SURTOUT PAS OUBLIER CETTE LIGNE ! Sinon boucle infinie
                break;

            default: 
                printf("The .aut file contains errors, especially in n*128 bytes of Actions\n");
                stop_condition=1;
                break;
            }
        }
    /*
    printf("Do you want to leave the program? [Y/n]\n");
    scanf("%c",&yes_or_no);
        switch(yes_or_no){
            case 'Y':
                user_choice=1;
                exit(0);
                break;
            case 'n':
                user_choice=0;
                break;
            default:
                fprintf(stderr,"Veuillez répondre par Y (for yes) or n (for no)\n");
                break;
        }
    printf("\n");
    }
    */

    //On libère l'allocation mémoire liée au matrice des actions 
    free_matrix(A_m,n);       
    free_matrix(R_m,2);       
    free_matrix(D_m,n);       
    free_matrix(B_m,n);       

    fclose(f);
    return 0;
}


// ------------------* Nefzi Wacim *----------------- 
//-------------------* Module main *------------------