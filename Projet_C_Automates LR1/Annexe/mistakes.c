//LES Ratés
#include <stdio.h>
#include <stdlib.h>

int nb_of_states(FILE *f){
    fopen("f","r");
    int n;
    if(f == NULL)
        exit(1);
    fscanf(f,"a %d\n",&n);
    return n;
    fclose(f);
}


/*
int main() {
    // writeFile( filename );
    FILE *f =fopen("word.aut","r+");
    char buffer[5];
    // readFile(f);
    printf("%li \n", fread(buffer, 4, 3, f)); 

    return 0;
}
*/

 /*
// la boucle while ne se termine jamais , voir version d'après 

int main(int argc, char *argv[])
{
    FILE* fichier = NULL;
    int caractereActuel = 0;
 
    fichier = fopen("word.aut", "r");
 
    if (fichier != NULL)
    {
        // Boucle de lecture des caractères un à un
        do
        {
            fseek(fichier, 4, SEEK_SET); // en 2eme arg, 0 correspond au à la premiere decimal du fichier, donc pour passer le premier 10
            // (saut de ligne) il faut aller à 4 directement (qui correpond à action(0,0))
            caractereActuel = fgetc(fichier); // On lit le caractère
            //printf("%d\n", caractereActuel); // le \n m'as permis de comprendre que caractere actuel prend le nombre décimal a 2 chiffres 
            //et donc utiliser fseek correctement
            printf("%d",caractereActuel);

        } while (caractereActuel != 10); // On continue tant que fgetc n'a pas retourné 10 qui signifie un saut à la ligne
        printf("\n");
        fclose(fichier);
    }
 
    return 0;
}
*/



// on va donc utiliser un while avec une condition d'arret et ça marche ! 
//on peut utiliser cette fonction afin de compléter la matrice au fur et à mesure 

int main(int argc,char* argv[]){
    FILE* f= fopen("word.aut", "r");
    int current_char = 0;
    fseek(f,4,SEEK_SET); //on se place directement au caractère correspondant à action(0,0)
    if (f != NULL){
        int i =127;
        while(i>=0){
            current_char =fgetc(f);
            printf("%d",current_char);
            i--;
        }
        printf("\n");
    }
    fclose(f);
    return 0;
}



// 14h 29/12/2021

Matrix actions_matrix(FILE *f){ // 
    fopen("f","r+");
    int n = nb_of_states(f); // Le cas où f==NULL est traité dans cette fonction
    Matrix M = create_Matrix(n,128); //Matrice n lignes et 128 colonnes
    // boucle qui va ajouter les élements du fichier dans la matrice 
    int current_char = 0;
    fseek(f,4,SEEK_SET); //on se place directement au caractère correspondant à action(0,0)
    if (f != NULL){
        int i;
        int j=0;
        for(i=0; i<n; i++){
            while(j<128){ // PROBLEME : seule la première ligne fonctionne 
                current_char =fgetc(f);
                M[i][j]=current_char;
                j++;
            }
        }
    }
    return M;
}

// 31/12/21 10:51 
// J'avais juste oublié de remettre j à 0 --'

Matrix actions_matrix(FILE *f, int n){
    Matrix M = create_Matrix(n,128); //Matrice n lignes et 128 colonnes
    if (f != NULL){
        int i;
        int j=0;
        // double boucle qui va ajouter les élements du fichier dans la matrice 
        // fseek(f, 4, SEEK_SET);
        int current_char = 0;        
        for(i=0; i<n; i++){
            fseek(f, 4+i*128,SEEK_SET);//on se place directement au caractère correspondant à action(0,0) pour i=0
            // printf("Postion début : %ld\n", ftell(f));
            // fseek(f, 128 ,SEEK_CUR);
            while(j<128){ // PROBLEME : seule la première ligne fonctionne
                current_char =fgetc(f);
                 printf("Postion pour %i : %ld\n",i, ftell(f));
                M[i][j]=current_char;
                j++;
            }
            printf("Postion actuel : %ld\n", ftell(f)); // La position est bonne 
        }
    }
    fseek(f, 128 + 1,SEEK_CUR); // Pour avoir la position du début de réduit pour la fonction réduit_matrix, 
                                    //le +1 permet de sauter le 10 (= saut de ligne), équivaut à   fseek(f, 4+n*128 + 1,SEEK_SET);
    printf("position finale actions_ matrix : %ld\n",ftell(f));
    return M;
}


// réduit avec fread 
// NE FONCTIONNE  PAS  

Matrix reduit_matrix(FILE *f, int n){
    Matrix M= create_Matrix(2, n);
    if (f !=NULL){
        int j ;
        // fseek(f, 4+i*128,SEEK_SET) // Inutile d'apres la ligne suivante
        printf("\nPostion actuel : %ld\n", ftell(f)); //Il n'y a, en effet, pas eu de rewind(f) depuis la création de actions_Matrix
        char* chaine[2*n + 4]; //le +4 correpond au 10 83 83 83, représation décimal du saut à la ligne et des '255'
        fread(chaine,sizeof(char),2*n+4,f);
        for(j=0; j<n; j++ ){ 
            M[0][j]=chaine[j]; 
            M[1][j]=chaine[j+(n-1)+5];  // pour avoir le terme après 10 83 83 83
        }         
    }
    return M;
}

// ESSAIE D'OPTIMISATION : NE MARCHE PAS 
Matrix reduit_matrix(FILE *f, int n){
    Matrix M= create_Matrix(2, n);
    int current_char= 0 ; 
    if (f !=NULL){
        int j,i ;
        // fseek(f, 4+i*128,SEEK_SET) // Inutile d'apres la ligne suivante
        // printf("\nPostion actuel : %ld\n", ftell(f)); //Il n'y a, en effet, pas eu de rewind(f) automatique depuis la création de actions_Matrix
        for(i=0;i<2;i++){
            for(j=0; j<n; j++){
                if(current_char == 10 ){ // la deuxième condition permet d'éviter le cas où il y aurait un 10 parmi les n valeur de réduit
                    current_char = fgetc(f); //permet de passer le saut de ligne
                    printf("Postion bloop 2: %ld  et %i \n ", ftell(f),j);
                }
                else{
                    current_char = fgetc(f);
                    M[i][j]=current_char;
                    printf("Postion normal : %ld et %i\n", ftell(f), j);
                } 

            }
        }
    }
    return M;
}


//MARCHE PAS 
Matrix decale_matrix(FILE *f, int n){
    Matrix M= create_Matrix(n,128);
    //le curseur est normalement bien placé grâce aux fonctions précédentes appellé dans l'ordre
    printf("la position de decale matrice est %ld\n", ftell(f));
    int s, c, sb;
    char dec[3];
    fgets(dec,3,f); // NE PEUX LIRE QUE DES CHAINE DE CARACTERE PAS DES NOMBRE 
    fseek(f, 1,SEEK_CUR);
    fseek(f, 1,SEEK_CUR);
    printf("la position finale de  reduit matrice est %ld\n", ftell(f));
    sscanf(dec,"%d %d %d", &s, &c , &sb);
    printf("%d %d %d\n", dec[1],dec[2],dec[3]);
    printf("%d %d %d\n", s, c,sb);
    /*
    while(s != 173 && c != 173 && sb != 173){
        printf("%d %d %d\n", s, c ,sb );
    }
    */ 
    return M;
}

//Problème rencontrée : la boucle s'est faite même avec le 173 173 173 ! Erreur corrigé 

Matrix decale_matrix(FILE *f, int n){
    printf("la position de decale matrice est %ld\n", ftell(f)); //le curseur est normalement bien placé grâce aux fonctions précédentes appellé dans l'ordre
    Matrix M= create_init_Matrix(n,128,-1); //ligne correspondent à s et les colonnes à s', permet de gagner de la place en mémoire (on aurait pu faire Matrice(n,128) et compléter avec les s')
    int s,c,sb;
    // while(s!=1 && c!=122 && sb!=1){ // inutile de mettre s!=173 && c!=173 && sb!=173 (ce qui nous arrange) avec l'alphabet s'arrête a 127, on est sur que 173 ne sera jamais une lettre
    int i=0;
    while(s!=173){
        s = fgetc(f);
        c = fgetc(f);
        sb = fgetc(f);
        M[s][c]=sb;
        printf("s:%d  c:%d  sb:%d\n",s,c,sb); 
        i++;

    }
    printf("la position finale de decale matrice est %ld\n", ftell(f));
    return M;
}


// 01/01/2021

int main(){
    /*char buf[256];
    fgets(buf,  256,stdin);
    printf("%i %i %i\n",buf[0],buf[1],buf[2]);
    sscanf(buf, "%[^\n]" );
    // sscanf(buf,"%s");
    printf("%i %i %i\n",buf[0],buf[1],buf[2]);*/
    char buf[256];
    fgets(buf,  256,stdin);
    printf("%i %i %i\n",buf[0],buf[1],buf[2]);
    int j;
    for(j=0;j<15;j++){
        printf("%2i",buf[j]);
    }
    /*scanf("%[^\n]",buf);
    int i;
    for(i=0;i<15;i++){
        printf("%2d",buf[i]);
    }
    printf("\n");
    */
    
    // int n = atoi("ok");
    // printf("%d\n",n);;
    /*char a = 'A';
    printf("%d\n",a);
    printf("%c\n",a);
    */

return 0
}


//ce main ne marche pas, l'idée est de revenir aux fonctions récursives

int main(){
    FILE *f = fopen("word.aut", "r");
   
    int n = nb_of_states(f); //Le nombre d'état de l'automate

    //Permet de se saisir de l'entrée standart
    char buf[256];
    fgets(buf,  256,stdin);
    sscanf(buf,"%s");

    //Création de la pile d'état 
    stack s= new();
    push(0,&s); // la pile contient Q0 (équivaut a l'état 0)
    
    //l'ordre d'appel des Matrices ci dessous est fondamentale pour être cohérent sur l'emplacement des curseurs (d'après mon implémentation)
    Matrix A_m = actions_matrix(f, n);
    Matrix R_m = reduit_matrix(f, n);
    Matrix D_m = decale_matrix(f, n);
    Matrix B_m = branchement_matrix(f, n);

    int k=0; // permet d'avancer dans l'entrée standart
    int current_state=0; //L'état en cours, ici 0 car l'état initiale est Q0 = 0
    int current_letter = buf[k]; //première lettre de l'entrée standart    

    // int act=A_m[current_state][current_letter]; // act = action(0,0) : action de la lettre initiale pour l'état 0
    int act =0;
    int nb_of_unstacking, A; //Pour la fonction Réduit : nombre de dépilement et A

    // int next_letter_stdin(current_letter,current_state){ // Fonction récursive 
    /*    
        
        printf("%d\n",act);
    */
    // while(current_letter!=10)
    for(int i=0;i<5;i++){ //signifie un retour à la ligne de l'entrée standart 
        act=A_m[current_state][current_letter];
        switch (act)
        {
        case 0: // Rejected 
            printf("Rejected\n");
            printf("l'erreur s'est produit à la lettre %i",k); 
            return 1;
            break;

        case 1: // Accepted 
            printf("Accepted\n");
            return 0;
            break;

        case 2: // Décale
            current_state = D_m[current_state][current_letter]; //s' = decale(s,c)
            push(current_state,&s); // on empile s'
            k++;
            current_letter=buf[k]; // on avance dans l'entrée
            // act=A_m[current_state][current_letter]; //dèjà fait après le while 
            printf("décale : current letter %i, l'état %i et l'action %i\n",current_letter,current_state,act);
            break;
        
        case 3: //Réduit
            nb_of_unstacking = R_m[0][current_state]; //nopmbre de dépilement
            A = R_m[1][current_state];// Même notation que l'énoncé

            for(int i=0; i<nb_of_unstacking-1 ;i++){ // on dépile nb_of_stacking-1 car on veut la valeur du dernier depilement  
                pop(&s);
            }
            current_state=pop(&s); // valeur du dernier dépilement, l'état courant est s'

            push(B_m[current_state][A],&s);// on empile Branchement(s',A)=s
            printf("décale : current letter %i, l'état %i et l'action %i\n",current_letter,current_state,act);

        default:
            printf("Le fichier .aut contient des erreurs\n");
            return 1;
            break;
        }
    }
    fclose(f);

    return 0;
}
 

/*
ce Réduit de main ne fonctionne que pour word.aut , il y a un problème dans la pile 

case 3: //Réduit
            nb_of_unstacking = R_m[0][current_state]; //nopmbre de dépilement
            A = R_m[1][current_state];// Même notation que l'énoncé
            // if (nb_of_unstacking!=0){ // pour eviter le for(0;-1;++)
                for(int i=0; i<nb_of_unstacking-1 ;i++){ // on dépile nb_of_stacking-1 car on veut la valeur du dernier depilement  
                    pop(&s);
                }
                current_state=pop(&s); // valeur du dernier dépilement, l'état courant est s'
            /*    
                push(B_m[current_state][A],&s);// on empile Branchement(s',A)=s
            }
            else{
                push(B_m[current_state][A],&s);// on empile Branchement(s,A)
            }
            */
            //push(B_m[current_state][A],&s);// on empile Branchement(s',A)=s
            printf("réduit : current letter %i, l'état %i\n",current_letter,current_state);
            printf("la pile est donc : \n");
            print_stack(&s);
*/

            /*
            switch (nb_of_unstacking)
            {
            case 0:
                push(B_m[current_state][A],&s);// on empile Branchement(s,A)
                break;
            case 1: 
                current_state = pop(&s); //on stocke s'
                push(B_m[current_state][A],&s);// on empile Branchement(s',A)=s
                break;
            default:
                for(int i=0; i<nb_of_unstacking-2 ;i++){ // on dépile nb_of_stacking-2 pour stocker le dernier dépilement dans un current_state en dehors de la boucle
                    pop(&s);
                }
                current_state = pop(&s); //on stocke s'
                push(B_m[current_state][A],&s);// on empile Branchement(s',A)=s
                break;
            }
            
            */


// Réduit qui Fonctionne ! 
            
          /*  
            nb_of_unstacking = R_m[0][current_state]; //nopmbre de dépilement
            A = R_m[1][current_state];// Même notation que l'énoncé
            
            for(int i=0; i<nb_of_unstacking ;i++){ // A CORRIGER : on dépile nb_of_stacking-1 pour stocker le dernier dépilement dans un current_state en dehors de la boucle
                pop(&s);
            }

            print_stack(&s);
            // printf("length vaut %i\n\n",s.length); // C'est correcte
            // current_state=pop(&s); // on stock s' qui est le sommet de la pile dépillée 
            current_state=s.content[s.length]; 
            printf("curent_state avant branchement vaut : %i \n", current_state);
            // push(current_state,&s);
            // print_stack(&s);
            
            printf("Branchement vaut : %i avec A : %i \n\n ", B_m[current_state][A],A);
            push(B_m[current_state][A],&s);// on empile Branchement(s',A)=s
            current_state=s.content[s.length]; // NE SURTOUT PAS OUBLIER CETTE LIGNE ! sinon boucle infinie
            printf("curent_state à la fin de réduit vaut : %i \n", current_state);

            printf("réduit : current letter %i, l'état %i\n",current_letter,current_state);
            printf("la pile est donc : \n");
            print_stack(&s);
            break;
*/

/*
07/01/2022

ne fonctionne pas pour arith.aut car 30 est codé sur 2 octets

int nb_of_states(FILE *f){
    int e; // le nombre d'états de l'automate.
    if(f == NULL)
        exit(1);
    fscanf(f,"a %d\n",&e); // on ne veut que la valeur int et pas a.
    return e; 
}
*/



//Real main 

//MAIN OPERATIONNEL

int main(int argc, char *argv[]){
    FILE *f = fopen(argv[1], "r");// word.aut word_bis.aut  dyck.aut  arith.aut
   printf("File %s correctly read. Please enter your inputs.\n",argv[1]);
    int n = nb_of_states(f); //Le nombre d'état de l'automate
    //Permet de se saisir de l'entrée standart
    char buf[256];
    fgets(buf,  256,stdin);
    sscanf(buf,"%s");
    printf("Il y a %i états dans l'automate\n\n",n);
    //Création de la pile d'état 
    stack s= new();
    push(0,&s); // la pile contient Q0 (équivaut a l'état 0)
    
    //l'ordre d'appel des Matrices ci dessous est fondamentale pour être cohérent sur l'emplacement des curseurs (d'après mon implémentation)
    Matrix A_m = actions_matrix(f, n);
    Matrix R_m = reduit_matrix(f, n);
    Matrix D_m = decale_matrix(f, n);
    Matrix B_m = branchement_matrix(f, n);
    print_Matrix(A_m,n , 128); 
    printf("\n");

    int k=0; // permet d'avancer dans l'entrée standart
    int current_state=0; //L'état en cours, ici 0 car l'état initiale est Q0 = 0
    int current_letter = buf[k]; //première lettre de l'entrée standart    

    // int act=A_m[current_state][current_letter]; // act = action(0,0) : action de la lettre initiale pour l'état 0
    int act = 0;
    int nb_of_unstacking, A; //Pour la fonction Réduit : nombre de dépilement et A
    int stop_condition;

    print_stack(&s); //pile du début 
    while(stop_condition!=1){
        act=A_m[current_state][current_letter];
        // printf("l'action est désormais %i avec l'état %i \n",act, current_state);
        switch (act)
        {
        case 0: // Rejected 
            printf("Rejected\n");
            printf("the error occurred to the letter %i\n",k+1); //k+1 et non k car la première lettre de l'entrée est d'indice 0 
            stop_condition=1;
            break;

        case 1: // Accepted 
            printf("Accepted\n");
            stop_condition=1;
            break;

        case 2: // Décale
            current_state = D_m[current_state][current_letter]; //s' = decale(s,c)
            push(current_state,&s); // on empile s'
            k++;
            current_letter=buf[k]; // on avance dans l'entrée
            // act=A_m[current_state][current_letter]; //dèjà fait après le while 
            printf("décale : current letter %i, l'état %i\n",current_letter,current_state);
            printf("la pile après décale vaut donc : \n");
            print_stack(&s);
            break;
        
        case 3: //Réduit
            nb_of_unstacking = R_m[0][current_state]; //nombre de dépilement
            A = R_m[1][current_state];// Même notation que l'énoncé
            //printf("le nombre de dépilement vaut : %i\n",nb_of_unstacking);
            //printf("curent_state au début de réduit vaut : %i \n", current_state);

            for(int i=0; i<nb_of_unstacking ;i++){ // A CORRIGER : on dépile nb_of_stacking-1 pour stocker le dernier dépilement dans un current_state en dehors de la boucle
                pop(&s);
            }

            // print_stack(&s);
            // printf("length vaut %i\n\n",s.length); // C'est correcte
            // current_state=pop(&s); // on stock s' qui est le sommet de la pile dépillée 
            current_state=s.content[s.length]; 
            printf("curent_state avant branchement vaut : %i \n", current_state);
            // push(current_state,&s);
            // print_stack(&s);
            
            printf("Branchement vaut : %i avec A : %i \n\n ", B_m[current_state][A],A);
            push(B_m[current_state][A],&s);// on empile Branchement(s',A)=s
            current_state=s.content[s.length]; // NE SURTOUT PAS OUBLIER CETTE LIGNE ! sinon boucle infinie
            printf("curent_state à la fin de réduit vaut : %i \n", current_state);

            printf("à la fin de réduit : current letter %i, l'état %i\n",current_letter,current_state);
            printf("la pile à la fin de réduit est donc : \n");
            print_stack(&s);
            printf("find de réduit \n\n\n");
            break;

        default:
            printf("Le fichier .aut contient des erreurs\n");
            stop_condition=1;
            break;
        }
    }
    fclose(f);
    return 0;
}
 