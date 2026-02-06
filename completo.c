//SAMUELE FRANCESE 939848
//GESTIONE ANALISI DI LABORATORIO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_CODE 20

enum priority {LOW, MEDIUM , HIGH};

struct analysis {

    enum priority prio;
    int duration;
    char lab_zone[LEN_CODE];

};

struct item {

    int id_smp;
    struct item *next; 

};

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Errore parametri");
        return 1;
    }

    int k = atoi(argv[1]);

    if(k < 6 || k > 60){
        printf("Errore parametri");
        return 1;
    }
    
    int refDuration; 
    int targetPriority;

    do{
        printf("inserisci refDuration: ");
        scanf("%d" , &refDuration);
        if(refDuration < 0 || refDuration > 100){
           printf("Input errato figlio di troia");
           return 1;
        }
    }while(refDuration < 0 || refDuration > 100);


    do{
        printf("inserisci targetPriority: ");
        scanf("%d" , &targetPriority);
        if(targetPriority < 0 || targetPriority > 100){
           printf("Input errato figlio di troia");
           return 1;
        }
    }while(targetPriority < 0 || targetPriority > 2);

    struct analysis *array = malloc(k * sizeof(int));
    if(array == NULL){
        printf("memoria esaurita");
        return 1;
    } 

    for(int i = 0 ; i < k ; i++){

        int inHours;
        scanf("%d" , &inHours);

        if(inHours < 0 || inHours > 100 ){
            printf("input errato \n ");
            free(array);
            return 1;
        }

        array[i].duration = inHours;
        
        // classificazione delle priorità

        if(array[i].duration < 5){
            array[i].prio = LOW; 
        }
        else if (array[i].duration <= 20) {
            array[i].prio = MEDIUM;
        }
        else {
            array[i].prio = HIGH;
        }

        switch ( i % 4 ){ 
            case 0 :
                strcpy(array[i].lab_zone, "ZONA_A"); //strcpy metti l'array
                break;
            case 1:
                strcpy(array[i].lab_zone, "ZONA_B");
                break;
            case 2:
                strcpy(array[i].lab_zone, "ZONA_C");
                break;
            case 3: 
                strcpy(array[i].lab_zone, "ZONA_D");
                break;
        }
    

    struct item *head = NULL ; //inzializzo 

    for(int i = 0 ; i < k ; i ++){
        if(array[i].duration > refDuration){
            head = append_
        }
    }
    }
    return 0;
}