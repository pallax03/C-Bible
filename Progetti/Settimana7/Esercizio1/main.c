#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

#include <windows.h> //il programma funziona perfettamente solo su windows
#define clear() system("cls");
COORD GetConsoleCursorPosition();
void gotoxy();

//define dei comandi per muoversi
#define ARROW_UP 72
#define ARROW_DOWN 80

#define ESCAPE 27
#define ENTER 13

//variabili del programma
#define MAX_NOME 20  //massimi caratteri consentiti per il nome della stanza
#define NUMSTANZE 10 //massime stanze consentite

struct stanza {
    char nome[MAX_NOME];
    float larghezza;
    float lunghezza;
    float area;
    int num_ostacoli;
    int priorita_pulizia; //1 = molto alta, più numero è alto più è meno importante pulire...
};

//vettore delle stanze pubblico
struct stanza *stanze[NUMSTANZE];
int count_stanze=0;

//caricamento
COORD GetConsoleCursorPosition();
void gotoxy();
void robConnect();

void aggiungiStanza();
void mostraInfoStanza();
void modificaStanza();
void calcolaPercorso();

int main()
{
    /*Gruppo:
    Matricola:  Alex Mazzoni       E-mail: alex.mazzoni3@studio.unibo.it
    Matricola:  Giovanni Luca      E-mail: giovanni.luca@studio.unibo.it
    Matricola:  Michele Farneti    E-mail: michele.farneti@studio.unibo.it
    */

    printf("\nSettimana 7 - Esercizio 1\t E-mail di riferimento: alex.mazzoni3@studio.unibo.it\n\n");
    
    int scelta = -1;
    printf("Salve utente, io sono Rob8, il tuo domestico cibernetico! Attendi qualche secondo per il mio"
           " caricamento...\n");
    robConnect(); //commentare se non si vuole il caricamento.
    clear(); //ripulisce lo schermo
    while (scelta!=0) { //stampa il menu finche' non si inserisce 0
        printf("\nMenu\' dell voci: \n");
        printf("\t1. Aggiungi stanza.\n");
        printf("\t2. Mostra informazioni di una stanza.\n");
        printf("\t3. Modifica una stanza.\n");
        printf("\t4. Calcola percorso in base alla priorita\' di pulizia.\n");
        printf("\t0. Disconnettiti.\n");
        printf("\nutente, digita pure il numero relativo alla voce interessata: ");
        scanf("%d", &scelta);
        fflush(stdin);
        switch (scelta) {
            case 0:
                printf("\nArrivederci.");
                break;
            case 1:
                aggiungiStanza(); //aggiunge una stanza al vettore stanze
                break;
            case 2:
                mostraInfoStanza(); //mostra le informazioni di una stanza
                break;
            case 3:
                modificaStanza(); //permette la modifica di una stanza
                break;
            case 4:
                calcolaPercorso(); //ordina la sequenza delle stanze in ordine crescente per stabilire la priorita' di pulizia
                break;
        }
    }
    return 0;
}

void aggiungiStanza() {
    if(stanze[count_stanze] == NULL) //controlla se il vettore e' libero
    {
        stanze[count_stanze] = malloc(sizeof(struct stanza)); //alloca memoria grande quanto la grandezza della struct stanza
        if(stanze[count_stanze]!=NULL) //comincia ad aggiungere la stanza se la malloc va a buon fine
        {
            bool flag=false;
            do //controlla se la stanza e' gia' stata inseirta controllando se il nome e' gia' presente
            {
                flag=false;
                printf("Nome stanza: ");
                scanf("%s", stanze[count_stanze]->nome);
                fflush(stdin);
                for (int i = 0; i < count_stanze; i++)
                {
                    if(stanze[i]!=NULL) {
                        if(strcmp(stanze[count_stanze]->nome, stanze[i]->nome)==0) {
                            flag = true;
                        }
                    }
                }
                if(flag)
                    printf("\n\tstanza gia' presente nel sistema!\n");
            } while (flag); //e richiede il nome fino a che non e' diverso da un altra stanza
    
            printf("Larghezza: ");
            scanf("%f", &stanze[count_stanze]->larghezza);
            fflush(stdin);
            printf("Lunghezza: ");
            scanf("%f", &stanze[count_stanze]->lunghezza);
            fflush(stdin);
            stanze[count_stanze]->area = stanze[count_stanze]->lunghezza * stanze[count_stanze]->larghezza;
            printf("Numero di ostacoli: ");
            scanf("%d", &stanze[count_stanze]->num_ostacoli);
            fflush(stdin);
            printf("Priorita' di pulizia: ");
            scanf("%d", &stanze[count_stanze]->priorita_pulizia);
            fflush(stdin);
            count_stanze++;
            printf("\n\n\tstanza aggiunta con successo!");
            //estetica
            clock_t now = clock();
            for( ; clock() - now < 2 * CLOCKS_PER_SEC; ); //aspetto 2 secondi prima di ripulire lo schermo e tornare al main()
            clear();
        }
    }
}

void mostraInfoStanza() {
    char nome_stanza[MAX_NOME];
    printf("Inserisci il nome della stanza: "); //dato il nome della stanza
    scanf("%s", &nome_stanza);

    bool trovato = false;
    int i=0;
    for (i = 0; !trovato && i < count_stanze; i++) //controlla se e' presente nel vettore la stanza che si vuole cercare
    {
        if(strcmp(stanze[i]->nome, nome_stanza)==0)
        {
            trovato = true;
        }
    }
    i--;
    if(trovato) //se e' presente la visualizza
    {
        printf("\n\t%s\n", stanze[i]->nome);
        printf("\t%.1f ", stanze[i]->larghezza);
        printf("x %.1f metri\n", stanze[i]->lunghezza);
        printf("\tArea: %.1f metri^2\n", stanze[i]->area);
        printf("\tnumero ostacoli: %d\n", stanze[i]->num_ostacoli);
        printf("\tpriorita' di pulizia: %d", stanze[i]->priorita_pulizia);
        printf("\n\n");
    }
    else
    { //altrimenti stampa un messaggio di errore
        printf("\n\n\tnessuna stanza presente con il nome di: '%s'", nome_stanza);
        clock_t now = clock();
        for( ; clock() - now < 2 * CLOCKS_PER_SEC; ); //aspetta secondi prima di ripulire lo schermo e tornare al main()
        clear();
    }
}

void scegliParametro(int stanza_scelta) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD old_coord = GetConsoleCursorPosition(hConsole);
    int y=0;        //imposta il campo di movimento iniziale e l'intervallo in cui l'utenete puo' muoversi
    int y_min=0; //compresi
    int y_max=4; //compresi
    gotoxy((old_coord.Y - y_max)+y, 7);// muove il cursore nella posizione iniziale considerando i tab
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
                switch (y) //switch per l'implementazione grafica //poiche' ogni y ha il suo parametro
                {
                    case 0: //nome
                        gotoxy((old_coord.Y - y_max)+y, 7+1);// muove il cursore nella posizione
                        scanf("%s", stanze[stanza_scelta]->nome);
                        break;
                    case 1: //larghezza
                        gotoxy((old_coord.Y - y_max)+y, 7+1);// muove il cursore nella posizione
                        scanf("%f", &stanze[stanza_scelta]->larghezza);
                        stanze[stanza_scelta]->area = stanze[stanza_scelta]->larghezza * stanze[stanza_scelta]->lunghezza;
                        break;
                    case 2: //lunghezza
                        gotoxy((old_coord.Y - y_max)+y-1 , 7+((int)logf(stanze[stanza_scelta]->larghezza))+5+1);
                        scanf("%f", &stanze[stanza_scelta]->lunghezza);
                        stanze[stanza_scelta]->area = stanze[stanza_scelta]->larghezza * stanze[stanza_scelta]->lunghezza;
                        break;
                    case 3: //numero ostacoli
                        gotoxy((old_coord.Y - y_max)+y, 24+1);// muove il cursore nella posizione
                        scanf("%d", &stanze[stanza_scelta]->num_ostacoli);
                        break;
                    case 4: //priorita' di pulizia
                        gotoxy((old_coord.Y - y_max)+y, 29+1);// muove il cursore nella posizione
                        scanf("%d", &stanze[stanza_scelta]->priorita_pulizia);

                        break;
                }
               break;
        }
        gotoxy((old_coord.Y - y_max)+y, 7); // muove il cursore nella posizione
        switch (y) //switch per l'implementazione grafica
        {
            case 0: //nome
                break;
            case 1: //larghezza
                break;
            case 2: //lunghezza
                gotoxy((old_coord.Y - y_max)+y-1 , 7+((int)logf(stanze[stanza_scelta]->larghezza))+5);
                break;
            case 3: //numero ostacoli
                gotoxy((old_coord.Y - y_max)+y, 24);// muove il cursore nella posizione
                break;
            case 4: //priorita' di pulizia
                gotoxy((old_coord.Y - y_max)+y, 29);// muove il cursore nella posizione
                break;
        }
    }
    printf("\n\n");
}

void modificaStanza() {
    char nome_stanza[MAX_NOME];
    printf("Inserisci il nome della stanza: "); //dato il nome della stanza
    scanf("%s", &nome_stanza);

    bool trovato = false;
    int i=0;
    for (i = 0; !trovato && i < count_stanze; i++) //controlla se e' presente nel vettore la stanza che si vuole cercare
    {
        if(strcmp(stanze[i]->nome, nome_stanza)==0)
        {
            trovato = true;
        }
    }
    i--;
    if(trovato) //se e' presente la visualizza
    {
        printf("\nMuoversi con le frecce direzionali (su e giu') e premere ENTER per scegliere il parametro da modificare oppure ESC per terminare la modifica\n");
        printf("\n\t%s\n", stanze[i]->nome);
        printf("\t%.1f ", stanze[i]->larghezza);
        printf("x %.1f metri\n", stanze[i]->lunghezza);
        printf("\tArea: %.1f metri^2\n", stanze[i]->area);
        printf("\tnumero ostacoli: %d\n", stanze[i]->num_ostacoli);
        printf("\tpriorita' di pulizia: %d", stanze[i]->priorita_pulizia);
        scegliParametro(i);     //funzione che fa scegliere il parametro da modificare
        printf("\n\n");
    }
    else
    { //altrimenti stampa un messaggio di errore
        printf("\n\n\tnessuna stanza presente con il nome di: '%s'", nome_stanza);
        clock_t now = clock();
        for( ; clock() - now < 2 * CLOCKS_PER_SEC; ); //aspetta secondi prima di ripulire lo schermo e tornare al main()
        clear();
    }
}
 
void calcolaPercorso() {
    printf("\n");
    struct stanza *tmp;
    for (int i = 0; i < count_stanze - 1; i++) //bubble sort del vettore stanze in base al parametro priorita' pulizia
    {
        for (int j = 0; j < count_stanze - i - 1; j++)
        {
            if (stanze[j]->priorita_pulizia > stanze[j + 1]->priorita_pulizia)
            {
                tmp = stanze[j];
                stanze[j] = stanze[j + 1];
                stanze[j + 1] = tmp;
            }
        }
    }

    for (int i = 0; i < count_stanze; i++) //stampa del vettore stanze
    {
        printf("\t%d) %s\tpriorita: %d\n", i+1, stanze[i]->nome, stanze[i]->priorita_pulizia);
    }
    printf("\n");
}

void robConnect() {
    time_t now = 0;
    float delay = 0.15; //ogni quanti secondi si vuole stampare un quadratino
    char quadratino = 254; //carattere ascii del quadratino
    COORD old_coord = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)); //prendo le coordinate del puntatore della console
    printf("\nEseguo connessione...\n");
    for (int i = 1; i <= 100; i++) { // itera 100 volte questo ciclo
        delay += i/100; //il delay diventa sempre piu' lungo ad ogni iterazione
        now = clock();  //inizializzo il timer
        gotoxy(old_coord.Y, i); //imposto il cursore della console alla posizione dove voglio stampare il quadratino
        printf("%c", quadratino); //stampo il quadratino
        gotoxy(old_coord.Y, 102); //imposto il cursore nella stessa riga ma dopo 102 caratteri
        printf("%d%%", i);        //e stampo la percentuale di caricamento
        if(i>=98) delay = 2; //appena si avvicina alla fine il delay viene impostato a 2 secondi
        for( ; clock() - now < delay * CLOCKS_PER_SEC; );
    }
    printf("\n\nconnessione eseguita con successo :)\n\n");
    now = clock();
    for( ; clock() - now < 2 * CLOCKS_PER_SEC; ); //aspetto 2 secondi prima di ritornare al main()
}

//gestisce la console prendendo le coordinate del puntatore nel momento in cui la si richiama
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput) //prende le coordinate del cursore nel momento in cui la si chiama
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

void gotoxy(int y, int x) //mette il cursore della console nella posizione x y 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = GetConsoleCursorPosition(hConsole);
    coord.X = x;
    coord.Y = y;
    if (!SetConsoleCursorPosition(hConsole, coord)){} //gestisce gli errori
}