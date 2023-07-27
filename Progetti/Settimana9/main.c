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

//inserire come caselle totali un quadrato perfetto, poiche' il tabellone deve essere un quadrato
#define CASELLE_TOTALI 25
//costanti della casella in ASCII
#define GRANDEZZA_CASELLA_Y 3//compresi
#define GRANDEZZA_CASELLA_X 8//compresi

#define MAX_DOMANDE 8 //E' IL NUMERO MASSIMO DELLE DOMANDE (E RISPOSTE), aggiornarlo se si vogliono nuove domande
#define PATH_DOMANDE "./domande.txt"
#define PATH_RISPOSTE "./risposte.txt"

struct giocatore
{
	char identificativo; //pedina che verra' visualizzata nel tabellone
   	char nickname[20];
   	int colore;
   	int posizione;		 //posizione del giocatore da [0, CASELLE_TOTALI]
   	COORD coordinate_label; //posizione in termini di coordinate nella console della label
};

struct casella
{
   	COORD coordinate_casella; //serve per stampare le caselle successive
   	COORD coordinate_giocatori; //serve per stampare i giocatori in modo appropriato all'interno delle caselle
  	int giocatori_presenti; //serve per l'algoritmo di visualizzazione corretta del giocatore
   	int speciale; //per memorizzare la casella dove il giocatore dovra' andare se capita in essa (oscala, oserpente o obuco)
};

struct casella *caselle[CASELLE_TOTALI];
int count_caselle=0;
struct giocatore giocatori[5];
int count_giocatori=0;

char *domande[MAX_DOMANDE];
char *risposte[MAX_DOMANDE];
int count_domande_risposte=0;

//linked list per la coda (gestione dei turni)
struct Node {
    int indice_giocatore;
    struct Node *next;
};

//mi raccomando mettere le funzione qua ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void gameMaster();
bool gameState();
void inizializzaFile();
void inizializzaCampo();
void inizializzaGiocatori();

void gotoCasella();
int lanciaDado();
bool richiediDomanda();

void setupBox();
void setupCasella();
//mi raccomando mettere le funzione qua ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
    /*Gruppo:
    Matricola:  Alex Mazzoni       E-mail: alex.mazzoni3@studio.unibo.it
    Matricola:  Giovanni Luca      E-mail: giovanni.luca@studio.unibo.it
    Matricola:  Michele Farneti    E-mail: michele.farneti@studio.unibo.it
    */

    printf("\nSettimana 9 - Esercizio 1\t E-mail di riferimento: alex.mazzoni3@studio.unibo.it\n\n");
	srand(time(NULL));
	
    printf("Quante persone partecipano al gioco Snakes & Ladders? ");
	scanf("%d", &count_giocatori);
	fflush(stdin);

	//inizializza domande e risposte mettendole dentro a due array di indice uguale
	inizializzaFile();

	//inizializzazione del gioco
	inizializzaGiocatori(); //prima i giocatori poi il campo
	inizializzaCampo();		
	gameMaster(); //e' la funzione che gestisce i turni la vittoria e la sconfitta e tutti gli effetti fdurante il gioco (ovviamente tutto in sottofunzioni).

    return 0;
}

void gameMaster() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	clock_t now = clock(); //variabile clock perpermettere di aspettare che l'utente legga le frasi, senza eseguire il gioco istantaneamente

	COORD coord_MessageBox; //mi salvo le coordinate per lo spazio riservato, dove stampare le informazioni (o frasi) aggiuntive durante l'esecuzione del gioco  
	coord_MessageBox.Y = caselle[CASELLE_TOTALI-1]->coordinate_casella.Y + 4;
	coord_MessageBox.X = 0;
	//creare la coda (linked list) per la gestione dei turni
	int vincitore = 0; //variabile che serve per sapere quale giocatore ha vinto

	//inizializzazione della coda (gestione dei turni), la creo inserendo in ogni nodo un valore che parte dal numero di giocatori totali e arriva fino a 0
	//percio' il numero di nodi restera' fisso cambiera' solo una variabile al suo interno ed essa dipende dalla posizione del nodo nella lista, essa (la variabile)
	//indica che sta a quel giocatore (indice_giocatore)
	//primo nodo (testa)
	struct Node *head = malloc(sizeof(struct Node));
	int tmp_count_giocatori = count_giocatori;
	tmp_count_giocatori--;
	head->indice_giocatore = tmp_count_giocatori;
	head->next = NULL;
	do //creazione degli altri nodi
	{
		struct Node *newNode = malloc(sizeof(struct Node));
		tmp_count_giocatori--;
		newNode->indice_giocatore = tmp_count_giocatori;

		// Add the new node to the front of the linked list
		newNode->next = head;
		head = newNode;
	} while (tmp_count_giocatori!=0);

	struct Node *turno = head; //testa per la lista dei turni (linked list circolare) (ricomincia sempre!)

	//ciclo per le e l'avanzamento del gioco in corso (il ciclo termina appena un giocatore finisce la partita!)
	do
	{
		setupBox(coord_MessageBox, 80); //ripulisce la message box (serve per stampare frasi aggiuntive informazioni durante il gioco).
		
		//aspetta 0.4 secondi prima eseguire le altre istruzioni
        now = clock();
        for( ; clock() - now < 0.4 * CLOCKS_PER_SEC; ); 

		if(turno==NULL) //se la coda e' finita ricomincia dalla testa
			turno = head;

		if(turno->indice_giocatore!=999) // controlla se il giocatore puo' effettuare il turno oppure no
		{		
			//lancia il dado aspettando un input e muovendo la pedina
			setupBox(coord_MessageBox, 80); //ripulisce la message box e imposta il cursore della casella su di essa per stampare un messaggio
			printf("%s premi per lanciare i dadi!", giocatori[turno->indice_giocatore].nickname);
			//funzione che permette di lanciare il dado e spostare la pedina sulla casella desiderata
			gotoCasella((lanciaDado(turno->indice_giocatore) + giocatori[turno->indice_giocatore].posizione), turno->indice_giocatore);
			//setupBox(coord_MessageBox); //ripulisce la message box
			
			//caselle speciali
			if (caselle[giocatori[turno->indice_giocatore].posizione]->speciale==999) //obuchi
			{
				//stampo un messaggio 
				setupBox(coord_MessageBox, 80);
				printf("\tOh no %s, sei finito in un buco, stai fermo per un turno!", giocatori[turno->indice_giocatore].nickname);
				//sovrascrivo il turno del giocatore per fargli saltare un turno
				turno->indice_giocatore = 999;
				//aspetto 2 secondi
				now = clock();
        		for( ; clock() - now < 2 * CLOCKS_PER_SEC; ); 
			}
			else if(caselle[giocatori[turno->indice_giocatore].posizione]->speciale<0) //serpenti
			{
				setupCasella(turno->indice_giocatore);//ripulisce il giocatore da quella casella
				//imposta la nuova posizione in base a dove puntava la coda del serpente
				giocatori[turno->indice_giocatore].posizione = caselle[giocatori[turno->indice_giocatore].posizione]->speciale * -1;
				gotoCasella(giocatori[turno->indice_giocatore].posizione, turno->indice_giocatore);

				setupBox(coord_MessageBox, 80); //stampo un messaggio 
				printf("\tOh no %s, sei finito su un serpente!", giocatori[turno->indice_giocatore].nickname);
				
				//aspetta 2 secondi
				now = clock();
        		for( ; clock() - now < 2 * CLOCKS_PER_SEC; ); 
			}
			else if(caselle[giocatori[turno->indice_giocatore].posizione]->speciale>0) //scale
			{
				//fai la domanda se risponde correttamente la usa senno no
				if(giocatori[turno->indice_giocatore].posizione < caselle[giocatori[turno->indice_giocatore].posizione]->speciale) //puo' prendere la scala
				{
					setupBox(coord_MessageBox, 80);
					printf("\t%s sei finito in una scala, rispondi alla domanda per usarla!", giocatori[turno->indice_giocatore].nickname);
					
					//aspetta 1 secondo prima di andare avanti
					now = clock();
        			for( ; clock() - now < 1 * CLOCKS_PER_SEC; );

					//mette il cursore alla box per richiedere la domanda
					setupBox(coord_MessageBox, 80);
					if(richiediDomanda(rand() % count_domande_risposte)) { //se risponde correttamente usa la scala
						//stampo un messaggio 
						setupBox(coord_MessageBox, 80);
						printf("\tbravo %s, hai risposto correttamente!", giocatori[turno->indice_giocatore].nickname);	

						setupCasella(turno->indice_giocatore); //ripulisce il giocatore da quella casella
						//mette la posizione del giocatore alla posizione che sara' usando la scala
						giocatori[turno->indice_giocatore].posizione = caselle[giocatori[turno->indice_giocatore].posizione]->speciale;
						gotoCasella(giocatori[turno->indice_giocatore].posizione, turno->indice_giocatore);
					}
					else {
						//stampo un messaggio 
						setupBox(coord_MessageBox, 80);
						printf("\tsbagliato %s, rimani a questa casella!", giocatori[turno->indice_giocatore].nickname);	
					}
					//aspetta 2 secondi prima di andare avanti
					now = clock();
        			for( ; clock() - now < 2 * CLOCKS_PER_SEC; ); 
				}
			}
		}
		else //quando un giocatore e' finito nella casella obuco ora deve reimpostare la lista dei turni correttamente
		{
			int count=0; //percio conta da quanti nodi e' formata la lista e in base agli elementi che ci sono e' il turno del giocatore
			struct Node *tmp = head;
			while(tmp != turno) {
				count++;
				tmp = tmp->next;
			}
			turno->indice_giocatore=count;
		}
		turno = turno->next; //passa al giocatore dopo.
	} while (gameState(&vincitore)); //ciclo che si termina appena un giocatore vince

	//va alla posizione sotto il tabellone per stampare un messaggio di vittoria
	setupBox(coord_MessageBox, 80);
	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | RGB(giocatori[vincitore].colore, 0, 0));
	printf("\tBravoo %s, hai vinto!", giocatori[vincitore].nickname);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

bool richiediDomanda(int domanda_generata) { //richiede una domanda e se risponde correttamente lo restituisce
	printf("%s ", domande[domanda_generata]);
	//printf("%s", risposte[domanda_generata]);//c'e' un \0 o \n
	char tmp[100];
	scanf("%s", tmp);
	if(strcmp(risposte[domanda_generata], tmp) == 0)
		return true;

	return false;
}

void inizializzaFile() { //crea e legge i file memorizzandoli in due vettori
	FILE *file;
	char x;

	file = fopen(PATH_DOMANDE, "w"); //crea file domande
	fprintf(file, "88 + 11 =\n"
				  "53 - 13 =\n"
				  "35 - 15 =\n"
    			  "20 - 10 =\n"
				  "49 *  2 =\n"
				  "36 /  6 =\n"
				  "20 *  5 =\n");
    fclose(file);
	        
	file = fopen(PATH_RISPOSTE, "w"); //crea file domande
	fprintf(file,"99\n"
    			 "40\n"
    			 "20\n"
    			 "10\n"
    			 "98\n"
    			 "6\n"
     			 "100\n"); 
    fclose(file);

	//inserisco le domande nel vettore domande
	file = fopen(PATH_DOMANDE, "r");   //mode: r → sola-lettura.
	count_domande_risposte=0;
    if(file != NULL)
    {
        int i=0;
        char buffer_lettura[100];
        while (!feof(file))
        {
            fscanf(file, "%c", &x);
            if(x=='\n')
            {
                domande[count_domande_risposte] = malloc(sizeof(char) * i);
                if (domande[count_domande_risposte] != NULL) 
                {
                    strcpy(domande[count_domande_risposte], buffer_lettura);
					domande[count_domande_risposte][i]='\0';
                    count_domande_risposte++;
                }
                i = 0;
            }
            else
            {
                buffer_lettura[i] = x;
                i++;
            }
        }
        fclose(file);
    }

	//e le risposte nel vettore risposte
	file = fopen(PATH_RISPOSTE, "r");   //mode: r → sola-lettura.
	count_domande_risposte=0;
    if(file != NULL)
    {
        int i=0;
        char buffer_lettura[100];
        while (!feof(file))
        {
            fscanf(file, "%c", &x);
            if(x=='\n')
            {
                buffer_lettura[i] = x;
                risposte[count_domande_risposte] = malloc(sizeof(char) * i);
                if (risposte[count_domande_risposte] != NULL) 
                {
                    strcpy(risposte[count_domande_risposte], buffer_lettura);
					risposte[count_domande_risposte][i]='\0';
                    count_domande_risposte++;
                }
                i = 0;
            }
            else
            {
                buffer_lettura[i] = x;
                i++;
            }
        }
        fclose(file);
    }
	count_domande_risposte--;
}

void setupBox(COORD coord_MessageBox, int spazi) {	//mette il puntatore nella Box dove stampare le frasi aggiuntive e la ripulisce
	gotoxy(coord_MessageBox.Y, coord_MessageBox.X); 
	for (int i = 0; i < spazi; i++) printf(" ");
	gotoxy(coord_MessageBox.Y, coord_MessageBox.X);
}

bool gameState(int *vincitore) { //funzione che controlla se un giocatore ha vinto
	for (int i = 0; i < count_giocatori; i++)
	{
		if(giocatori[i].posizione == (CASELLE_TOTALI-1))
		{
			*vincitore=i;
			return false;
		}
	}
	return true;
}

int lanciaDado(int indice_giocatore) { //genera un numero casuale [1, 6], aspetta un input e lo restituisce
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(giocatori[indice_giocatore].coordinate_label.Y, giocatori[indice_giocatore].coordinate_label.X);
	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | RGB(giocatori[indice_giocatore].colore, 0, 0));
	printf("%s (Your turn)", giocatori[indice_giocatore].nickname);
	//devi pulire prima la console 
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	getch(); //aspetta che prema qualcosa prima di generare il numero e passare alla casella successiva
	
	setupBox(giocatori[indice_giocatore].coordinate_label, 30); //pulisce la casella e ci ristampa il suo nome
	gotoxy(giocatori[indice_giocatore].coordinate_label.Y, giocatori[indice_giocatore].coordinate_label.X);
	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | RGB(giocatori[indice_giocatore].colore, 0, 0));
	printf("%s", giocatori[indice_giocatore].nickname);
	//devi pulire prima la console 
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	
	return (1 + (rand() / (RAND_MAX / (6 - 1 + 1) + 1)));
}

void gotoCasella(int casella, int indice_giocatore) { //data una posizione il programma sposta la pedina del giocatore inserito alla casella della posizione inserita
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//pulisci la casella precedente dal giocatore
	setupCasella(indice_giocatore);

	giocatori[indice_giocatore].posizione = casella;
	if(giocatori[indice_giocatore].posizione>=(CASELLE_TOTALI-1))
		giocatori[indice_giocatore].posizione = (CASELLE_TOTALI-1); //e il giocatore ha vinto.
	
	//sposta i giocatori in base a quanti c'e' ne sono
	gotoxy(caselle[giocatori[indice_giocatore].posizione]->coordinate_giocatori.Y, caselle[giocatori[indice_giocatore].posizione]->coordinate_giocatori.X + indice_giocatore);
	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | RGB(giocatori[indice_giocatore].colore, 0, 0));
	printf("%c", giocatori[indice_giocatore].identificativo);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void setupCasella(int indice_giocatore) { //e' una funzione grafica che ripulisce la casella ristampando tutti i giocatori presenti in quella casella tranne il giocatore che va via
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//deve prendere le coordinate della casella del giocatore ripulirla e controllare quanti giocatori ci stanno e stamparli
	gotoxy(caselle[giocatori[indice_giocatore].posizione]->coordinate_giocatori.Y, caselle[giocatori[indice_giocatore].posizione]->coordinate_giocatori.X); //ripuliscila
	printf("     ");

	//ora stampa i giocatori che ci sono in quella casella tranne il giocatore che si sta spostando.
	for (int i = 0; i < count_giocatori; i++)
	{
		if(i!=indice_giocatore)
		{
			if(giocatori[i].posizione==giocatori[indice_giocatore].posizione)
			{
				gotoxy(caselle[giocatori[i].posizione]->coordinate_giocatori.Y, caselle[giocatori[i].posizione]->coordinate_giocatori.X + i);
				SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | RGB(giocatori[i].colore, 0, 0));
				printf("%c", giocatori[i].identificativo);
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		}
	}
	
}

void inizializzaCampo() { //e' la funzione piu' complessa che genera il campo da gioco le caselle e le stampa
    clear();
	for (int i = 0; i < CASELLE_TOTALI; i++) caselle[i]=NULL; //inizializzo il vettore di struct

    //numero per la generazione di tutte le variabili in maniera automatica del campo in forma quadrata
	int quadrato_perfetto = (int) sqrt(CASELLE_TOTALI);

    //la prima casella e' fissa
	caselle[count_caselle] = malloc(sizeof(struct casella)); //istanza l'elemento del vettore
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    caselle[count_caselle]->coordinate_casella = GetConsoleCursorPosition(hConsole); //memorizza le coordinate del +in alto a sinistra
    printf("+-----+ ");
    gotoxy((caselle[count_caselle]->coordinate_casella.Y)+1, caselle[count_caselle]->coordinate_casella.X);
    printf("|     | ");
    gotoxy(caselle[count_caselle]->coordinate_casella.Y+2, caselle[count_caselle]->coordinate_casella.X);
    printf("+%3d  + ", count_caselle+1); //finisce di stampare la casella nel modo corretto e inizializza le altre variabili
    caselle[count_caselle]->coordinate_giocatori.Y = caselle[count_caselle]->coordinate_casella.Y+1;
    caselle[count_caselle]->coordinate_giocatori.X = caselle[count_caselle]->coordinate_casella.X+1;
    caselle[count_caselle]->giocatori_presenti = count_giocatori;
	caselle[count_caselle]->speciale = 0; // 0: vuol dire che non succede nulla, 999: obuco, negativo: serpente, positivo: scala.
	//stampa i giocatori nella casella 1
	for (int i = 0; i < count_giocatori; i++)
	{
		gotoxy(caselle[count_caselle]->coordinate_giocatori.Y, caselle[count_caselle]->coordinate_giocatori.X + i);
		SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | RGB(giocatori[i].colore, 0, 0));
		printf("%c", giocatori[i].identificativo);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
    count_caselle++;


    int divisore = quadrato_perfetto;
	int separatore = quadrato_perfetto;
	int indice_giocatore = 0;
    while(count_caselle<CASELLE_TOTALI) //gira tutte le caselle
    {   
		if(caselle[count_caselle]==NULL) //la inizializza se non e' gia' stato fatto prima
			caselle[count_caselle] = malloc(sizeof(struct casella)); //inizializzo le caselle

		//animazione
        clock_t now = clock();
        for( ; clock() - now < 0.06 * CLOCKS_PER_SEC; ); 

        //gestione stampa e variabili per la grafica delle caselle
        COORD previous_box = caselle[count_caselle-1]->coordinate_casella;

		//algoritmo per la stampa quadrata del tabellone
        if(count_caselle<separatore)       //destra
			previous_box.X += GRANDEZZA_CASELLA_X;
        else if(count_caselle==separatore) //giu
			previous_box.Y += GRANDEZZA_CASELLA_Y;
        else if(count_caselle<separatore+divisore) //sinistra
            previous_box.X -= GRANDEZZA_CASELLA_X;
        else if(count_caselle==separatore+divisore) //giu
        {
            previous_box.Y += GRANDEZZA_CASELLA_Y;
            separatore += divisore*2; //separatore = ?, divisore = 6
        }
		//stampa della casella nella posizione voluta
        caselle[count_caselle]->coordinate_casella = previous_box;
        gotoxy(caselle[count_caselle]->coordinate_casella.Y, caselle[count_caselle]->coordinate_casella.X);
        printf("+-----+ ");
        gotoxy(caselle[count_caselle]->coordinate_casella.Y+1, caselle[count_caselle]->coordinate_casella.X);
        printf("|     | ");
        gotoxy(caselle[count_caselle]->coordinate_casella.Y+2, caselle[count_caselle]->coordinate_casella.X);
        printf("+%3d  + ", count_caselle+1);
        caselle[count_caselle]->coordinate_giocatori.Y = caselle[count_caselle]->coordinate_casella.Y+1;
        caselle[count_caselle]->coordinate_giocatori.X = caselle[count_caselle]->coordinate_casella.X+1;
        
		//inizializzazione delle restanti variabili della casella
        caselle[count_caselle]->giocatori_presenti = 0;
		caselle[count_caselle]->speciale = 0;
		
		//creo uno spazio per ogni etichetta di ogni giocatore
		if(indice_giocatore<count_giocatori)
		{
			if(count_caselle==separatore || count_caselle==(separatore-1))
			{
				giocatori[indice_giocatore].coordinate_label.Y = caselle[count_caselle]->coordinate_casella.Y+1;
				giocatori[indice_giocatore].coordinate_label.X = caselle[count_caselle]->coordinate_casella.X+32;
				//giocatori[indice_giocatore].coordinate_label.Y = (previous_box.Y-GRANDEZZA_CASELLA_Y)+1;
				//giocatori[indice_giocatore].coordinate_label.X = previous_box.X+32;
				gotoxy(giocatori[indice_giocatore].coordinate_label.Y, giocatori[indice_giocatore].coordinate_label.X);
				SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | RGB(giocatori[indice_giocatore].colore, 0, 0));
				printf("%s", giocatori[indice_giocatore].nickname);
				indice_giocatore++;
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //reset color
			}
		}

		//genero le caselle speciali (da sistemare ci sono diversi bug sulla generazione delle caselle in posti gia' utilizzati)
		if(count_caselle<CASELLE_TOTALI-1)
		{
			bool speciale = ((rand() % (quadrato_perfetto-1)) + 1) == 1; //ogni tanto decide di generare una casella speciale
			if(speciale)
			{
				int cosa = ((rand() % 3) + 1);
				switch (cosa)
				{
				case 1: //serpenti
					if(count_caselle >= quadrato_perfetto)
					{
						do
						{
							cosa = (1 + (rand() / (RAND_MAX / ((count_caselle-3) - 1 + 1) + 1)))*-1;
							speciale = false; //riciclo la variabile
							for (int i = 0; i < CASELLE_TOTALI; i++)
							{
								if(caselle[i]!=NULL) 
								{
									if(caselle[i]->speciale<0)
									{
										if(caselle[i]->speciale==cosa) //nessun altra casella deve contenere quella casella
											speciale=true;
									}
									else
									{
										if(caselle[i]->speciale==(cosa*-1)) //nessun altra casella deve contenere quella casella
											speciale=true;
									}
								}
							}
							if(caselle[(cosa*-1)]!=NULL)
							{
								if(caselle[(cosa*-1)]->speciale!=0)
									speciale=true;
							}
						} while (speciale);
						caselle[count_caselle]->speciale = cosa; //memorizzo la posizione della coda del serpente
					}
					break;
				case 2: //scale
					if(count_caselle<CASELLE_TOTALI-quadrato_perfetto)
					{
						do
						{
							cosa = (count_caselle+3) + (rand() / (RAND_MAX / ((CASELLE_TOTALI-1) - (count_caselle+3) + 1) + 1));
							speciale = false; //riciclo la variabile

							if(cosa==CASELLE_TOTALI-1) //se la scala va dalla casella (count_caselle) alla casella cosa (cosa == alla casella finale), ne genera un altra
							{
								speciale = true;
							}
							else
							{
								for (int i = 0; i < CASELLE_TOTALI; i++) //controlla se la casella generata (cosa) e' gia' occupata dai serpenti oppure se e' gia' "speciale"
								{
									if(caselle[i]!=NULL) 
									{
										if(caselle[i]->speciale<0)
										{
											if((caselle[i]->speciale*-1)==cosa) //nessun altra casella deve contenere quella casella
												speciale=true;
										}
										else
										{
											if(caselle[i]->speciale==cosa) //nessun altra casella deve contenere quella casella
												speciale=true;
										}
									}
									if(caselle[cosa]!=NULL)
									{
										if(caselle[cosa]->speciale!=0)
											speciale=true;
									}
								}
							}
						} while (speciale);
						caselle[count_caselle]->speciale = cosa; //memorizzo la posizione della coda del serpente
					}
					break;
				case 3: //buchi
					speciale = false; //riciclo la variabile
					for (int i = 0; i < CASELLE_TOTALI; i++)
					{
						if(caselle[i]!=NULL) 
						{
							if(caselle[i]->speciale<0)
							{
								if((caselle[i]->speciale*-1)==count_caselle)
									speciale=true;
							}
							else
							{
								if(caselle[i]->speciale==count_caselle)
									speciale=true;
							}
						}
					}
					
					if(!speciale)
						caselle[count_caselle]->speciale = 999;
					
					break;
				}
			}
		}

		count_caselle++; //passo alla casella successiva
    }

	//stampo le caselle speciali con colori e nomi
	int colors = count_giocatori+1; //i primi colori sono riservati ai giocatori
	for (int i = 0; i < CASELLE_TOTALI; i++) //gira tutte le caselle
	{
		if(caselle[i]->speciale==999) //e' un buco
		{
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | RGB(0, 0, 0));
        	gotoxy(caselle[i]->coordinate_casella.Y, caselle[i]->coordinate_casella.X);
        	printf("+obuco+ ");
        	gotoxy(caselle[i]->coordinate_casella.Y+1, caselle[i]->coordinate_casella.X);
        	printf("|     | ");
        	gotoxy(caselle[i]->coordinate_casella.Y+2, caselle[i]->coordinate_casella.X);
        	printf("+%3d  + ", i+1);
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //reset color
		}
		else if(caselle[i]->speciale>0) //e' una scala
		{
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | RGB(colors, 0, 0));
        	gotoxy(caselle[i]->coordinate_casella.Y, caselle[i]->coordinate_casella.X);
        	printf("+scala+ ");
        	gotoxy(caselle[i]->coordinate_casella.Y+1, caselle[i]->coordinate_casella.X);
        	printf("|     | ");
        	gotoxy(caselle[i]->coordinate_casella.Y+2, caselle[i]->coordinate_casella.X);
        	printf("+%3d  + ", i+1);
			
			gotoxy(caselle[caselle[i]->speciale]->coordinate_casella.Y, caselle[caselle[i]->speciale]->coordinate_casella.X);
        	printf("+scala+ ");
        	gotoxy(caselle[caselle[i]->speciale]->coordinate_casella.Y+1, caselle[caselle[i]->speciale]->coordinate_casella.X);
        	printf("|     | ");
        	gotoxy(caselle[caselle[i]->speciale]->coordinate_casella.Y+2, caselle[caselle[i]->speciale]->coordinate_casella.X);
        	printf("+%3d  + ", caselle[i]->speciale+1);
			colors++;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //reset color
		}
		else if(caselle[i]->speciale<0) //e' un serpente
		{
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | RGB(colors, 0, 0));
        	gotoxy(caselle[i]->coordinate_casella.Y, caselle[i]->coordinate_casella.X);
        	printf("+snake+ ");
        	gotoxy(caselle[i]->coordinate_casella.Y+1, caselle[i]->coordinate_casella.X);
        	printf("|     | ");
        	gotoxy(caselle[i]->coordinate_casella.Y+2, caselle[i]->coordinate_casella.X);
        	printf("+%3d  + ", i+1);
			
			gotoxy(caselle[(caselle[i]->speciale*-1)]->coordinate_casella.Y, caselle[(caselle[i]->speciale*-1)]->coordinate_casella.X);
        	printf("+snake+ ");
        	gotoxy(caselle[(caselle[i]->speciale*-1)]->coordinate_casella.Y+1, caselle[(caselle[i]->speciale*-1)]->coordinate_casella.X);
        	printf("|     | ");
        	gotoxy(caselle[(caselle[i]->speciale*-1)]->coordinate_casella.Y+2, caselle[(caselle[i]->speciale*-1)]->coordinate_casella.X);
        	printf("+%3d  + ", (caselle[i]->speciale*-1)+1);
			colors++;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //reset colors
		}

	}
	//gotoxy(caselle[CASELLE_TOTALI-1]->coordinate_casella.Y, caselle[CASELLE_TOTALI-1]->coordinate_casella.X); //mette il puntatore alla fine del tabellone
	//printf("\n\n");
	
	//finestra di debug
	// for (int i = 0; i < CASELLE_TOTALI; i++)
	// {
	// 	printf("\nCasella %d\n\tspeciale: %d\n", i+1, caselle[i]->speciale);
	// }
}

void inizializzaGiocatori() { //inizializza il vettore giocatori con le informazioni base e richiedendole 
	bool input_statico=false;
	if(count_giocatori>5) //se si inserisce un numero che e' maggiore di 5 il programma mettera' le informazioni dei giocatori da per se
	{
		count_giocatori=3;
		input_statico=true;	
	}

	for (int i = 0; i < count_giocatori; i++) //richiedere tutti i dati dei giocatori
	{
		if(input_statico) {
			//per testare velocemente il gioco
			sprintf(giocatori[i].nickname, "Giocatore %d", i+1);
			giocatori[i].identificativo= i+65;
		}
		else {
			printf("\n");
			printf("Giocatore %d\n", (i+1));
			fflush(stdin);
			printf("\tinserire la pedina: ");
			scanf("%c", &giocatori[i].identificativo);		
			fflush(stdin);
			printf("\tinserire il nickname: ");
			scanf("%s", giocatori[i].nickname);
		}

		giocatori[i].posizione=0; //casella 1
		giocatori[i].colore= i+1; //i primi 5 sono riservati ai giocatori percio decidere un colore fra i primi 5

		//animazione prima di richiedere i dati del secondo giocatore
		clock_t now = clock();
        for( ; clock() - now < 0.4 * CLOCKS_PER_SEC; );
		printf("\n");
	}
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput) //funzioni di windows per la grafica
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

void gotoxy(int y, int x) //va alla posizione x y nella console
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = GetConsoleCursorPosition(hConsole);
    coord.X = x;
    coord.Y = y;
    if (!SetConsoleCursorPosition(hConsole, coord)){} //gestisce gli errori
}