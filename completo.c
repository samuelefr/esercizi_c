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

struct item { // creazione di come deve essere fatto ogni nodo

    int id_smp;  // il dato
    struct item *next;  //puntatore al prossimo nodo

};


// FUNZIONI ESTREMAMENTE IMPORTANTI DA SAPERE

//1) CREARE NUOVO NODO DELLA LISTA IN CIMA

struct item *new_item(int id_smp , struct item *next){
    // chiediamo memoria per un nodo
    struct item *nuovo = malloc(sizeof(struct item));

    //controllo obbligatorio della memoria
    if(nuovo == NULL){
        printf("memoria esaurita");
        exit(1); // uscita forzata mi raccomando non usare return perche siamo in una funzione struct
    }
    // riempiamo i campi del nodo
    nuovo->id_smp = id_smp;
    nuovo->next = next; // colleghiamo a quello successivo o a null

    return nuovo; // restituiamo l'indirizzo del nuovo nodo
}   

//2) INSERISCE UN NODO IN FONDO ALLA LISTA E RITORNA LA NUOVA TESTA

struct item *append_to_list(int id_smp , struct item *head){
    // se la lista e' vuota diventa la testa
    if(head == NULL ){
        return new_item(id_smp,NULL);
    }
    //altrimenti dobbiamo scorrere la lista fino alla fine
    struct item *corrente = head; // partiamo dalla testa
    while(corrente->next != NULL ){
        corrente = corrente->next; //mi sposto avanti
    }
    //ora "corrente" e' l'ultimo nodo . attacchiamo quello nuovo dopo di lui
    corrente->next = new_item(id_smp, NULL);

    return head; //la testa non cambia mai se la lista non era vuota

}

//3) CONTA QUANTI CAMPIONI HANNO DURATA STRETTAMENTE MAGGIORE DI MIN_VAL
int count_longer_than(struct analysis array[], int k , int min_val){
    int contatore = 0;
    for(int i = 0 ; i < k ; i++ ){
        if(array[i].duration > min_val){
            contatore++;
        }
    }
    return contatore;
}

//4) CALCOLA LA DURATA MEDIA DEI CAMPIONI CHE APPARTENGONO ALLA CATEGORIA "T"
//   RITORNA 0 SE NON CI SONO CAMPIONI DI QUEL TIPO
double avg_duration_by_type(struct analysis array[] , int k , enum priority t){ 
    double somma = 0 ;
    int trovati = 0 ;

    for(int i = 0 ; i < k ; i++){
        if(array[i].prio == t){
            somma += array[i].duration;
            trovati++;
        }
    }

    // se non abbiamo trovato campioni di quel tipo ritorniamo 0
    if(trovati == 0){
    return 0.0 ; 
    }
    return somma / trovati;
}

//5) DEALLOCA L'INTERA LISTA
void clear_list(struct item *head){
    struct item *temp;
    while (head != NULL) {
        temp = head; //salviamo il nodo attuale in una variabile temporanea
        head = head -> next; //spostiamo la testa al prossima
        free(temp); //liberiamo il nodo salvato, cosi libera tutto
    } 
}

//--main--

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
    
    int refDuration , targetPriority;

    do{
        printf("inserisci refDuration: ");
        scanf("%d" , &refDuration);
        if(refDuration < 0 || refDuration > 100){
           printf("Input errato");
           return 1;
        }
    }while(refDuration < 0 || refDuration > 100);


    do{
        printf("inserisci targetPriority: ");
        scanf("%d" , &targetPriority);
        if(targetPriority < 0 || targetPriority > 100){
           printf("Input errato");
           return 1;
        }
    }while(targetPriority < 0 || targetPriority > 2);

    struct analysis *array = malloc(k * sizeof(struct analysis));
    if(array == NULL){
        printf("memoria esaurita \n");
        return 1;
    } 
    //acquisizione dati campioni
    for(int i = 0 ; i < k ; i++) {
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

        // assegnazione zona 
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
    } 
// costruzione della lista (filtro)
    struct item *head = NULL ; //inzializzo 
    for(int i = 0 ; i < k ; i ++){
        if(array[i].duration > refDuration){ //se duration e' strettamente maggiore di ref
            head = append_to_list(head ,i);
        }
    }
    // MENU OPERATIVO
    int cmd;
    scanf("%d",&cmd);
    
    return 0;
}


