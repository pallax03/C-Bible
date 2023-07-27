#include <stdio.h>  // gestione diinput / ouput
#include <stdlib.h> // gestione della memoria
#include <string.h> // gestione delle stringhe
#include <math.h>   // funzioni per alcuni calcoli

#define MAX_STRING 21 //20 caratteri utili + 1 per il terminatore

#define MAX_PRODOTTO_LISTINO 100 // righe della tabella listino


struct supermercato
{
    char codice_supermercato[MAX_STRING];
    
    struct prodotto *lista_prodotti;

    struct supermercato *next;
};

struct prodotto
{
    char codice_prodotto[MAX_STRING];
    char codice_fornitore[MAX_STRING];
    unsigned int quantita_presente;

    struct prodotto *next;
};


struct listino
{
    char codice_prodotto[MAX_STRING];
    char codice_fornitore[MAX_STRING];
    double prezzo_unitario;
    unsigned int quantita_minima; //deve essere presente in ogni supermercato
};

//tabella listino
struct listino tabella[MAX_PRODOTTO_LISTINO]; //e' la tabella con righe ordinate e MAX_PRODOTTO_LISTINO e' il numero di righe presenti

//lista principale di supermercati
struct supermercato *supermercati;

int main() {
    //inizializzo la testa della lista collegata di supermercati
    supermercati = NULL;
}

void chiudi_supermercato(char *codice_supermercato_da_eliminare, char *codice_supermercato_di_riserva) {
    struct supermercato *supermercato_eliminato = supermercati;
    struct supermercato *previous = supermercati;
    bool eliminato = false;

    while (supermercato_eliminato != NULL) { // se la lista supermercati e' vuota e' inizializzata a NULL quindi non entra nel ciclo
        if(strcasecmp(supermercato_eliminato->codice_supermercato, codice_supermercato_da_eliminare)==0) { //confronto le due stringhe e se sono uguali cancello il supermercato
            previous->next = supermercato_eliminato->next; //prende l'elemento precedente e sostituisce l'elemento successivo con il nodo successivo di quello attuale
            eliminato = true;
            break;
        }
        previous = supermercato_eliminato; //memorizza il nodo attuale nella variabile che indica il nodo precedente 
        supermercato_eliminato = supermercato_eliminato->next; //memorizza nella variabile del nodo attuale il nodo successivo
    }

    //terminato il ciclo se ha trovato una corrispondenza avremo che la variabile supermercato_eliminato ha memorizzato il nodo eliminato.
    if(eliminato) {
        //sposta i prodotti nel supermercato specificato nell'argomento
        struct supermercato *supermercato_di_riserva = supermercati;
        eliminato = false;
        while (supermercato_di_riserva != NULL) {
            if(strcasecmp(supermercato_di_riserva->codice_supermercato, codice_supermercato_di_riserva)==0) {
                eliminato = true; //riutilizzo la variabile booleana per un flag
                break;
            }
            supermercato_di_riserva = supermercato_di_riserva->next;    //va al supermercato successivo nella lista
        }

        if(eliminato) {
            struct prodotto *lista_prodotti_da_aggiungere = supermercato_eliminato->lista_prodotti;
            while (lista_prodotti_da_aggiungere != NULL)
            {
                //supermercato_di_riserva->lista_prodotti aggiungi a questa lista il nuovo nodo lista_prodotti_da_aggiungere
                struct prodotto *prodotto_da_aggiugnere = lista_prodotti_da_aggiungere; //visto che non vogliamo modificare gli elementi della lista creo una variabile temporanea

                prodotto_da_aggiugnere->next = supermercato_di_riserva->lista_prodotti;
                supermercato_di_riserva->lista_prodotti = prodotto_da_aggiugnere;


                lista_prodotti_da_aggiungere = lista_prodotti_da_aggiungere->next; //va all'elemento della lista
            }
        }
        
    }
}

void stampa_prodotti_in_esaurimento(char *codice_supermercato) {
    struct supermercato *lista_supermercati = supermercati;
    while (lista_supermercati != NULL) { //giro tutta la lista dei supermercati
        if(strcasecmp(lista_supermercati->codice_supermercato, codice_supermercato)==0) { //appena trova il supermercato passato come argomento della funzione
            printf("supermercato di codice: %s\n", lista_supermercati->codice_supermercato);

            struct prodotto *lista_prodotti = lista_supermercati->lista_prodotti;
            while (lista_prodotti != NULL) { //giro la lista dei prodotti del supermercato
                for (int i = 0; i < MAX_PRODOTTO_LISTINO; i++) { //mi giri tutta la tabella listino
                    if(strcasecmp(tabella[i].codice_prodotto, lista_prodotti->codice_prodotto)==0) { //appena trova il rpdotto nella lista dei
                        if(lista_prodotti->quantita_presente<tabella[i].quantita_minima) {
                            printf("il prodotto: %s\nquantita' presente: %u e' minore della quantita' minima: %u", lista_prodotti->codice_prodotto, lista_prodotti->quantita_presente, tabella[i].quantita_minima);
                        }
                    }
                }
                lista_prodotti = lista_prodotti->next;
            }
            break; //perche' ha gia' trovato e stampato i prodotti se hanno la quantita' prsente minore dlela quantita' minima e il coiclo che gira i supermercati si puo' quindi interrompere.
        }
        lista_supermercati = lista_supermercati->next;
    }   
}

char * miglior_supermercato() {
    struct supermercato *lista_supermercati = supermercati;
    char codice_supermercato[MAX_STRING];
    double somma_prezzo_supermercato=0, somma_prezzo_supermercato_max=0;
    while (lista_supermercati != NULL) { //gira la lista dei supermercati
        somma_prezzo_supermercato = 0;
        struct prodotto *lista_prodotti = lista_supermercati->lista_prodotti;
        while (lista_prodotti != NULL) { //gira la lista dei prodotti di un supermercato
            for (int i = 0; i < MAX_PRODOTTO_LISTINO; i++) { //gira la tabella del listino dei prodotti
                if(strcasecmp(lista_prodotti->codice_prodotto, tabella[i].codice_prodotto)==0) { //appena trova il prodotto
                    somma_prezzo_supermercato += tabella[i].prezzo_unitario; //somma il prezzo dei prodotti
                }
            }
            lista_prodotti = lista_prodotti->next;
        }
        //dopo aver girato tutta la lista dei prodotti di un signo supermercato,
        //avremo la variabile somma_prezzo_supermercato che ha la somma di tutti i prezzi dei prodotti presenti in un supermercato;
        if(somma_prezzo_supermercato_max<somma_prezzo_supermercato) { //si confronta la somma dei prezzi del supermercato appena calcolato con quella del maggiore, e se <, 
            somma_prezzo_supermercato_max = somma_prezzo_supermercato;
            strcpy(codice_supermercato, lista_supermercati->codice_supermercato); //memorizza il codice del supermercato con il valore maggiore dei prodotti
        }//la variabile che contiene il valore dell'insieme dei prodotti con valore maggiore, viene aggionata con quella del supermercato attuale che e' maggiore.
        

        lista_supermercati = lista_supermercati->next; //va al supermercato successivo
    }
    return codice_supermercato; //restituisce il codice del supermercato con l'insieme di prodotti con valore maggiore
}