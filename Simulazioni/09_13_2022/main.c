#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRUTTURE_MEDICO 200    //numero massimo di strutture medico
#define GIORNI_SETTIMANA 7      //numero giorni della settimana poiche' ogni medico ha una lista di turni per una settimana
#define MAX_PAZIENTI_PER_TURNO 5

struct struct_medico {
    char id_medico[12+1]; //vettore di caratteri, stringa di 12 caratteri utili
    char reparto[30+1];   //stringa di 30 caratteri utili

    struct singolo_turno *turni[GIORNI_SETTIMANA]; //teste delle liste a strutture collegate
};

struct singolo_turno {
    unsigned int id_turno;   //intero compreso tra 1 e 8, in un giorno un medico puo' avere solo 8 turni massimo
    unsigned int pazienti_per_turno;   //intero compreso fra 1 e 5, perche' ogni medico in ogni turno puo' visitare al massimo 5 pazienti

    
    struct singolo_turno *next; //puntatore all'elemento successivo della lista collegata
};

struct esubero {
    struct singolo_turno *turni[GIORNI_SETTIMANA]; //teste delle liste a strutture collegate
};

struct struct_medico *medici; //vettore dinamico contenente 200 strutture medico
struct esubero esuberi[STRUTTURE_MEDICO];

int main() {
    medici = malloc(sizeof(struct struct_medico) * STRUTTURE_MEDICO);   //alloco in memoria

    for (int i = 0; i < STRUTTURE_MEDICO; i++) {
    //inizializzo se esistono altri vettori dinamici
        for (int j = 0; j < GIORNI_SETTIMANA; j++) {
            medici[i]->turni[j] = NULL;
            esuberi[i]->turni[j] = NULL;
        }
    }
    
    
    return 0;
}

void leggi_appuntamenti(char *path_file) {
    FILE *file;
    file = fopen(path_file, "r");
            
    char id_paziente[12+1], id_medico[12+1];
    unsigned int turno_richiesto, giorno_richiesto;

    struct singolo_turno *tmp;
    struct singolo_turno *tmp_esub;
    if(FILE != NULL) {
        while(!feof) { //finche' non e' alla fine del file itera il blocco
            fscanf(file, "%s %s %u %u", id_paziente, id_medico, &turno_richiesto, &giorno_richiesto);

            for (int i = 0; i < STRUTTURE_MEDICO; i++) {
                if(strcasecmp(medici[i]->id_medico, id_medico)==0) { //trovo un medico
                    tmp = medici[i]->turni[giorno_richiesto-1];
                    while (tmp != NULL) {
                        if(tmp->id_turno == turno_richiesto) {
                            if(tmp->pazienti_per_turno < 5) {
                                tmp->pazienti_per_turno++;
                            }
                            else {
                                tmp_esub = esuberi[i].turni[giorno_richiesto - 1];

                                while (tmp_esub != NULL) {
                                    if(tmp_esub->id_turno == turno_richiesto) {
                                        tmp_esub->pazienti_per_turno++
                                        break;
                                    }
                                    tmp_esub = tmp_esub->next;
                                }
                                break;
                            }
                        }
                        tmp = tmp->next;
                    }
                }
            }
        }

        fclose(file); 
    }
}

int stampa_esuberi(int i, int j, struct singolo_turno *tmp) {   //ricorsiva
    int numero_totale_di_pazienti;
    if (i == STRUTTURE_MEDICO) {
        return;
    }
    if (j == GIORNI_SETTIMANA) {
        stampa_esuberi(i + 1, 0, esuberi[i + 1].turni[0]);
        return;
    }
    if (tmp == NULL) {
        printf("%d", numero_totale_di_pazienti);
        numero_totale_di_pazienti = 0;
        stampa_esuberi(i, j + 1, esuberi[i].turni[j + 1]);
        return;
    }

    numero_totale_di_pazienti += stampa_esuberi(i, j, tmp->next);
    return tmp->pazienti_per_turno;
}

void stampa_esuberi_nonricorsiva() { //non ricorsiva
    for (int i = 0; i < STRUTTURE_MEDICO; i++) {
        for (int j = 0; j < GIORNI_SETTIMANA; j++) {
            struct singolo_turno *tmp = esuberi[i].turni[j];
            int numero_totale_di_pazienti=0;
            while (tmp != NULL) {
                numero_totale_di_pazienti += tmp->pazienti_per_turno;
                tmp = tmp->next;
            }
            printf("%d", numero_totale_di_pazienti);
        }
    }
}

float occupazione_medico(char *id_medico) {
    int i=0;
    for (i = 0; i < STRUTTURE_MEDICO; i++) {
        if(strcasecmp(medici[i].id_medico, id_medico) == 0) {
            break;
        }
    }
    
    struct singolo_turno *tmp;
    int conta_turni_totali = 0, pazienti_per_turno_totali = 0;
    for (int j = 0; j < GIORNI_SETTIMANA; j++) {
        
        tmp = medici[i].turni[j]; //turni massimi 8
        while (tmp != NULL) {
            conta_turni_totali++; //al massimo sono 5 per turno

            pazienti_per_turno_totali += tmp->pazienti_per_turno;
            tmp = tmp->next;
        }
    }

    float percentuale_occupazione = (float) (100 * pazienti_per_turno_totali) / (conta_turni_totali*MAX_PAZIENTI_PER_TURNO); 
}
