#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//uso il materiale che ha condiviso il prof. Ravaioli, cosi possiamo avere delle funzioni per la console che valgono sia su mac sia su windows
//aggiornamento: non so per quale motivo e' meno cross-platform del previsto ma ho aggiunto le funzioni togliendo i colori e richiamando una funzione del cmd di windows in modo che con il cmd funzioni.
//io utilizzavo mingw il comando: gcc -std=c99 -o main.exe main.c
//per compilare ma mi ha fatto notare che effettivamente funzionava solo nella mia macchina.
#ifdef _WIN32 // valido sia per 32 che 64 bit
    #include <conio.h>
    #include <windows.h>
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
    #define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
    #endif

    static HANDLE stdoutHandle;
    static DWORD outModeInit;

    void setupConsole(void) {
        DWORD outMode = 0;
        stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        if(stdoutHandle == INVALID_HANDLE_VALUE) {
            exit(GetLastError());
        }
        if(!GetConsoleMode(stdoutHandle, &outMode)) {
            exit(GetLastError());
        }
        outModeInit = outMode;
        outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if(!SetConsoleMode(stdoutHandle, outMode)) {
            exit(GetLastError());
        }
    }
#else
    #include <termios.h>
    #include <unistd.h>

    int getch(void) {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr( STDIN_FILENO, &oldattr );
        newattr = oldattr;
        newattr.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
        return ch;
    }

    int getche(void) {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr( STDIN_FILENO, &oldattr );
        newattr = oldattr;
        newattr.c_lflag &= ~( ICANON );
        tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
        return ch;
    }
#endif

//ANSI COLOR CODES
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
//how to use color:
//printf("This is " RED "red" RESET " and this is " BLU "blue" RESET "\n");

//clear() e' utile per ripulire la console
#define clear() system("cls")
//#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))

#define MAX_ASCII 254 //i caratteri ascii vanno da 1 a 254 compresi
#define MIN_ASCII 1

int generaCarattereASCII(int delta, char lettera) { //queste istruzioni iniziali servono per far andare la generazione del carattere ascii sempre piu' vicina alla lettera che l'utente ha inserito
    int min = (int) lettera - delta; //esempio lettera inserita A = 65 e il delta e' 5, l'intervallo e' [60, 70]
    int max = (int) lettera + delta; //esempio lettera inserita A = 65 e il delta e' 5, l'intervallo e' [60, 70]
    if(min<MIN_ASCII || max>MAX_ASCII) {min=MIN_ASCII;max=MAX_ASCII;}//se il calcolo esce dall'intervallo [1, 254] lo sistema 

    int ASCII_generato = rand() % (max - min) + min; //genera il carattere ascii
    if(ASCII_generato < 7 || ASCII_generato > 15) // escludo i caratteri ASCII che non mostrano nulla
        return ASCII_generato;
    else
        return 49; //e ritorno 49 (numero a caso)
}

#define CARATTERE_DI_FINE_INSERIMENTO '#' //modificare questo carattere se si vuole terminare l'inserimento del testo con un carattere differente
#define LUNGHEZZA_STRINGA 200             //modificare questo valore se si vuola modificare la lunghezza del vettore di caratteri
#define GIRA 20                           //questo valore indica le volte massime che quel singolo carattere impieghera' per "uscire" giusto. 

#define VELOCITA_TESTO 0.05f     //velocita in secondi che ci mette prima di stampare la stringa
#define VELOCITA_CARATTERE 0.02f //velocita in secondi che ci mette prima di stampare un carattere

int main()
{
    /*Gruppo:
    Matricola:  Alex Mazzoni       E-mail: alex.mazzoni3@studio.unibo.it
    Matricola:  Giovanni Luca      E-mail: giovanni.luca@studio.unibo.it
    Matricola:  Michele Farneti    E-mail: michele.farneti@studio.unibo.it
    */
    printf("\nSettimana 5 - Esercizio 2\t E-mail di riferimento: alex.mazzoni3@studio.unibo.it\n");

    srand(time(NULL));

    int i = 0;
    char testo[LUNGHEZZA_STRINGA];
    
    // parallelo[i] e' un numero generato casualmente dall'intervallo [2, GIRA] che definisce quante volte quel singolo carattere deve cambiare prima di uscire il suo carattere effettivo
    int parallelo[LUNGHEZZA_STRINGA]; //vettore parallelo di interi del vettore di caratteri (in modo che ogni lettera avra' il proprio numero corrispondente)
    int max_parallelo = 0; //memorizza il numero massimo uscito dai numeri generati dall'intervallo [2, GIRA]

    char * colori[] = { RED, BLU, YEL, MAG, CYN, GRN}; //vettore di stringhe (per usare comodamente i colori)

    printf("\ninserisci il testo (inserire il carattere '%c'):\n", CARATTERE_DI_FINE_INSERIMENTO);
    for(i=0; i < sizeof(testo) - 1 && (testo[i]=getch()) != CARATTERE_DI_FINE_INSERIMENTO ; i++) //inserire il termine definito enlla define per terminare la testo oppure finire la lunghezza della stringa 
    {
        if(testo[i]=='\r') testo[i]='\n'; //se l'utente ha inserito l'andata a capo mostra anche l'effetto dell'andata a capo (senno eseguirebbe solo un '\r' carriage return)
        printf("%c", testo[i]); //stampa il carattere inserito.
        if(testo[i]!='\b') //se l'utente ha premuto il backspace
        { //altrimenti se non ha premuto il backspace
            parallelo[i] = rand() % (GIRA - 2) + 2; //generami quante volte il carattere deve uscire prima di "uscire" giusto
            if(parallelo[i]>max_parallelo)max_parallelo = parallelo[i]; //memorizza il valore massimo generato fra tutti quelli usciti
        }
        else i=i-2; //allora ritorna indietro a due elementi prima cosi ripete l'inserimento del carattere prima
    }
    int lunghezza_effettiva = i; //memorizza la lunghezza della stringa 
    testo[i+1] = '\0'; //alla fine del vettore inserisce sempre il valore 'NULL' nullo

    clock_t now;
    for (i = 0; i <= max_parallelo ; i++) //primo ciclo che finisce quando tutti i caratteri sono usciti giusti
    {
        int indice_colori = rand() % (5 - 0) + 0; //genera un colore dal vettore di colori [0,5]
        now = clock();
        for( ; clock() - now < VELOCITA_TESTO*CLOCKS_PER_SEC; ); // timer per la stampa della stringa
        
        clear();   //pulisce lo schermo
        printf("\n\n");
        for (int j = 0; j < lunghezza_effettiva; j++)   //ciclo che stampa la stringa (carattere per carattere)
        {
            now = clock();
            for( ; clock() - now < VELOCITA_CARATTERE*CLOCKS_PER_SEC; ); // con un timer definito per la stampa di ogni carattere
            
            if(i<parallelo[j])      //se esempio il carattere inserito a ha come corrispettivo il valore generato 5, se il ciclo e' alla 3a iterazione non mostra il carattere giusto ma dei valori generati casualmente
            {
                printf( "%c", colori[indice_colori] ,generaCarattereASCII( (((i+1)*100)/parallelo[j]), testo[j])); //versione senza colori
                //printf( "%s" "%c" RESET, colori[indice_colori] ,generaCarattereASCII( (((i+1)*100)/parallelo[j]), testo[j])); //mi stampa il carattere con il colore generato per l'iterazione di i,
            }    //e mi genera un carattereASCII che diventa sempre piu' vicino (in base alla tabella ASCII) al carattere che l'utente ha inserito.
            else
            {
                printf("%c", testo[j]); //versione senza colori
                //printf(WHT "%c" RESET, testo[j]); //altrimenti mostra il carattere giusto con il colore bianco
            }

        }
    }
    printf("\n\n");

    scanf("%i"); //per non far chiudere il cmd appena termina l'esecuzione

    return 0;
}