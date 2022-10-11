// ------------------* Nefzi Wacim *----------------- 
//-------------------* actions.h *------------------

#ifndef _ACTIONS_H
#define _ACTIONS_H

#include "matrix.h"

/*  @requires: a valid File f
    @assigns : nothing
    @ensures : return the number of states of the automaton 
*/

int nb_of_states(FILE *f);


/*  @requires: a valid File f
    @assigns : nothing
    @ensures : return the matrix of action defined as M[s][c]=action(s,c), s : the state and c : the letter
*/

Matrix actions_matrix(FILE *f, int n);


/*  @requires: a valid File f
    @assigns : nothing
    @ensures : return the matrix of reduction defined as M[i][s]=reduit(s), i = 0 or 1,  s : the state and c : the letter
*/

Matrix reduit_matrix(FILE *f, int n);


/*  @requires: a valid File f
    @assigns : nothing
    @ensures : return the matrix of reduction defined as M[s][c]=s',  s : the state c : the letter, s'= new state
*/

Matrix decale_matrix(FILE *f, int n);

/*  @requires: a valid File f
    @assigns : nothing
    @ensures : return the matrix of reduction defined as M[s][c]=s',  s : the state c : the letter, s'= new state
*/

Matrix branchement_matrix(FILE *f, int n);

#endif


// ------------------* Nefzi Wacim *----------------- 
//-------------------* actions.h *------------------
