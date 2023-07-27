#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

//definiamo le grandezze del campo da gioco
//cambiare quasti valore se si vuole aumentare la grandezza del campo da gioco
#define ROWS 9 
#define COLUMNS 9

int campo[ROWS][COLUMNS];  //dichiariamo la matrice del campo da gioco (memorizzo al suo interno valori da 9 a 18, per le celle non scoperte e da -1 a 8 per le celle scoperte) 
int numero_difficolta =-1; //difficolta
int numero_mine;           //numero di mine totali
int riga_scelta=0;          
int colonna_scelta=0;
bool game_status = true;

void visualizza_casella_ij(int a, int b); //funzione che selezionata una casella la scopre e in caso scopre le adiacenti 
void inizializza_gioco();                 //inizializza il campo da gioco
void scegli_posizione();                  //richiede la cella 
void visualizza();                        //stampa il campo da gioco
void scegli_difficolta();                 //richiede la difficiolta
void controlla_vincita();                 //controla se eil giocatore ha vinto


//FUNZIONI DEI COMANDI 
//WINDOWS
#define clear() system("cls");
void gotoxy(int y, int x)
{
    COORD coord;
    coord.X = x-1;
    coord.Y = y-1;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!SetConsoleCursorPosition(hConsole, coord)){}
}

//MAC / LINUX
//#define clear() printf("\033[H\033[J")
//#define gotoxy(y,x) printf("\033[%d;%dH", (y), (x))

//intervalli su cui si ci puo muovere con le frecciette nel campo minato
int x_min=1, y_min=3; //compresi
int x_max=COLUMNS, y_max=ROWS+2; //compresi

//define deie comandi per muoversi
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77

#define ESCAPE 27
#define ENTER 13

int main()
{
    /*Gruppo:
    Matricola:  Alex Mazzoni       E-mail: alex.mazzoni3@studio.unibo.it
    Matricola:  Giovanni Luca      E-mail: giovanni.luca@studio.unibo.it
    Matricola:  Michele Farneti    E-mail: michele.farneti@studio.unibo.it
    */

    printf("\nSettimana 6 - Esercizio 2\t E-mail di riferimento: alex.mazzoni3@studio.unibo.it\n\n");
    
    printf("Benvenuto in CAMPO MINATO!\n");

    bool partitainiziata=false;
    //menu che richiede la difficolta senno non e' possibile giocare
    int voce_selezionata=0;
    do
    {
        printf("\nInserisci il numero della voce che desideri effettuare: ");
        if(numero_difficolta!=-1)
            printf("\n\t1. Gioca.");
        printf("\n\t2. Imposta difficolta.\n");
        printf("\t0. Termina il programma.\n");
        printf("\ninserire il numero della voce che vuole effettuare: ");
        scanf("%d", &voce_selezionata);
        fflush(stdin);
        switch (voce_selezionata) {
        case 0://esce
            break;
        case 1:
            if(numero_difficolta!=-1)//In caso l'utente abbia inserito la difficolta, inizializzo il campo in relazione alla difficolta
            {
                inizializza_gioco();
                voce_selezionata = 0; //esci dal ciclo in modo che cominci il gioco
                partitainiziata=true;
            }
            break;
        case 2:
            scegli_difficolta();
            break;
        }
        printf("\n\n");
    } while (voce_selezionata!=0);

    //faccio cominciare la partita
    if(partitainiziata)
    {
        do{
            scegli_posizione(); //stampa il campo e richiede la posizione
            visualizza_casella_ij(riga_scelta,colonna_scelta);  //funzione ricorsiva che scopre la cella selezionata
            controlla_vincita(); //controlla se ha vinto
        }
        while(game_status); //controlla se il gioco e' finito oppure no
        visualizza();
    }
    printf("\n\nAlla prossima!!");

    return 0;
}

int controlla_bordi(int *riga, int delta_i, int *colonna, int delta_j) {//funzione che controlla dati due indici se escono dai limiti della matrice CAMPO
    if(*riga + (delta_i)<0)
    {*riga = *riga - (delta_i);*colonna = *colonna - (delta_j);return 0;}
    if(*riga + (delta_i)>=ROWS)
    {*riga = *riga - (delta_i);*colonna = *colonna - (delta_j);return 0;}

    if(*colonna + (delta_j)<0)
    {*riga = *riga +- (delta_i);*colonna = *colonna - (delta_j);return 0;}
    if(*colonna + (delta_j)>=COLUMNS)
    {*riga = *riga - (delta_i);*colonna = *colonna - (delta_j);return 0;}
}

void visualizza_casella_ij(int y, int x) {
    if(campo[y][x]==9)     //controlla se la cella selezionata e' una bomba se lo e' 
    {
        campo[y][x] -=10;         //la scopre
        game_status = false;      //fa terminare la partita
        printf("Hai perso!\n\n"); //e stampa un messaggio di sconfitta
    }
    else if(campo[y][x]>8)//se invece la cella selezionata deve essere scoperta
    {
        campo[y][x] -=10; //la scopre
        if(campo[y][x]==0) // e se e' 0 controlla tutte le direzioni e si richiamano a vicenda per tutti gli 0 nelle direzioni
        {
            //controlla direzioni
            for (int i=y, j=x, d=0; d<8; ) //8 direzioni
            {
                switch (d)
                {
                    case 0:     //direzione ⬉
                        controlla_bordi(&i,-1, &j, -1); //controlla se non esce dalla matrice
                        if(campo[i-1][j-1]==10) //controlla se e' uno 0 se lo e' si richiama e sposta l'elemento selezionato allo 0 uscito
                        {
                            i--;j--;
                            visualizza_casella_ij(i,j);
                        }
                        else //altrimenti se non e' 0 cambia direzione e resetta la posizione allo 0 di partenza per l'istanza della funzione
                        {
                            d++;
                            i=y;j=x;
                        }
                        break;
                    case 1:     //direzione ↑
                        controlla_bordi(&i,-1, &j, 0);
                        if(campo[i-1][j]==10)
                        {
                            i--;
                            visualizza_casella_ij(i,j);
                        }
                        else
                        {
                            d++;
                            i=y;j=x;
                        }
                        break;
                    case 2:     //direzione ⬈
                        controlla_bordi(&i,-1, &j, +1);
                        if(campo[i-1][j+1]==10)
                        {
                            i--;j++;
                            visualizza_casella_ij(i,j);
                        }
                        else
                        {
                            d++;
                            i=y;j=x;
                        }
                        break;
                    case 3:     //direzione →
                        controlla_bordi(&i,0, &j, +1);
                        if(campo[i][j+1]==10)
                        {
                            j++;
                            visualizza_casella_ij(i,j);
                        }
                        else
                        {
                            d++;
                            i=y;j=x;
                        }
                        break;
                    case 4:     //direzione ⬊
                        controlla_bordi(&i,+1, &j, +1);
                        if(campo[i+1][j+1]==10)
                        {
                            i++;j++;
                            visualizza_casella_ij(i,j);
                        }
                        else
                        {
                            d++;
                            i=y;j=x;
                        }
                        break;
                    case 5:     //direzione ↓
                        controlla_bordi(&i,+1, &j, 0);
                        if(campo[i+1][j]==10)
                        {
                            i++;
                            visualizza_casella_ij(i,j);
                        }
                        else
                        {
                            d++;
                            i=y;j=x;
                        }
                        break;
                    case 6:     //direzione ⬋
                        controlla_bordi(&i,+1, &j, -1);
                        if(campo[i+1][j-1]==10)
                        {
                            i++;j--;
                            visualizza_casella_ij(i,j);
                        }
                        else
                        {
                            d++;
                            i=y;j=x;
                        }
                        break;
                    case 7:     //direzione ←
                        controlla_bordi(&i,0, &j, -1);
                        if(campo[i][j-1]==10)
                        {
                            j--;
                            visualizza_casella_ij(i,j);
                        }
                        else
                        {
                            d++;
                            i=y;j=x;
                        }
                        break;
                }
                if(campo[i][j]>8) //scopre sempre la casella se non e' stata scoperta
                    campo[i][j] -=10; //decrementa perche' selezionato
            }
        }
    }
}

void inizializza_gioco() {
    srand(time(NULL));
    int i;
    int riga_casuale;
    int colonna_casuale;

    //Vado a selezionare il numero di mine che saranno presenti nel campo in base alla difficolta scelta.
    switch (numero_difficolta) {
        case 2:
            numero_mine = 5;
            break;
        case 3:
            numero_mine = 10;
            break;
        case 4:
            numero_mine = 15;
            break;
        case 5:
            numero_mine = 20;
            break;
        default:
            numero_mine = 1;
    }

    //Utilizzo una matrice inizializzandola a 10 che equivale a 0 ma coperto. e eseguendo al valore una sottrazione di dice si trova il suo vero valore da scoperta
    //esempio una mina equivale a -1 da scoperta percio' a 9 da coperta, 5 scoperto equivale a 15 da coperto
    for (i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            campo[i][j] = 10;
        }
        printf("\n");
    }

    //Genero casualmente le mine, facendo attenzione a non generarle nelle stesse posizioni
    i=0;
    do
    {
        riga_casuale = rand() % 9;
        colonna_casuale = rand() % 9;
        if(campo[riga_casuale][colonna_casuale]==10)
        {
            campo[riga_casuale][colonna_casuale] -= 1;
            i++;
        }
    } while (i < numero_mine);

    printf("\n\nIn questo campo sono nascoste %i mine, attenzione!\n",numero_mine);

    //inizio a memorizzare nelle caselle del campo i relativi numeri relativi al numero di mine adiacenti a loro.
    //percio' scorre ogni casella contando quante mine ci sono nelle celle sdiacenti corrispettive e memorizza in seguito il numero di mine contato nella cella.
    for (i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            if(campo[i][j] != 9)
            {
                int count_bombe=0;
                if(i>0)
                {
                    if(campo[i-1][j] == 9)
                    {
                        count_bombe++;
                    }
                    if(j>0)
                    {
                        if(campo[i-1][j-1] == 9)
                        {
                            count_bombe++;
                        }
                    }
                    if(j<8)
                    {
                        if(campo[i-1][j+1] == 9)
                        {
                            count_bombe++;
                        }
                    }
                }

                if(i<8)
                {
                    if(campo[i+1][j]==9)
                    {
                        count_bombe++;
                    }
                    if(j<8)
                    {
                        if(campo[i+1][j+1] == 9)
                        {
                            count_bombe++;
                        }
                    }
                    if(j>0)
                    {
                        if(campo[i+1][j-1] == 9)
                        {
                            count_bombe++;
                        }
                    }
                }
                if(j>0)
                {
                    if(campo[i][j-1]==9)
                    {
                        count_bombe++;
                    }
                }
                if(j<8)
                {
                    if(campo[i][j+1]==9)
                    {
                        count_bombe++;
                    }
                }
                campo[i][j]+=count_bombe;
            }
        }
    }
    
}

void scegli_posizione() {//richiede la posizione a schermo
    int x=colonna_scelta+x_min, y=riga_scelta+y_min; //x[1, 9] //y[3, 11]
    clear(); //pulisce lo schermo
    printf("Muoversi con le frecce direzionali e premere ENTER per selezionare la mina! (se si bugga premere piu' volte le frecce)\n\n");
    visualizza(); //visualizza iil campo da gioco
    gotoxy(y, x*4);// muove il cursore nella posizione ultima
    char c = ' ';
    while (c!=ENTER) //e permette di muoversi all'interno dello schermo finche' non si preme con enter una cella
    {
        c = getch();
        switch (c)
        {
            case ARROW_UP:    // key up
                if(y-1>=y_min)
                    y--;
               break;
           case ARROW_DOWN:    // key down
                if(y+1<=y_max)
                    y++;
               break;
           case ARROW_RIGHT:    // key right
                if(x+1<=x_max)
                    x++;
               break;
           case ARROW_LEFT:    // key left
                if(x-1>=x_min)
                    x--;
               break;
        }
        gotoxy(y, (x*4));// muove il cursore
    }
    gotoxy(y_max+1,x_max+1);//va alla fine della matrice stampata per stampare successivamente
    printf("\n\n");
    // printf("\n\n colonna_scelta=%d\n", x-1);
    // printf("riga_scelta=%d\n", y-1);
    colonna_scelta = x-x_min;
    riga_scelta = y-y_min;
}

void visualizza() //stampa in base alle celle scoperte o coperte il campo
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            if(campo[i][j]>=9)
            {
                printf("%4c", 'X');
            }
            else
            {
                printf("%4d", campo[i][j]);
            }
        }
        printf("\n");
    }

}

void scegli_difficolta() {
    //Faccio reinserire all'utente la difficoltá desiderata fino a quando non inserisce un valore contemplato
    do
    {
        printf("\n\tScegli una difficolta da 1 a 5 inclusi: ");
        scanf("%d", &numero_difficolta);
        fflush(stdin);
    }
    while(numero_difficolta<1 ||numero_difficolta >5);

    printf("\n\t\tDifficolta scelta: %d / 5", numero_difficolta);
}

void controlla_vincita() {
    int count_spazirimasti=0;
    for (int i = 0; i < ROWS; i++)//scorre ogni cella del campo da gioco e conta quante celle totali coperte ci sono
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            if(campo[i][j]>8)
            {
                count_spazirimasti++;
            }
        }
    }

    if(count_spazirimasti==numero_mine) //se le celle coperte rimaste corrispondono al numero totali di mine della partita il giocatore ha vinto e termina la partita.
    {
        game_status=false;
        printf("Hai vinto, Bravo!!!\n\n");
    }
    
}