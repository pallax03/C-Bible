#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Queue //la coda e' un tipo di dato dove si usa come manipolazione degli elementi la modalita' FIFO (First In First Out).
    int value;

    struct Queue *next;
};

struct Queue * appendNode(struct Queue *list, struct Queue *node) { //aggiungi un nodo alla lista in maniera FIFO
    if(list == NULL) return node;
    list->next = appendNode(list->next, node);
    return list;
}

struct Queue * estractNode(struct Queue *list) { //estrai un nodo dalla lista
    if(!list) return NULL;
    return list->next;
}

void inserisci_voto_coda(struct Queue **head, int value);

int main() {
    struct Queue *head = NULL;

    inserisci_voto_coda(&head, 5);
    printf("%d", head->value);

    printf("\n");
    inserisci_voto_coda(&head, 10);
    printf("%d", head->next->value);
    printf("\n");

    inserisci_voto_coda(&head, 15);


    head = estractNode(head);
    printf("%d", head->value);
    printf("\n");
    printf("%d", head->next->value);

    return 0;
}

void inserisci_voto_coda(struct Queue **head, int value) {
    struct Queue *node = malloc(sizeof(struct Queue)); //crea il nodo
    node->next = NULL;      //quando inizializzo un nuovo nodo per non avere ambiguita' inizializzo a NULL il successivo

    //inserisce i dati all'interno del nodo
    node->value = value;    
    
    *head = appendNode(*head, node);  //aggiunge (collega) il nodo alla lista
}