#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){
    int n,m,k;
    

    printf("=== ESERCIZI : malloc , calloc , realloc === \n");
    printf("inserisci dimensione iniziale array A[n]: ");
    scanf("%d", &n );

    //allocazione in memoria con malloc
    int *A = malloc(n * sizeof(int));
    if(A == NULL){
        printf("errore memoria piena \n");
        return 1;
    }

    //inserimento dinamico array A
    printf("inserisci i %d valori per l'array A \n");
    for(int i = 0 ; i < n ; i++){
        printf("A[%d] = ", i);
        scanf("%d", &A[i]);
    }
    printf("\n\n");

    //parte 3 e 4 : allocazione array B con calloc

    printf("inserisci dimensione iniziale array B[m]: ");
    scanf("%d" , &m);

    //allocazione con calloc (full inizializzata)
    int *B = calloc(m , sizeof(int)); //attenzione virgola e non per
    if(B == NULL){
        printf("Erroe : memoria insufficiente \n");
        free(A);
        return 1;
    }

    //stampa array a inizializzato grazie al calloc
    printf("\n ARRAY INIZIALIZZATO (CALLOC) : ");
    for(int i = 0 ; i < m ; i++){
        printf("%d" , B[i]);
    }
    printf("\n");

    //input valori su alcune delle posizioni dell'array
    printf("\n inserisci valori su B a caso (digita -1 per terminare )\n");

    int pos; //come riferimento faccio 2 variabili momentanee!!!
    int val;

    while(1){
        printf("posizione : (-1 per terminare) ");
        scanf("%d" , &pos);

        if(pos == -1) break;

        if(pos < 0 || pos >= m ){
            printf("posizione non valida");
            continue;
        }

        printf("valore : ");
        scanf("%d" , &val);
        B[pos] = val;
    }

    //stampa array modificato

    printf("\n array B modificato: ");
    for(int i = 0 ; i < m ; i++ ){
        printf("%d" , B[i]);

    }
    printf("\n\n");


    //parte 5 e 6 ridimensionamento array
    int k;
    printf("inserisci nuova dimensione : ");
    scanf("%d" , &k);
    
    *A = realloc(A , k * sizeof(int));
    if(A == NULL){
        printf("ERRORE : memoria insufficiente");
        free(B);
    }




    return 0; 
}