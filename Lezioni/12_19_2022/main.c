#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>


#define MAX_MEDICI 200
#define MAX_TURNI 7
#define ABSOLUTEPATH_APPUNTAMENTI "./appuntamenti.txt"

struct singolo_turno //lista indicizzata di ogni turno
{
    struct singolo_turno *next;

    unsigned int id_turno; // [1, 8]
    unsigned int pazienti_per_turno; // [1, 5]
};

struct medico
{
    char id_medico[13]; //12 + 1 per il carattere \0, ordinati gia' per ordine crescente (presuppiamo che già lo siano non c'è bisogno di farlo).
    char reparto[31];   //30 + 1 per il carattere \0
    struct singolo_turno *turni[MAX_TURNI]; //è la testa una per ogni giorni della settimana
};

/*
    esempio (appuntamenti.txt):
    id_paziente[12] id_medico[12] turno_richieto(intero [1, 8]) giorno_richiesto(intero [1, 5])
    2-145;1-21;2;4
    2-221;1-34;5;3
*/

struct esubero
{
    struct singolo_turno *turni[MAX_TURNI];
};


struct medico *medici;
int count_medici = 0; //mi serve per sapere quanti elementi ha allocato il vettore medici.

struct esubero *esuberi;
int count_esuberi = 0;

//funzioni: ----------------------------------
void leggi_appuntamenti();


//--------------------------------------------

int main() {
    medici = calloc(MAX_MEDICI, sizeof(struct medico));
    if(medici==NULL) exit(1); //errore allocazione memoria

    esuberi = calloc(MAX_MEDICI, sizeof(struct esubero));
    if(esuberi==NULL) exit(1); //errore allocazione memoria

    for (int i = 0; i < MAX_MEDICI; i++) {
        for (int j = 0; j < MAX_TURNI; j++) {
            medici[i].turni[j] = NULL;
            esuberi[i].turni[j] = NULL;
        }
    }

    //punto da 14 punti
    leggi_appuntamenti(ABSOLUTEPATH_APPUNTAMENTI);

    return 0;
}

void leggi_appuntamenti(char *nome_file) {
    FILE *file;
	file = fopen(nome_file, "r");   //mode: r → sola-lettura.
    
    char id_paziente[12 + 1], id_medico[30 + 1];
    int turno_richiesto, giorno_richiesto;
    
    struct singolo_turno temp;
    struct singolo_turno temp_esub;

    if(file != NULL)
    {
        while (!feof(file))
        {
            fscanf(file, "%s %s %d %d", id_paziente, id_medico, &turno_richiesto, &giorno_richiesto);
            
            for (int i = 0; i < MAX_MEDICI; i++)
            {
                if(strcmp(medici[i].id_medico, id_medico) == 0) {
                    temp = medici[i].turni[giorno_richiesto - 1];
                    while (temp != NULL) {
                        if(temp->id_turno == turno_richiesto) {
                            if(temp->pazienti_per_turno < 5) {
                                tmep->pazienti_per_turno++;
                            }
                            else {
                                temp_esub = esuberi[i].turni[giorno_richiesto - 1];
                                while (temp_esub != NULL) {
                                    if(temp_esub->id_turno == turno_richiesto) {
                                        temp_esub->pazienti_per_turno++;
                                        break;
                                    }
                                    temp_esub = temp_esub->next;
                                }
                            }
                            break;
                        }
                        temp = temp->next;
                    }
                    
                }

            }
        }
        fclose(file);
    }
}



//bubble sort per una lista di interi in ordine crescente
// void bubbleSort(int lista[10]) {
//     for (int i = 0; i < (10-1); i++)
//     {
//         for (int j = 0; j < (10-1-i); j++)
//         {
//             if(lista[j] > lista[j+1])
//             {
//                 int tmp = lista[j];
//                 lista[j] = lista[j+1];
//                 lista[j+1] = tmp;
//             }
//         }
//     }
// }