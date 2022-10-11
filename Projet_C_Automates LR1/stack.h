// ------------------* Nefzi Wacim *----------------- 
//-------------------* stack.c *------------------

#ifndef stack_h
#define stack_h

/*
--------Prototypes des fonctions de stack.c----------
*/
#define SIZE 1000

typedef struct stack {
    int content[SIZE];
    int length;
} stack;

/*  @requires nothing
    @assigns nothing
    @ensures return an empty stack 
*/

stack new();

/*  @requires nothing
    @assigns nothing
    @ensures return an empty stack 
*/
stack init_stack(stack r);

//Vacuity test 
/*  @requires nothing
    @assigns nothing
    @ensures return if stack r is empty  
*/
int vacuity_test_stack(stack r);

/*  @requires: nothing
    @assigns : stack r 
    @ensures : put i on the top of r
*/

void push(int i, stack *r);

/*  @requires: nothing
    @assigns : stack r 
    @ensures : remove and return the element at the top of the stack r
*/
int pop(stack *r);

/*  @requires: nothing
    @assigns : nothing
    @ensures : print stack r
*/

void print_stack(stack *r);

#endif


// ------------------* Nefzi Wacim *----------------- 
//-------------------* stack.h *------------------