#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX_AGENTI_NOMI 100
#define TOP_AGENTE_ANNO 3

struct agente
{
    char id_agente[10+1];
    char nome_cognome_agente[70+1];
    int n_clienti_agente;

    struct appuntamento *lista_appuntamenti;
    struct agente *next;
};

struct appuntamento
{
    char id_cliente[10+1];
    char id_agente[10+1];
    char codice_richiesta_prestazione[15+1];

    struct appuntamento *next;
};

struct agente_nomi
{
    char id_agente[10+1];
    char nome_cognome_agente[70+1];
};


struct agente *lista_agenti;

struct agente_nomi agenti_nomi[MAX_AGENTI_NOMI]; 

int main() {
    lista_agenti = leggi_appuntamenti("./appuntamenti.txt");

    return 0;
}

struct agente * leggi_appuntamenti(char *file_path) {
    FILE *file;
    file = fopen(file_path, "r");

    if(file != NULL) // se vera il file e' stato aperto correttamente
    {
        while(!feof(file)) {
            char id_cliente[11], id_agente[11], codice_richiesta_prestazione[16];
            fscanf(file, "%s %s %s", id_cliente, id_agente, codice_richiesta_prestazione);

            //alloco e memorizzo gia' l'appuntamento, (poi decido a quale lista va collegato)
            struct appuntamento *new_node_appuntamento = malloc(sizeof(struct appuntamento));
            strcpy(new_node_appuntamento->id_agente, id_agente);
            strcpy(new_node_appuntamento->id_cliente, id_cliente);
            strcpy(new_node_appuntamento->codice_richiesta_prestazione, codice_richiesta_prestazione);

            struct agente *agente_esistente = lista_agenti;
            bool agente_gia_presente = false;
            while (agente_esistente != NULL) {
                if(strcmp(agente_esistente->id_agente, id_agente)==0) {agente_gia_presente=true;break;}
                agente_esistente = agente_esistente->next;
            }
            if(agente_gia_presente) { //vai a costruire solo un nuovo appuntamento
                //controllando pero' se il cliente ha gia' prenotato un appuntamento dallo stesso agente
                struct appuntamento *tmp_appuntamento = agente_esistente->lista_appuntamenti;
                struct appuntamento *appuntamento_precedente = agente_esistente->lista_appuntamenti;
                bool cliente_gia_presente = false;
                while (tmp_appuntamento != NULL) {
                    if(strcmp(tmp_appuntamento->id_cliente, id_cliente)==0) {
                        cliente_gia_presente = true;
                        break; //fondamentale
                    }
                    appuntamento_precedente = tmp_appuntamento;
                    tmp_appuntamento = tmp_appuntamento->next;
                }

                if(cliente_gia_presente) {
                    //inserisci l'appuntamento prima del tmp
                    appuntamento_precedente->next = new_node_appuntamento;
                    new_node_appuntamento->next = tmp_appuntamento;
                }
                else {
                    agente_esistente->n_clienti_agente++; //perche' e' un cliente diverso

                    //collega l'appuntamento nuovo alla lista degli appuntamenti dell'agente
                    new_node_appuntamento->next = agente_esistente->lista_appuntamenti;
                    agente_esistente->lista_appuntamenti = new_node_appuntamento;
                }
                
            }
            else { //costruisce anche un agente nella lista
                struct agente *new_node_agente = malloc(sizeof(struct agente));
                //inizializza la lista degli appuntamenti dell'agente
                new_node_agente->lista_appuntamenti = NULL;
                
                for (int i = 0; i < MAX_AGENTI_NOMI; i++) {
                    if(strcmp(id_agente, agenti_nomi[i].id_agente)==0) {
                        strcpy(new_node_agente->nome_cognome_agente, agenti_nomi[i].nome_cognome_agente);
                        break;
                    }
                }
                strcpy(new_node_agente->id_agente, id_agente);
                //avendo costruito ora l'agente allora e' impossibilie che la lista appuntamenti ne abbia piu' di uno
                new_node_agente->n_clienti_agente++;

                //collega l'appuntamento nuovo alla lista degli appuntamenti dell'agente
                new_node_appuntamento->next = new_node_agente->lista_appuntamenti;
                new_node_agente->lista_appuntamenti = new_node_appuntamento;
                
                //collega il nuovo agente alla lista agenti
                new_node_agente->next = lista_agenti;
                lista_agenti = new_node_agente;
            }
        

        }

        fclose(file);
    }

    return head;
}

void stampa_agenti(struct agente *tmp_agente) {
    if(!tmp_agente) return ; //se la lista e' null si interrompe
    printf("%s, agente: %s, n_clienti: %d\n", tmp_agente->id_agente, tmp_agente->nome_cognome_agente, tmp_agente->n_clienti_agente);
    struct appuntamento *tmp_appuntamenti = tmp_agente->lista_appuntamenti;
    while (tmp_appuntamenti != NULL) {
        printf("appuntamento:\ncliente: %s\n\trichiesta: %s", tmp_appuntamenti->id_cliente, tmp_appuntamenti->codice_richiesta_prestazione);
        tmp_appuntamenti = tmp_appuntamenti->next;
    }
    stampa_agenti(tmp_agente->nexTOP_AGENTE_ANNOt);
}

void premio_agente_anno() {
    //stampa la top 3 agenti 
    struct agente agente_anno[TOP_AGENTE_ANNO];
    int prestazioni_agente_anno[];
    for (int i = 0; i < TOP_AGENTE_ANNO; i++) prestazioni_agente_anno[i]=0;
    

    struct agente *tmp_agenti = lista_agenti;
    while (tmp_agenti != NULL) {
        struct appuntamento *tmp_appuntamenti = tmp_agenti->lista_appuntamenti;
        int i=0;//posizione dell'elemento nella lista

        int conta_prestazioni = 0;
        while (tmp_appuntamenti != NULL) {
            struct appuntamento *tmp_appuntamenti_confronto = tmp_agenti->lista_appuntamenti;
            int j=0;//posizione dell'elemento nella lista
            while (tmp_appuntamenti_confronto != NULL) {
                if(strcmp(tmp_appuntamenti->id_cliente, tmp_appuntamenti_confronto->id_cliente)==0) {
                    if(j<i) {conta_prestazioni=0;break;}//allora l'elemento e' gia' stato contato
                    conta_prestazioni++;
                }
                j++; //posizione dell'elemento nella lista
                tmp_appuntamenti_confronto = tmp_appuntamenti_confronto->next;
            }
            for (int m = 0; m < TOP_AGENTE_ANNO; m++) {
                if(conta_prestazioni>prestazioni_agente_anno[i]) {
                    prestazioni_agente_anno[i] = conta_prestazioni;
                    agente_anno[i] = tmp_agenti; //memorizza gli agenti top
                }
            }
            
            i++;    //posizione dell'elemento nella lista
            tmp_appuntamenti = tmp_appuntamenti->next;
        }
        
        tmp_agenti = tmp_agenti->next;
    }

    printf("i migliori %d agenti:\n", TOP_AGENTE_ANNO);
    for (int i = 0; i < TOP_AGENTE_ANNO; i++) {
        printf("%s, agente: %s, n_clienti: %d\n", agente_anno[i]->id_agente, agente_anno[i]->nome_cognome_agente, agente_anno[i]->n_clienti_agente);
    }
    
}