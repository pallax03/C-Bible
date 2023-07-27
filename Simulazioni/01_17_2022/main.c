#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VOTI 5

struct struct_studente{
    char nome[10+1];
    char cognome[20+1];
    char matricola[6+1];
    unsigned int voti[MAX_VOTI];
    float media;

    struct struct_studente *next;
};

struct Corso
{
    char id_corso[10+1];
    char descrione[100+1];

    struct struct_studente *lp; //lista positivi, sono presenti gli studenti la cui media dei voti e'  >= 18
    struct struct_studente *ln; //lista negativi, sono presenti gli studenti la cui media dei voti e'  <  18
    struct struct_studente *lt; //lista tutti
};

struct struct_studente * appendNode(struct struct_studente *list, struct struct_studente *s) {
    if(list==NULL) return s; //if(!list) vuol dire list == null
    list->next = appendNode(list->next, s);
    return list;
}

void inserisci_coda_lista(struct Corso *corso, char nome[], char cognome[], char matricola[], unsigned int voti[]);

int main() {
    struct Corso *corso = malloc(sizeof(struct Corso));
    
    corso->lp = NULL;
    corso->ln = NULL;
    corso->lt = NULL;

    int voti[MAX_VOTI] = {18,22,30,22,10};
    inserisci_coda_lista(corso, "alex", "mazzoni", "000001", voti);
    inserisci_coda_lista(corso, "mattia", "bertozzi", "000002", voti);
    inserisci_coda_lista(corso, "michele", "farneti", "000003", voti);
    inserisci_coda_lista(corso, "christian", "luca", "000004", voti);


    printf("%s", corso->lp->cognome);
    printf("%s", corso->lp->next->cognome);

    return 0;
}

void inserisci_coda_lista(struct Corso *corso, char nome[], char cognome[], char matricola[], unsigned int voti[]) {
    struct struct_studente *s = malloc(sizeof(struct struct_studente));
    strcpy(s->nome, nome);
    strcpy(s->cognome, cognome);
    strcpy(s->matricola, matricola);

    int somma=0;
    int i=0;
    for (i = 0; i < MAX_VOTI; i++) {
        s->voti[i] = voti[i];
        somma += s->voti[i];
    }
    s->media = (float) somma / i;
    
    if(s->media >= 18)  corso->lp = appendNode(corso->lp, s);   //aggiungi in lista positivi
    else                corso->ln = appendNode(corso->ln, s);   //aggiungi in lista negativi

}

struct struct_studente * crea_unica_lista(struct Corso *corso) {
struct struct_studente *lt = appendNode(corso->lp, corso->ln);
corso->lp = corso->ln = 0;
return lt;
}
