

#include <stdlib.h>
#include <stdio.h>


int nb_of_states2(FILE *f){
    if(f == NULL)
        exit(1);
    char buf[7];
    fgets(buf,7,f);
    for(int i=0; i<7; i++)
        printf("buf[%i] vaut %i\n",i,buf[i]);
    printf("la position du cursuer 2 est %li\n", ftell(f));
    return buf[2];
} 

int nb_of_states(FILE *f){
    if(f == NULL)
        exit(1);
    char buf[7];
    fgets(buf,7,f); // on ne veut que la valeur int et pas a.
    // sscanf(buf, "%s");
    for(int i=0; i<7; i++)
        printf("buf[%i] vaut %s\n",i,&buf[i]);
    printf("la position du cursuer est %li\n", ftell(f));
    return atoi(&buf[2]); 
}



int main(int argc, char* argv[]){
    FILE *f= fopen(argv[1],"r");

    printf("le nombre d'état 2 vaut : %i\n", nb_of_states2(f));  
    // printf("le nombre d'état vaut : %i\n", nb_of_states(f));
    
    //printf("le nombre d'état 2 vaut : %i\n", nb_of_states2(f));
    
    fclose(f);
}