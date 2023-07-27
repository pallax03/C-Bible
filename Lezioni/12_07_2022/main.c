#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Cella {
    struct Cella *next;
    char carattere; //inserisco le variabili che voglio usare
};

struct Cella* creaElemento();
void inserisciElemento(struct Cella **testa, struct Cella *nuovo);
void eliminaElemento(struct Cella **testa);
void stampaLista(struct Cella **testa);

int main() {
    struct Cella *testa;
    testa=NULL;

    struct Cella *nuovo;
    nuovo = creaElemento();
    inserisciElemento(&testa, nuovo);
    
    //ripetere questa istruzione per aggiungere un nnuovo elemento alla lista
    nuovo = creaElemento();


    return 0;
}

void stampaLista(struct Cella *testa) { //perchè si vuole usare la variabile locale nel main quindi la testa va puntata 
    struct Cella *tmp;
    tmp = testa;
    while (tmp != NULL) //fino a che l'elemento successivo non è nullo
    {
        //scorre tutta la lista
        tmp = tmp->next; //va a quello successivo
    }

}

void eliminaElemento(struct Cella **testa) { //perchè si vuole usare la variabile locale nel main quindi la testa va puntata 
    if(*testa==NULL) //se la lista è già alla fine non elimina nulla
        return;
    
    struct Cella *tmp = *testa;
    *testa = tmp->next;
    tmp->next = NULL; //programmazione preventiva
    free(tmp);
}

void inserisciElemento(struct Cella **testa, struct Cella *nuovo) { //perchè si vuole usare la variabile locale nel main quindi la testa va puntata 
    nuovo->next=*testa; //questo non ha senso
    *testa = nuovo;
}

struct Cella* creaElemento() {
    struct Cella *nuovo;

    //creo nuovo elemento
    nuovo = malloc(sizeof(struct Cella));
    if (nuovo == NULL) {
        exit(1);
    }
    nuovo->next=NULL; //programmazione preventiva
}