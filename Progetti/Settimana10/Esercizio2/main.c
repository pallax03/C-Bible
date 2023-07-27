#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

//pila
//la pila ADT di tipo LiFo(Last In First Out), cioe' l'ultimo elemento inserito sara' il primo ad essere estratto (per estratto si intende la funzione pop).
#define MAX 4           // [0,3] = 4 elementi massimi

//VettoreStatico: ---------------------------------------------------------------------------------------------
//variabili:
int testaStatica = 0;
int pilaStatica[MAX];

//funzioni:
void pushStatico();    //aggiunge un elemento alla pila.
void popStatico();     //visualizza e scarta l'ultimo elemento della pila.
void printStatico();   //stampa tutti gli elementi della pila (solo visualizzare).
void resetStatico();   //azzera la pila.
//-------------------------------------------------------------------------------------------------------------

//VettoreDinamico: --------------------------------------------------------------------------------------------
//variabili:
int testaDinamica = 0;
int *pilaDinamica;

//funzioni:
void pushDinamico();    //aggiunge un elemento alla pila.
void popDinamico();     //visualizza e scarta l'ultimo elemento della pila.
void printDinamico();   //stampa tutti gli elementi della pila (solo visualizzare).
void resetDinamico();   //azzera la pila.
//-------------------------------------------------------------------------------------------------------------

//ListaIndicizzata: -------------------------------------------------------------------------------------------
//variabili:
struct Node {
    struct Node *next;
    int valore;
};
struct Node *head;

//funzioni:
void pushIndicizzato();    //aggiunge un elemento alla pila.
void popIndicizzato();     //visualizza e scarta l'ultimo elemento della pila.
void printIndicizzato();   //stampa tutti gli elementi della pila (solo visualizzare).
void resetIndicizzato();   //azzera la pila.
//-------------------------------------------------------------------------------------------------------------

int main() {
    /*Gruppo:
    Matricola:  Alex Mazzoni       E-mail: alex.mazzoni3@studio.unibo.it
    Matricola:  Giovanni Luca      E-mail: giovanni.luca@studio.unibo.it
    Matricola:  Michele Farneti    E-mail: michele.farneti@studio.unibo.it
    */

    printf("\nSettimana 10 - Esercizio 2\t E-mail di riferimento: alex.mazzoni3@studio.unibo.it\n\n");

    //menu di inserimento
    int scelta = 0, tipo = 0;
    do {
        printf("\nTipo di pila: \n");
        printf("\t1. Vettore Statico.\n");
        printf("\t2. Vettore Dinamico.\n");
        printf("\t3. Lista Indicizzata.\n");
        printf("\nquale tipo di pila si vuole: ");
        scanf("%d", &tipo);

        //piccolo timer per far leggere ogni otput prima di cancellare lo schermo
        clock_t now = clock();
        for( ; clock() - now < 1 * CLOCKS_PER_SEC; ); 
        system("cls"); //pulisce lo schermo
    } while (tipo!=1 && tipo!=2 && tipo!=3);
    
    switch (tipo) {
        case 1:
            printf("\nHai selezionato pila a vettore statico!\n");
            break;
        case 2:
            printf("\nHai selezionato pila a vettore dinamico!\n");
            pilaDinamica = calloc(MAX, sizeof(int));
            break;
        case 3:
            printf("\nHai selezionato pila a lista indicizzata!\n");
            head = malloc(sizeof(struct Node));
            head = NULL;
            break;
    }

    //piccolo timer per far leggere ogni otput prima di cancellare lo schermo
    clock_t now = clock();
    for( ; clock() - now < 2 * CLOCKS_PER_SEC; ); 
    system("cls"); //pulisce lo schermo

    do { //solito menu che richiede una voce in input e finche' non si inserisce 0 si ripete
        printf("\nGestisci la pila: \n");
        printf("\t1. Aggiungi un elemento. push();\n");
        printf("\t2. Estrai un elemento. pop();\n");
        printf("\t3. Stampa la pila intera. print();\n");
        printf("\t4. Azzera la pila. reset();\n");
        printf("\t0. Termina il programma.\n");
        printf("\ndigiti il numero corrispondente alla voce interessata: ");
        scanf("%d", &scelta); 
        switch (scelta) {
            case 0:
                printf("\nArrivederci.");
                break;
            case 1:
                switch (tipo) {
                    case 1:
                        pushStatico();
                        break;
                    case 2:
                        pushDinamico();
                        break;
                    case 3:
                        pushIndicizzato();
                        break;
                }
                break;
            case 2:
                switch (tipo) {
                    case 1:
                        popStatico();
                        break;
                    case 2:
                        popDinamico();
                        break;
                    case 3:
                        popIndicizzato();
                        break;
                }
                break;
            case 3:
                switch (tipo) {
                    case 1:
                        printStatico();
                        break;
                    case 2:
                        printDinamico();
                        break;
                    case 3:
                        printIndicizzato();
                        break;
                }
                break;
            case 4:
                switch (tipo) {
                    case 1:
                        resetStatico();
                        break;
                    case 2:
                        resetDinamico();
                        break;
                    case 3:
                        resetIndicizzato();
                        break;
                }
                break; 
        }
        //piccolo timer per far leggere ogni otput prima di cancellare lo schermo
        clock_t now = clock();
        for( ; clock() - now < 2 * CLOCKS_PER_SEC; ); 
        system("cls"); //pulisce lo schermo

    }while (scelta!=0);
    return 0;   
}

// FUNZIONI PILA VETTORE STATICO -----------------------------------------------------------
//push  (aggiunge un elemento alla pila)
void pushStatico() {
    if(testaStatica==MAX) { //la pila e' piena e non e' possibile aggiungere nuovi elementi
        printf("la pila ha raggiunto il numero massimo di elementi (%d)!", testaStatica);
    }
    else {
        //aggiugno il nuovo elemento
        printf("inserire il valore del nuovo elemento: ");
        scanf("%d", &pilaStatica[testaStatica++]);
    }
}

//pop   (visualizza e scarta l'ultimo elemento della pila)
void popStatico() {
    if(testaStatica==0) { //la pila e' vuota
        printf("la pila non contiene nessun elemento.");
    }   
    else {   //e cosi facendo stampo e elimino l'ultimo elemento
        printf("%d", pilaStatica[--testaStatica]);
        //oppure
        // testaStatica--;
        // printf("%d", pilaStatica[testaStatica]);
    }
}

//print (stampa tutti gli elementi della pila)
void printStatico() {
    if(testaStatica==0) {
        printf("la pila non contiene nessun elemento.");
    }
    else {
        printf("\npila:");
        for (int i = testaStatica-1; i >= 0; i--) {
            printf("\n\tindice: %d, valore: %d", i, pilaStatica[i]);
        }
    }
}

//reset (azzera la pila)
void resetStatico() {
    testaStatica=0;
    printf("\n\tpila resettata.");
}
//-----------------------------------------------------------------------------------------

// FUNZIONI PILA VETTORE DINAMICO ---------------------------------------------------------
//push  (aggiunge un elemento alla pila)
void pushDinamico() {
    if(testaDinamica==MAX) { //la pila e' piena e non e' possibile aggiungere nuovi elementi
        printf("la pila ha raggiunto il numero massimo di elementi (%d)!", testaDinamica);
    }
    else {
        //aggiugno il nuovo elemento
        printf("inserire il valore del nuovo elemento: ");
        scanf("%d", &pilaDinamica[testaDinamica++]);
    }
}

//pop   (visualizza e scarta l'ultimo elemento della pila)
void popDinamico() {
    if(testaDinamica==0) { //la pila e' vuota
        printf("la pila non contiene nessun elemento.");
    }   
    else {   //e cosi facendo stampo e elimino l'ultimo elemento
        printf("%d", pilaDinamica[--testaDinamica]);
        //oppure
        // testaDinamica--;
        // printf("%d", pilaDinamica[testaDinamica]);
    }
}

//print (stampa tutti gli elementi della pila)
void printDinamico() {
    if(testaDinamica==0) {
        printf("la pila non contiene nessun elemento.");
    }
    else {
        printf("\npila:");
        for (int i = testaDinamica-1; i >= 0; i--) {
            printf("\n\tindice: %d, valore: %d", i, pilaDinamica[i]);
        }
    }
}

//reset (azzera la pila)
void resetDinamico() {
    testaDinamica = 0;
    printf("\n\tpila resettata.");
}
//------------------------------------------------------------------------------------------

// FUNZIONI PILA LISTA INDICIZZATA ---------------------------------------------------------
//push  (aggiunge un elemento alla pila)
void pushIndicizzato() {
    struct Node *new = malloc(sizeof(struct Node));
    if(new==NULL) { //la pila e' piena e non e' possibile aggiungere nuovi elementi
        printf("non e' possibile aggiungere un nuovo elemento nella pila");
    }
    else {
        //aggiugno il nuovo elemento
        printf("inserire il valore del nuovo elemento: ");
        scanf("%d", &new->valore);
        new->next = head;
        head = new;
    }
}

//pop   (visualizza e scarta l'ultimo elemento della pila)
void popIndicizzato() {
    if(head==NULL) {
        printf("la pila non contiene nessun elemento.");
    }
    else {
        printf("%d", head->valore);
        head = head->next;
    }
}

//print (stampa tutti gli elementi della pila)
void printIndicizzato() {
    if(head == NULL) {
        printf("la pila non contiene nessun elemento.");
    } 
    else {
        struct Node *tmp;
        tmp = head;
        int count = 0;
        while (tmp!=NULL) {tmp = tmp->next; count++;} //count the elements of the linked list
        
        tmp = head;
        printf("\npila:");
        while (tmp!=NULL) {
            count--;
            printf("\n\tindice: %d, valore: %d", count, tmp->valore);
            tmp = tmp->next;
        }
    }
}

//reset (azzera la pila)
void resetIndicizzato() {
    head = NULL;
    printf("\n\tpila resettata.");
}
//------------------------------------------------------------------------------------------