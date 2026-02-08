// SAMUELE FRANCESE 939848
// GESTIONE ANALISI DI LABORATORIO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_CODE 20

// Definizione enum per le priorità
enum priority {
    LOW = 0,
    MEDIUM = 1,
    HIGH = 2
};

// Struttura per un singolo campione
struct analysis {
    enum priority prio;
    int duration;
    char lab_zone[LEN_CODE];
};

// Struttura per un nodo della lista
struct item {
    int id_smp;
    struct item *next;
};

// ========== FUNZIONI ==========

// Crea un nuovo nodo della lista
struct item *new_item(int id_smp, struct item *next) {
    struct item *nuovo = malloc(sizeof(struct item));
    
    if (nuovo == NULL) {
        printf("Memoria esaurita\n");
        exit(1);
    }
    
    nuovo->id_smp = id_smp;
    nuovo->next = next;
    
    return nuovo;
}

// Inserisce un nodo in fondo alla lista
struct item *append_to_list(struct item *head, int id_smp) {
    // Lista vuota: il nuovo nodo diventa la testa
    if (head == NULL) {
        return new_item(id_smp, NULL);
    }
    
    // Scorro fino all'ultimo nodo
    struct item *corrente = head;
    while (corrente->next != NULL) {
        corrente = corrente->next;
    }
    
    // Aggiungo il nuovo nodo in coda
    corrente->next = new_item(id_smp, NULL);
    
    return head;
}

// Conta campioni con durata > min_val
int count_longer_than(struct analysis A[], int k, int min_val) {
    int contatore = 0;
    
    for (int i = 0; i < k; i++) {
        if (A[i].duration > min_val) {
            contatore++;
        }
    }
    
    return contatore;
}

// Calcola la media delle durate per una categoria
double avg_duration_by_type(struct analysis A[], int k, enum priority t) {
    double somma = 0;
    int trovati = 0;
    
    for (int i = 0; i < k; i++) {
        if (A[i].prio == t) {
            somma += A[i].duration;
            trovati++;
        }
    }
    
    if (trovati == 0) {
        return 0.0;
    }
    
    return somma / trovati;
}

// Dealloca tutta la lista
void clear_list(struct item *head) {
    struct item *temp;
    
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// ========== MAIN ==========

int main(int argc, char *argv[]) {
    
    // 1) CONTROLLO PARAMETRI DA LINEA DI COMANDO
    if (argc != 2) {
        printf("Errore parametri\n");
        return 1;
    }
    
    int k = atoi(argv[1]);
    
    if (k < 6 || k > 60) {
        printf("Errore parametri\n");
        return 1;
    }
    
    // 2) LETTURA PARAMETRI DI CONTROLLO
    int refDuration, targetPriority;
    
    if (scanf("%d", &refDuration) != 1 || refDuration < 0 || refDuration > 100) {
        printf("Input errato\n");
        return 1;
    }
    
    if (scanf("%d", &targetPriority) != 1 || targetPriority < 0 || targetPriority > 2) {
        printf("Input errato\n");
        return 1;
    }
    
    // 3) ALLOCAZIONE ARRAY
    struct analysis *array = malloc(k * sizeof(struct analysis));
    
    if (array == NULL) {
        printf("Memoria esaurita\n");
        return 1;
    }
    
    // 4) LETTURA DATI CAMPIONI
    for (int i = 0; i < k; i++) {
        int inHours;
        
        if (scanf("%d", &inHours) != 1 || inHours < 0 || inHours > 100) {
            printf("Input errato\n");
            free(array);
            return 1;
        }
        
        // Salvo la durata
        array[i].duration = inHours;
        
        // Classifico la priorità
        if (inHours < 5) {
            array[i].prio = LOW;
        } else if (inHours <= 20) {
            array[i].prio = MEDIUM;
        } else {
            array[i].prio = HIGH;
        }
        
        // Assegno la zona in base a i % 4
        switch (i % 4) {
            case 0:
                strcpy(array[i].lab_zone, "ZONA_A");
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
    
    // 5) COSTRUZIONE LISTA (FILTRO)
    struct item *head = NULL;
    
    for (int i = 0; i < k; i++) {
        if (array[i].duration > refDuration) {
            head = append_to_list(head, i);
        }
    }
    
    // 6) MENU OPERATIVO
    int cmd;
    
    while (1) {
        if (scanf("%d", &cmd) != 1) {
            break;  // Esco se l'input fallisce
        }
        
        if (cmd == 0 || cmd == 1) {
            break;  // Esco se ricevo 0 o 1
        }
        
        switch (cmd) {
            case 4:
                printf("OVER_REF:");
                if (head == NULL) {
                    printf(" none\n");
                } else {
                    struct item *curr = head;
                    while (curr != NULL) {
                        printf(" %d", curr->id_smp);
                        curr = curr->next;
                    }
                    printf("\n");
                }
                break;
                
            case 7:
                printf("COUNT_LONGER %d\n", count_longer_than(array, k, refDuration));
                break;
                
            case 8:
                printf("AVG_CAT %d: %.2f\n", targetPriority, 
                       avg_duration_by_type(array, k, (enum priority)targetPriority));
                break;
                
            default:
                // Altri comandi: non faccio nulla
                break;
        }
    }
    
    // 7) PULIZIA FINALE
    clear_list(head);
    free(array);
    printf("Chiusura\n");
    
    return 0;
}