#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>



//FUNZIONI DEI COMANDI utili per l'inserimento e la scelta durante l'esecuzione del programma
//FUNZIONA SOLO SU WINDOWS
#include <windows.h> //il programma funziona perfettamente solo su windows
#define clear() system("cls");
COORD GetConsoleCursorPosition();
void gotoxy();

//define dei comandi per muoversi
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77

#define ESCAPE 27
#define ENTER 13

//DATI DEL PROGRAMMA
#define MAX_INSEGNAMENTI 10 //numero massimo del vettore di strutture insegnamenti
#define MAX_STUDENTI 10     //numero massimo del vettore di strutture studenti
#define NUM_ESAMI 10        //numero massimo del vettore di strutture piano_di_studi

#define GRANDEZZA_CODICE 6 //5 numeri + 1 '\0' //grandezza del codice

struct insegnamento { //struct per gli insegnamenti
    char codice[GRANDEZZA_CODICE];
    char descrizione[50];
    unsigned int anno_somministrazione;
    unsigned int crediti;
};

struct esame    //struct per i piani di studi
{
    char codice_insegnamento[GRANDEZZA_CODICE];
    unsigned int voto; //0 se non sostenuto
};

struct studente { //struct studente
    int matricola;
    char nome[21];
    char cognome[21];
    unsigned int anno_immatricolazione;
    struct esame *piano_di_studi[NUM_ESAMI];
    int count_pianodistudi;
};

//variabili pubbliche  (perche' tutte le funzioni le andranno ad usare)
struct studente *studenti[MAX_STUDENTI];
int count_studenti=0;

struct insegnamento *insegnamenti[MAX_INSEGNAMENTI];
int count_insegnamenti=0;

//funzioni usate
void aggiungiInsegnamento();
void stampaInsegnamenti();
void aggiungiStudente();
void scegliPianoDiStudi();
void aggiungiPianoDiStudi();
void visualizzaStudente();
void modificaVotoStudente();
void calcolaMedia();

int main()
{
    /*Gruppo:
    Matricola:  Alex Mazzoni       E-mail: alex.mazzoni3@studio.unibo.it
    Matricola:  Giovanni Luca      E-mail: giovanni.luca@studio.unibo.it
    Matricola:  Michele Farneti    E-mail: michele.farneti@studio.unibo.it
    */

    printf("\nSettimana 7 - Esercizio 2\t E-mail di riferimento: alex.mazzoni3@studio.unibo.it\n\n");
    
    //carico tutti gli insegnamenti che si vogliono aggiungere nei piani di studi
    aggiungiInsegnamento( "00013\0", "Analisi Matematica\0", 2022, 12);
    aggiungiInsegnamento( "00819\0", "Programmazione    \0", 2022, 12);
    aggiungiInsegnamento( "26338\0", "Idoneita' Inglese \0", 2022, 6);

    int scelta = -1;
    while (scelta!=0) { //solito menu che richiede una voce in input e finche' non si inserisce 0 si ripete
        printf("\nMenu': \n");
        printf("\t1. Aggiungi nuovo studente.\n");
        printf("\t2. Visualizza studente.\n");
        printf("\t3. Modifica studente.\n");
        printf("\t4. Calcola media di tutti gli studenti.\n");
        printf("\t0. Disconnettiti.\n");
        printf("\nutente, digita pure il numero relativo alla voce interessata: ");
        scanf("%d", &scelta);
        fflush(stdin);
        switch (scelta) {
            case 0:
                printf("\nArrivederci.");
                break;
            case 1:
                aggiungiStudente();
                break;
            case 2:
                visualizzaStudente();
                break;
            case 3:
                modificaVotoStudente();
                break;
            case 4:
                calcolaMedia();
                break;  
        }
    }
    return 0;
}

void aggiungiInsegnamento(char *cod, char *des, unsigned int anno, unsigned int cr) { //passo come argomento le variabili per riempire un insegnamento
    insegnamenti[count_insegnamenti] = malloc(sizeof(struct insegnamento)); //lo alloco in memoria dinamicamente
    if(insegnamenti[count_insegnamenti] != NULL)// se la malloc non riesce a aggiungere spazio in memoria 
    {
        strcpy(insegnamenti[count_insegnamenti]->codice, cod);
        strcpy(insegnamenti[count_insegnamenti]->descrizione, des);
        insegnamenti[count_insegnamenti]->anno_somministrazione = anno;
        insegnamenti[count_insegnamenti]->crediti = cr;
        count_insegnamenti++;
    } 
}

void stampaInsegnamenti() {
    for (int i = 0; i < count_insegnamenti; i++) //stampa del vettore insegnamenti
    {
        printf("\t%s", insegnamenti[i]->codice);
        printf("\t%s", insegnamenti[i]->descrizione);
        printf("\t\t%u", insegnamenti[i]->anno_somministrazione);
        printf("\t\tcrediti: %u\n", insegnamenti[i]->crediti);
    }
    printf("\n");
}

void aggiungiStudente() {
    if(studenti[count_studenti]==NULL) //controlla se il vettore e' libero
    {
        studenti[count_studenti] = malloc(sizeof(struct studente)); //alloca memoria grande quanto la grandezza della struct studente
        if(studenti[count_studenti]!=NULL) //comincia ad aggiungere lo studente se la malloc va a buon fine
        {
            bool flag=false;
            do //controlla se la matricola e' gia stata inserita dal numero matricola
            {
                flag=false;
                printf("Numero Matricola: ");
                scanf("%d", &studenti[count_studenti]->matricola);
                for (int i = 0; i < count_studenti; i++)
                {
                    if(studenti[i]!=NULL) {
                        if((studenti[count_studenti]->matricola)==(studenti[i]->matricola)) {
                            flag = true;
                        }
                    }
                }
                if(flag)
                    printf("\n\tnumero matricola gia' presente nel sistema!\n");
            } while (flag); //e richiede il numero della matricola finche' non e' una matricola non presente nel vettore
           
            printf("Nome: ");
            scanf("%s", &studenti[count_studenti]->nome);
            printf("Cognome: ");
            scanf("%s", &studenti[count_studenti]->cognome);
            printf("Anno di immatricolazione: ");
            scanf("%d", &studenti[count_studenti]->anno_immatricolazione);
            studenti[count_studenti]->count_pianodistudi=0;
            scegliPianoDiStudi(); //funzione che fa scegliere fra gli insegnamenti disponibili
            count_studenti++;
            printf("\n\n\tstudente aggiunto con successo!");
            clock_t now = clock();
            for( ; clock() - now < 2 * CLOCKS_PER_SEC; );
            clear();
        }
    }
}

void scegliPianoDiStudi() { //permette di scegliere in maniera grafica quali insegnamenti si vuole aggiungere al piano di studio dello studente
    printf("\n\nMuoversi con le frecce direzionali (su e giu') per scegliere un insegnamento e premere ENTER per aggiungerlo al piano di studi oppure ESC per terminare l'aggiunta\n\n");
    stampaInsegnamenti();
    printf("\n");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD old_coord = GetConsoleCursorPosition(hConsole);
    int y=0; //y=(old_coord.Y-5) e' il range per 3 insegnamenti e' da modificare se si vuole aggiugerne altri

    int y_min=0; //compresi
    int y_max=count_insegnamenti-1; //compresi
    gotoxy(y+(old_coord.Y-2-count_insegnamenti), old_coord.X);// muove il cursore nella posizione 
    char c = ' ';
    while (c!=ESCAPE) //e permette di muoversi all'interno dello schermo finche' non si preme ESC
    {
        c = getch();
        switch (c)
        {
            case ARROW_UP:
                if(y-1>=y_min)
                    y--;
               break;
           case ARROW_DOWN:
                if(y+1<=y_max)
                    y++;
               break;
            case ENTER:
                aggiungiPianoDiStudi(y); //appena viene premuto enter inserisce effettivamente l'insegnamento selezionato all'interno del vettore piano di studio presente all'interno del vettore studenti
                printf("X"); //printa un carattere per far notare che si e' aggiunto quell'insegnamento
               break;
        }
    gotoxy(y+(old_coord.Y-2-count_insegnamenti), old_coord.X); // muove il cursore nella posizione 
    }
    printf("\n\n");
}

void aggiungiPianoDiStudi(int insegnamento_scelto) {
    //fare il controllo se l'insegnamento e' gia' stato inserito
    bool gia_inserito = false;
    for (int i = 0; i < studenti[count_studenti]->count_pianodistudi; i++)
    {
        if(strcmp(studenti[count_studenti]->piano_di_studi[i]->codice_insegnamento, insegnamenti[insegnamento_scelto]->codice)==0)
        {
            gia_inserito = true;
        }
    }
    if(!gia_inserito)// altrimenti se non e' stato inserito lo inserisce nel vettore piano di studi
    {
        studenti[count_studenti]->piano_di_studi[studenti[count_studenti]->count_pianodistudi] = malloc(sizeof(struct esame));
        if(studenti[count_studenti]->piano_di_studi[studenti[count_studenti]->count_pianodistudi] != NULL) //aggiunge un nuovo piano di studi solo se la malloc va a buon fine
        {
            strcpy(studenti[count_studenti]->piano_di_studi[studenti[count_studenti]->count_pianodistudi]->codice_insegnamento, insegnamenti[insegnamento_scelto]->codice);
            studenti[count_studenti]->piano_di_studi[studenti[count_studenti]->count_pianodistudi]->voto = 0;
            studenti[count_studenti]->count_pianodistudi++;
        }
    }
}

void visualizzaStudente() {
    int numero_matricola=0;
    printf("Inserisci il numero della matricola: "); //dato il numero della matricola
    scanf("%d", &numero_matricola);

    bool trovato = false;
    int i=0;
    for (i = 0; !trovato && i < count_studenti; i++) //controlla se e' presente nel vettore la matricola che si vuole cercare
    {
        if(studenti[i]->matricola == numero_matricola)
        {
            trovato = true;
        }
    }
    i--;
    if(trovato) //se e' presente la visualizza
    {
        printf("\n\t%s %s\t", studenti[i]->nome, studenti[i]->cognome);
        printf("immatricolato nel %u\n", studenti[i]->anno_immatricolazione);
        printf("\nPiano di studi:");
        for (int j = 0; j < studenti[i]->count_pianodistudi; j++)
        {
            printf("\n\t%s", studenti[i]->piano_di_studi[j]->codice_insegnamento);
            printf("\tvoto: %d", studenti[i]->piano_di_studi[j]->voto);
        }
        printf("\n\n");
    }
    else
    { //altrimenti stampa un messaggio di errore
        printf("\n\n\tnessuno studente trovato con il numero matricola '%d'", numero_matricola);
        clock_t now = clock();
        for( ; clock() - now < 2 * CLOCKS_PER_SEC; );
        clear();
    }
}

void modificaPianoDiStudi(int studente_scelto) { //fa scegliere fra gli insegnamenti del piano di studi dello studente il voto che si vuole modificare
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD old_coord = GetConsoleCursorPosition(hConsole);
    printf("\n\nMuoversi con le frecce direzionali (su e giu') e premere ENTER per modificare il voto dell'insegnamento oppure ESC per terminare la scelta\n\n");
    int y=0;

    int y_min=0; //compresi
    int y_max=studenti[studente_scelto]->count_pianodistudi-1; //compresi
    gotoxy(y+(old_coord.Y-3-studenti[studente_scelto]->count_pianodistudi), old_coord.X);// muove il cursore nella posizione
    char c = ' ';
    while (c!=ESCAPE) //e permette di muoversi all'interno dello schermo finche' non si preme con ESC
    {
        c = getch();
        switch (c)
        {
            case ARROW_UP:
                if(y-1>=y_min)
                    y--;
               break;
           case ARROW_DOWN:
                if(y+1<=y_max)
                    y++;
               break;
            case ENTER:
                gotoxy(y+(old_coord.Y-3-studenti[studente_scelto]->count_pianodistudi), old_coord.X-2);// muove la x 
                scanf("%d", &studenti[studente_scelto]->piano_di_studi[y]->voto); //modifica il voto inserendolo direttamente nella variabile
               break;
        }
        gotoxy(y+(old_coord.Y-3-studenti[studente_scelto]->count_pianodistudi), old_coord.X);// muove il cursore nella posizione
    }
    printf("\n\n");
}

void modificaVotoStudente() {
    int numero_matricola=0;
    printf("Inserisci il numero della matricola: "); //dato una matricola
    scanf("%d", &numero_matricola);

    bool trovato = false;
    int i=0;
    for (i = 0; !trovato && i < count_studenti; i++)
    {
        if(studenti[i]->matricola == numero_matricola)
        {
            trovato = true;
        }
    }
    i--;
    if(trovato) //controlla se e' presente, e se lo e' visualizza le informazioni e permette di modificare i voti del piano di studi
    {
        printf("\n\t%s %s\t", studenti[i]->nome, studenti[i]->cognome);
        printf("immatricolato nel %u\n", studenti[i]->anno_immatricolazione);
        if(studenti[i]->count_pianodistudi>0)
        {
            printf("\nPiano di studi:");
            for (int j = 0; j < studenti[i]->count_pianodistudi; j++)
            {
                printf("\n\t%s", studenti[i]->piano_di_studi[j]->codice_insegnamento);
                printf("\tvoto: %d", studenti[i]->piano_di_studi[j]->voto);
            }
            modificaPianoDiStudi(i);
        }
        else //se non ha nessun insegnamento all'interno del piano di studi da errore
            printf("\nNessun insegnamento nel piano di studi");

        printf("\n\n");
    }
    else //da errore anche se il numero matricola inserito non e' presente
    {
        printf("\n\n\tnessuno studente trovato con il numero matricola '%d'", numero_matricola);
        clock_t now = clock();
        for( ; clock() - now < 2 * CLOCKS_PER_SEC; ); //aspetta due secondi e poi ripulisce lo schermo e va avanti
        clear();
    }
}

void calcolaMedia() {
    int numeratore=0;
    int denominatore=0;
    for (int i = 0; i < count_studenti; i++) //scorre ogni studente
    {
        bool pianodistudi_completato = true;
        int numeratore_tmp=0;
        int denominatore_tmp=0;
        for (int j = 0; pianodistudi_completato && j < studenti[i]->count_pianodistudi; j++) //scorre il vettore piano di studi di ogni studente
        {
            if(studenti[i]->piano_di_studi[j]->voto!=0) //se l'insegnamento ha un voto != da 0, memorizza i dqati per calcolare la media pesata
            {
                bool insegnamento_trovato = false;
                int m;
                for (m = 0; m < count_insegnamenti && !insegnamento_trovato; m++) //prende i crediti ricercando fra gli insegnamenti qual'e' quello che sta scorrendo
                {
                    if(strcmp(insegnamenti[m]->codice, studenti[i]->piano_di_studi[j]->codice_insegnamento)==0)
                    {
                        insegnamento_trovato = true;
                    }
                }
                m--; //memorizza tutte le somme per fare la media ponderata
                numeratore_tmp += studenti[i]->piano_di_studi[j]->voto * insegnamenti[m]->crediti;
                denominatore_tmp += insegnamenti[m]->crediti;
            }
            else
            {   //altrimenti se un insegnamento risulta con voto == 0, non calcolera' la media di quello studente 
                pianodistudi_completato=false;
                numeratore_tmp=0;
                denominatore_tmp=0;
            }
        }
        numeratore+=numeratore_tmp;
        denominatore+=denominatore_tmp;
    }
    if(numeratore != 0 || denominatore != 0) //mostra la media se e' possibile calcolarla
    {
        float media = (float)numeratore/denominatore;
        printf("\nLa media pesata degli studenti che hanno completato il loro piano di studi e' %.2f\n", media);
    }
    else //altrimenti mostra un messaggio di errore
        printf("\nNessuno studente ha completato il proprio piano di studi\n");

}

//gestisce la console prendendo le coordinate del puntatore nel momento in cui la si richiama
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else //gestisce gli errori restituendo delle coordinate 0, 0  
    {
        // The function failed. Call GetLastError() for details.
        COORD invalid = { 0, 0 };
        return invalid;
    }
}

void gotoxy(int y, int x) //va alla posizione x y 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = GetConsoleCursorPosition(hConsole);
    coord.X = x;
    coord.Y = y;
    if (!SetConsoleCursorPosition(hConsole, coord)){} //gestisce gli errori
}