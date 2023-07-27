#include <stdio.h>      //Funzioni di input / output
#include <stdlib.h>     //Funzioni che gestiscono la memoria (malloc)
#include <string.h>     //Funzioni per la gestione delle stringhe (strcpy, strcasecmp: case compare cioè compara le stringhe senza considerare il case sensitive)
#include <stdbool.h>     //Funzioni per aggiungere il tipo di dato bool utile nella funzione vittorie_giocatore_torneo

#define NOME_FILE "./partite.txt" //definisco il nome del file
#define MAX_IDPARTITA 12     //11 caratteri utili + 1 per il terminatore '\0'
#define MAX_NOME 21          //20 caratteri utili per il nome + 1 per il terminatore
#define NSET 3               //numero dei set (dimensione vettore di interi che contiene i risultati)


struct Partita
{
    char id_partita[MAX_IDPARTITA];
    char gioc1[MAX_NOME];
    char gioc2[MAX_NOME];
    int ris1[NSET];    //vettore di 3 elementi contiene i punteggi di ogni set del giocatore1
    int ris2[NSET];    //vettore di 3 elementi contiene i punteggi di ogni set del giocatore2

    struct Partita *next; //puntatore al nodo successivo
};

struct Partita *lista_partite;  //la testa della lista è globale in modo che cosi tutte le funzioni vi possono accedervi e il suo tempo di vita è gestito dal programmatore

//funzioni: 
struct Partite * leggi_partite(char *file_path);
int stampa_partite(struct Partita *list, int count_lista);
int * vittorie_giocatore_torneo(struct Partita *lista_partite, char *gioc, char id_torneo[3]);
char * MVP_torneo(struct Partita *lista_partite, char id_torneo[3]);


int main() {
    lista_partite = NULL; //la inizializzo

    //richiamo tutte le funzioni memorizzando i parametri che restituiscono in variabili automatiche locali alla funzione main.
    lista_partite = leggi_partite(NOME_FILE);
    int conta_partite = stampa_partite(lista_partite, 0);       //anche qui c'era un errorino di distrazione
    int *partite_vinte_nel_torneo_e_percentuale_su_tutti_i_tornei = vittorie_giocatore_torneo(lista_partite, "Rossi", "Wim");
    char *giocatore_mvp_nel_torneo = MVP_torneo(lista_partite, "Wim");

    return 0; 
}

struct Partite * leggi_partite(char *file_path) {   // passato come argomento il perscorso del file crea la lista di partite, prendendo come input le variabili del file
    FILE *file;
    file = fopen(file_path, "r"); //apre il file con accesso di sola-lettura ("r").

    if(file != NULL) { //controlla se il file è stato aperto correttamente

        while (!feof(file)) {
            struct Partita *nuova_partita = malloc(sizeof(struct Partita));
            //memorizza le informazioni di una riga all'interno di una struttura Partita appena allocata

            fscanf(file, "%s %s %s %d %d %d %d %d %d", nuova_partita->id_partita, nuova_partita->id_partita, nuova_partita->id_partita, &nuova_partita->ris1[0], &nuova_partita->ris1[1], &nuova_partita->ris1[2], &nuova_partita->ris2[0], &nuova_partita->ris2[1], &nuova_partita->ris2[2]);


            struct Partita *tmp = lista_partite; //variabile temporanea per girare tutta la lista
            struct Partita *tmp_precedente = lista_partite; //variabile temporanea che memorizza l'elemento precedente.
            while (tmp != NULL) { //gira tutta la lista finchè il nodo é diverso da null
                //controllo quando posso aggiungere il nodo per formare una lista crescente per il campo id_partita.
                if(strcmp(nuova_partita->id_partita, tmp->id_partita)>0) { //se quello che è stato appena letto da file é maggiore dell'elemento della lista lo inserisce prima di quell'elemento
                    //collego il nuovo nodo (elemento) nella posizione prima del nodo tmp
                    nuova_partita->next = tmp;
                    tmp_precedente->next = nuova_partita;
                    break;          //quello che non mi ha fatto arrivare al 30
                }
                tmp_precedente = tmp; //memorizzo il nodo "attuale" come precedente
                tmp = tmp->next; //e il nodo "attuale" punterà a quello successivo
                //in questo modo si controlla il nodo successivo
            }
            
        }

        fclose(file);   //chiude il file
    }
    return lista_partite; //ritorno la testa della lista
}

int stampa_partite(struct Partita *list, int count_lista) { //funzione ricorsiva che stampa tutte le partite e il numero di partite stampate 
    if(list==NULL) return ; //potevo anche scrivere if(!list), quando è l'ultimo elemento interrompo la funzione qui
    
    count_lista = stampa_partite(list->next, count_lista); //richiama a sua volta la funzione ma dando l'elemento della lista successivo, e poi ritornerà la variabile che sta contando quante volte si è "richiamata"
    count_lista++; //incrementa la variabile
    
    //stampo le informazioni della partita
    printf("Partita: %s\n", list->id_partita);
    printf("Giocatore 1: %s\n\tpunteggio set 1: %d\n\tpunteggio set 2: %d\n\tpunteggio set 3: %d\n", list->gioc1, list->ris1[0], list->ris1[1], list->ris1[2]);
    printf("Giocatore 2: %s\n\tpunteggio set 1: %d\n\tpunteggio set 2: %d\n\tpunteggio set 3: %d\n\n", list->gioc1, list->ris1[0], list->ris1[1], list->ris1[2]);
    
    return count_lista; //restituisco la variabile incrementata 
}

//ho deciso di restituire un puntatore int, perchè sarà una variabile dinamica che conterrà il numero di partite vinte "[0]" e la percentuale di partite vinte "[1]"
int * vittorie_giocatore_torneo(struct Partita *lista_partite, char *gioc, char id_torneo[3]) { //prende come argomento la lista, l'identificativo del giocatore, e le prime 3 cifre della variabile id_partite
    int *partite_vinte = malloc(sizeof(int)*2); //restituisco in questo modo due interi perciò la percentuale viene calcolata e restituita come intero
    
    //serve per calcolare la percentuale
    int partite_totali = 0; //memorizza le partite totali che quel giocatore ha giocato, in TUTTI i tornei
    int partite_totali_vinte = 0; //memorizza il totale della partite che ha vinto quel giocatore passato come parametro, in TUTTI i tornei
    
    struct Partita *tmp = lista_partite; //giro tutta la lista delle partite
    while (tmp != NULL) {   //appena l'elemento è nullo esco dal blocco iterativo
        bool torneo_selezionato = false;    //flag per segnarsi se la partita che ha tmp, è del torneo passato come argomento
        int set_vinti=0;                    //alloca e inizializza un variabile che conta i set vinti

        if(strcasecmp(tmp->gioc1, gioc)==0) {   //controlla se la partita l'ha giocata come giocatore1, il giocatore passato come parametro   
            //qui ha giocato come giocatore 1
            if(strncasecmp(tmp->id_partita, id_torneo, 3)==0) torneo_selezionato = true; //controlla se la partita è del torneo richiesto
            
            for (int i = 0; i < NSET; i++) { //gira tutti i set
                if(tmp->ris1[i]>tmp->ris2[i]) { //confronta i punteggi
                    //il set [i] l'ha vinto il giocatore 1
                    set_vinti++; //conta quanti set ha vinto
                }
            }
            if(set_vinti>=2) {  //controlla se ha vinto la partita, se ha vinto 2 o più set ha vinto
                if(torneo_selezionato) partite_vinte[0]++; //incrementa la variabile che memorizza le partite in quel torneo vinte
                partite_totali_vinte++; //in ogni caso incrementa la variabile che conta quante partite ha vinto quel giocatore
            }
            partite_totali++;   //incrementa le partite totali che ha giocato in tutti i tornei
        }
        else if(strcasecmp(tmp->gioc2, gioc)==0) {  //controlla se la partita l'ha giocata come giocatore2, il giocatore passato come parametro
            //qui ha giocato come giocatore 2
            if(strncasecmp(tmp->id_partita, id_torneo, 3)==0) torneo_selezionato = true; //controlla se la partita è del torneo richiesto

            for (int i = 0; i < NSET; i++) { //gira tutti i set
                if(tmp->ris2[i]>tmp->ris1[i]) { //confronta i punteggi
                    //il set [i] l'ha vinto il giocatore 2
                    set_vinti++; //conta quanti set ha vinto
                }
            }
            if(set_vinti>=2) {  //controlla se ha vinto la partita, se ha vinto 2 o più set ha vinto la partita
                if(torneo_selezionato) partite_vinte[0]++; //incrementa la variabile che memorizza le partite in quel torneo richiesto, vinte
                partite_totali_vinte++; //in ogni caso incrementa la variabile che conta quante partite ha vinto quel giocatore
            }
            partite_totali++; //incrementa le partite totali che ha giocato in tutti i tornei
        }
        // se non entra in nessuno dei due if passa alla partita successiva

        tmp = tmp->next; //va al nodo successivo della lista
    }
    
    //calcola la percentuale sulle partite totali vinte in TUTTI i tornei 
    //partite_totali:100=partite_totali_vinte:x;
    partite_vinte[1] = (100 * partite_totali_vinte) / partite_totali; //essendo una divisione il risultato del calcolo è sicuramente un numero a virgola mobile, ma lo tratto come intero

    return partite_vinte; //restituisce il vettore di due elementi interi
}

char * MVP_torneo(struct Partita *lista_partite, char id_torneo[3]) { //preso come argomento la lista delle partite, e l'identificativo di un torneo (le prime 3 cifre dell'id_partita),
    char *giocatore = malloc(sizeof(char)*MAX_NOME); //restituisce il giocatore che ha vinto il numero maggiore di partite nel torneo passato come argomento.

    struct Partita *tmp_i = lista_partite; //gira tutta la lista di tmp_i
    int set_vinti_max = 0;
    while (tmp_i != NULL) {
        //controlla solo i tornei passati come argomento
        if(strncasecmp(tmp_i->id_partita, id_torneo, 3)==0) { //confronta le prime 3, potevo usare anche un sizeof per il 3 o anche una define
            struct Partita *tmp_j = tmp_i->next; //gira tutta la lista tmp_j
            int set_vinti = 0; //conta i set che ha vinto quel giocatore nei tornei (temporaneo)
            char giocatore_tmp[MAX_NOME]; //si segna il nome del giocatore con più set (temporaneo)
            while (tmp_j != NULL) { 
                if(strncasecmp(tmp_i->id_partita, id_torneo, 3)==0) { //mi controlla solo le partite di quel torneo richiesto
                    if(strcasecmp(tmp_i->gioc1, tmp_j->gioc1)==0) { //se ha giocato come giocatore 1
                        for (int i = 0; i < NSET; i++) { //gira tutti i set, confrontando tutti i punteggi
                            if(tmp_j->ris1[i]>tmp_j->ris2[i]) { //incrementa i set se quel giocatore ha vinto il set confrontando i punteggi
                                set_vinti++;    
                                strcpy(giocatore_tmp, tmp_j->gioc1);    //e memorizza il nome identificativo del giocatore
                            } 
                        }
                    }
                    else if(strcasecmp(tmp_i->gioc2, tmp_j->gioc2)==0) { //se ha giocato come giocatore 2
                        for (int i = 0; i < NSET; i++) {
                            if(tmp_j->ris2[i]>tmp_j->ris1[i]) { //incrementa i set se quel giocatore ha vinto il set confrontando i punteggi
                                set_vinti++;
                                strcpy(giocatore_tmp, tmp_j->gioc2);    //e memorizza il nome identificativo del giocatore
                            } 
                        }        
                    }
                }
                tmp_j = tmp_j->next; //passa alla partita successiva nella "seconda" lista
            }
            if(set_vinti_max<set_vinti) { //si segna che il giocatore mvp è il giocatore che ha contato con più set
                set_vinti_max = set_vinti; //aggiorna la variabile max in modo che possa confrontarla con i giocatori che hanno vinto più set di quello max fino ad ora
                strcpy(giocatore, giocatore_tmp);
            }
            tmp_i = tmp_i->next;   //passa alla partita successiva nella "prima" lista 
        }
    }

    return giocatore; //ritorna il nome identificativo del giocatore MVP
}