// ------------------* Nefzi Wacim *----------------- 
//-------------------* Module Pile (Stack) *------------------

#include <stdio.h> 
#include <stdlib.h>
#include "stack.h"

/*  @requires nothing
    @assigns nothing
    @ensures return an empty stack 
*/

stack new(){
    stack r;
    r.length = -1;
    return r;
}

/*  @requires nothing
    @assigns nothing
    @ensures return an empty stack 
*/
stack init_stack(stack r){
    r.length= -1;
    return r;
}

//Vacuity test 

/*  @requires nothing
    @assigns nothing
    @ensures return if stack r is empty 
*/
int vacuity_test_stack(stack r){
    return(r.length < 0);
}

/*  @requires: nothing
    @assigns : stack r 
    @ensures : put i on the top of r
*/

void push(int i, stack *r){
    if (r->length == SIZE-1) {
        printf("Stack is full");
        return;
    }
    r -> length++;
    r -> content[r->length] = i;
}

/*  @requires: nothing
    @assigns : stack r 
    @ensures : remove and return the element at the top of the stack r
*/
int pop(stack *r){
    if(vacuity_test_stack(*r)){
        printf("Stack is empty, you can't pop the last element");
        return 0;
    }
    //si r.length == 0 
    int s = r -> content[r-> length];
    r -> length--;
    return s;
}

/*  @requires: nothing
    @assigns : nothing
    @ensures : print stack r
*/

void print_stack(stack *r){
    stack s = *r; //copy of r to preserve it
    if(vacuity_test_stack(*r)){
        printf("Stack is empty");
        return;
    }
    while(!vacuity_test_stack(s)){
        printf("%3i\n", pop(&s)); // pour plus de visibilité
    }
    printf("\n");
}

/*
int main(){
    
    stack r = new();
    printf("l'élement 0 est %i\n",r.content[0]);
    printf("l'élement 1 est %i\n",r.content[1]);
    printf("l'élement 999 est %i\n",r.content[999]);
    printf("l'élement 1000 est %i\n",r.content[1000]);
    printf("l'élement 1001 est %i\n",r.content[1001]);
    push(1,&r);
    printf(" sa longueur est %i\n",r.length);
    push(6,&r);
    push(8,&r);
    push(3,&r);
    push(42,&r);
    push(0,&r);
    push(9,&r);
    push(8,&r);
    print_stack(&r);

    printf("l'élement 0 est %i\n",r.content[0]);

    for(int i=0; i<6 ;i++){ 
        pop(&r);
        printf("length : %i\n", r.length);
    }
    int c = pop(&r);
    printf("le pop vaut %i\n", c);
    print_stack(&r);


    return 0;
}
*/

// ------------------* Nefzi Wacim *----------------- 
//-------------------* Module Pile (Stack) *------------------