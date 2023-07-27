#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>

//FUNZIONI DEI COMANDI utili per l'inserimento e la scelta durante l'esecuzione del programma
//FUNZIONA SOLO SU WINDOWS
#include <windows.h> //il programma funziona perfettamente solo su windows
#define clear() system("cls");
COORD GetConsoleCursorPosition();
void gotoxy();

//define dei comandi per muoversi
#define ARROW_UP 72
#define ARROW_DOWN 80

#define ESCAPE 27
#define ENTER 13

#define JUMP 4 //define how many jump the cursor must do (y)

//end of graphics functions and defines

#define ABSOLUTE_FILE "./books.txt"

struct Node
{
    struct Node *next;

	char *title;
    char *author;
    char *publisher;
    int printing_year;
    char *genre;
    char *ISBN;
    float rating;
};

//funzioni: ---------------------------------------------------------------
void initializeBooksFromFile(struct Node **head);
void addBook(struct Node **head, char *title, char *author, char *publisher, int printing_year, char *genre, char *ISBN, float rating); 

void chooseBook(struct Node **head);
struct Node * deleteBook(struct Node **head, int n_node);
int printBooks(struct Node *head);
void booksSearch(struct Node *head, char *string);

char* getString();
char* replace_underscores_with_spaces(char const *str);


void saveBooksOnFile(struct Node *head);

void loading();
//-------------------------------------------------------------------------

int main() {
    /*Gruppo:
    Matricola:  Alex Mazzoni       E-mail: alex.mazzoni3@studio.unibo.it
    Matricola:  Giovanni Luca      E-mail: giovanni.luca@studio.unibo.it
    Matricola:  Michele Farneti    E-mail: michele.farneti@studio.unibo.it
    */

    printf("\nSettimana 10 - Esercizio 1\t E-mail di riferimento: alex.mazzoni3@studio.unibo.it\n\n");

    printf("\nConsiglio di mettere la console a schermo intero o comunque che la stampa dei libri sia presente in un'unica schermata!\n si possono aggiungere i libri anche solo scrivenedo nel file basta mettere uno spazio per separare i campi!\n");
    struct Node *head = NULL; //testa della linked list

    initializeBooksFromFile(&head);
    
    int choice;
    do { //solito menu che richiede una voce in input e finche' non si inserisce 0 si ripete
        fflush(stdin); //evitare ogni buffer da tastiera inserito accidentalmente ad ogni iterazione 
        printf("\nGestisci i Libri: \n");
        printf("\t1. Aggiungi un libro.\n");
        printf("\t2. Elimina un libro.\n");
        printf("\t3. Visualizza tutti i libri.\n");
        printf("\t4. Cerca per ?\n");
        printf("\t0. Termina il programma e salva i libri su file.\n");
        printf("\ninserisci il numero della scelta che si vuole effettuare: ");
        scanf("%d", &choice); 
        fflush(stdin);

        loading();  //piccolo caricamento

        switch (choice) {
            case 0:
                saveBooksOnFile(head);
                printf("\nArrivederci.");
                break;
            case 1:
                int buffer_printingyear;
                float buffer_rating;

                printf("\nTitolo: ");
                char *buffer_title = getString(); //richiedo in input una stringa e la memorizza in un puntatore

                printf("\nAutore: ");
                char *buffer_author = getString();  //richiedo in input una stringa e la memorizza in un puntatore

                printf("\nEditore: ");
                char *buffer_publisher = getString();   //richiedo in input una stringa e la memorizza in un puntatore

                printf("\nAnno di pubblicazione: ");
                scanf("%d", &buffer_printingyear);
                fflush(stdin);

                printf("\nGenere: ");
                char *buffer_genre = getString();   //richiedo in input una stringa e la memorizza in un puntatore

                printf("\nISBN: ");
                char *buffer_ISBN = getString();    //richiedo in input una stringa e la memorizza in un puntatore

                printf("\nValutazione: ");
                scanf("%f", &buffer_rating);
                fflush(stdin);

                //stampo il libro inserito
                printf("%s\t\t%s\n", replace_underscores_with_spaces(buffer_title), replace_underscores_with_spaces(buffer_author));
                printf("Editore:%s\t Genere:%s\t\tAnno di pubblicazione:%d\n", replace_underscores_with_spaces(buffer_publisher), replace_underscores_with_spaces(buffer_genre), buffer_printingyear);
                printf("ISBN:%s\t\t\tValutazione:%.1f\n\n",buffer_ISBN , buffer_rating);

                addBook(&head, buffer_title, buffer_author, buffer_publisher, buffer_printingyear, buffer_genre, buffer_ISBN, buffer_rating); //e lo memorizzo all'interno della lista
                break;
            case 2:
                chooseBook(&head);
                break;
            case 3:
                printBooks(head);
                break;
            case 4:
                printf("\nLA RICERCA NON E' CASE-SENSITIVE!");
                printf("\n(anno di pubblicazione) inserire un anno se si vogliono cercare tutti i libri pubblicati in quell'anno.");
                printf("\n(valutazione) inserire un valore decimale compreso tra 0 a 10 se si vogliono vedere i libri che hanno una valutazione superiore alla valutazione inserita (il valore deve avere il '.').");
                printf("\naltrimenti qualsiasi parola inserita il programma la confrontera' con le altri informazioni del libro e stampera' i libri che hanno una voce in corrispondenza \n(anche se si inserisce solo la prima parola es. harry trovera' tutti i libri che iniziano per harry).\n");

                printf("\ninserire il valore che si vuole cercare: ");
                char *buffer = getString();
                fflush(stdin);

                printf("\n");
                booksSearch(head, buffer);
                break; 
            default:
                choice=0; //se viene inserita una voce ambigua il programma esce dal ciclo senza salvare i libri su file
                break;
        }
    }while (choice!=0);
	return 0;
}

void initializeBooksFromFile(struct Node **head) { //prende il file lo legge, e memorizza i libri all'interno della lista
    FILE *file;
    file = fopen(ABSOLUTE_FILE, "r"); //apre il file come lettura
    if(file!=NULL)  //se il file e' stato aperto correttamente
    {
        while (!feof(file)) //itera queste istruzioni fino a quando il 'cursore' si trova alla fine del file
        {
            char buffer_title[100], buffer_author[100], buffer_publisher[100], buffer_genre[100], buffer_ISBN[100];
            int buffer_printingyear;
            float buffer_rating;
            //memorizza le informazioni secondo questa 'logica' 
            fscanf(file, "%s %s %s %d %s %s %f", buffer_title, buffer_author, buffer_publisher, &buffer_printingyear, buffer_genre, buffer_ISBN, &buffer_rating);
            
            //aggiunge un libro alla lista
            addBook(head, buffer_title, buffer_author, buffer_publisher, buffer_printingyear, buffer_genre, buffer_ISBN, buffer_rating);
        }
    }
    fclose(file); //chiude il file
}

void addBook(struct Node **head, char *title, char *author, char *publisher, int printing_year, char *genre, char *ISBN, float rating) { //aggiunge un libro alla lista
    struct Node *new_node = malloc(sizeof(struct Node)); //crea un nuovo nodo e memorizza le informazioni del libro

    new_node->title = (char *) malloc(strlen(title) + 1);
    sprintf(new_node->title, "%s\0", title);

    new_node->author = (char *) malloc(strlen(author) + 1);
    sprintf(new_node->author, "%s\0", author);

    new_node->publisher = (char *) malloc(strlen(publisher) + 1);
    sprintf(new_node->publisher, "%s\0", publisher);

    new_node->printing_year = printing_year;

    new_node->genre = (char *) malloc(strlen(genre) + 1);
    sprintf(new_node->genre, "%s\0", genre);

    new_node->ISBN = (char *) malloc(strlen(ISBN) + 1);
    sprintf(new_node->ISBN, "%s\0",ISBN);

    new_node->rating = rating;

    new_node->next = *head;
    *head = new_node;   //mette il nodo in cima alla lista (testa)
}

void chooseBook(struct Node **head) {   //fa scegliere un nodo con implementazione grafica e puo' eliminarlo
    int counted_books = printBooks(*head);  //stampa tutti i libri e memorizza quanti ne ha stampati
    if(counted_books>0) { //se i libri sono piu' di 0 ne fa sceglierne uno da eliminare o no
        COORD old_coords = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)); //prende le coordinate del cursore nella console
        printf("Scorrere i libri con le frecce direzionali SU e GIU, premere ENTER per eliminare il libro e ESCAPE per annullare.");

        old_coords.Y = old_coords.Y - (4*counted_books); //inizia dal primo
        old_coords.X = 0;
        int now_book = 0; //indic del libro su cui e' il cursore ora
        gotoxy(old_coords.Y + (4*now_book), old_coords.X); //metti il cursore a quelle coordinate 

        bool elimina = false; //ne posso eliminare solo uno per volta
        char c = ' ';
        while (c!=ESCAPE)//sfinche' non si preme enter o escape itera
        {
            c = getch();
            switch (c)
            {
            case ARROW_UP:  //va al libro precedente
                if(now_book-1>=0)   //controllando se non esce dalla lista
                    now_book--;
                break;
            case ARROW_DOWN:    //va al libro successivo
                if(now_book+1<counted_books)    //controllando se non esce dalla lista
                    now_book++;
                break;
            case ENTER: //se preme enter finisce il while e si segna che il libro e' da eliminare
                c=ESCAPE;
                elimina = true;
                break;
            default:
                break;
            }
            gotoxy(old_coords.Y + (4*now_book), old_coords.X); 
        }
        gotoxy(old_coords.Y + (4*counted_books), old_coords.X);
        if(elimina) {
            struct Node *deleted_book = deleteBook(head, now_book); //elimina il libro dalla posizione nella lista (scelta tramite la grafica) 
            printf("\n\thai eliminato il libro: %s\n", replace_underscores_with_spaces(deleted_book->title)); //stampa il titolo del libro eliminato
        }
        printf("\n");
    }
}

struct Node * deleteBook(struct Node **head, int n_node) {  //data la testa di una lista e il nodo che si vuole eliminare lo elimina
    struct Node *tmp = *head;
    struct Node *old_node = tmp;
    if(n_node==0)   //controlla se il libro e' quello in cima (se e' in cima (in testa)) fa puntare la testa all'elemento successivo
    {
        *head = tmp->next;
    }
    else    //altrimenti scorre la lista e va a eliminare il nodo corretto
    {
        int i = 0;
        for (i = 0; i != n_node && tmp != NULL ; i++) {
            old_node = tmp;
            tmp = tmp->next;
        }
        //dentro tmp c'e' quello che devi eliminare
        old_node->next = tmp->next; //cosi il nodo contenuto in tmp scompare
    }

    return tmp; //ritorno il libro eliminato
}

char* replace_underscores_with_spaces(char const *str) { //data una stringa rimpiazza gli underscore con spazi
    // allocate memory for the new string
    char *new_str = malloc(strlen(str) + 1);
    strcpy(new_str, str); //copy the string in another dynamic string
    
    char copy[100];
    strcpy(copy, str);

    char *token;
    token = strtok(copy, "_");
    strcpy(new_str, ""); //initialize new_str with an empty string because we wanna return this variable to the printf

    while (token != NULL) { // split the copy of the original string at underscores and concatenate the resulting substrings with spaces
        strcat(new_str, token);
        strcat(new_str, " ");
        token = strtok(NULL, "_");
    }

    return new_str;
}

void booksSearch(struct Node *head, char *string) { //cerca data una stringa i libri
    bool print = false;
    struct Node *tmp = head; //partendo dal primo elemento gli scorre tutti    

    if(atoi(string)==0) { //controlla se la stringa inserita e' una stringa di caratteri oppure e' l'anno di pubblicazione o la valutazione
        while (tmp != NULL) {
            print = false; //confronta tutte le informazioni di un libro con la stringa e appena trova una corrispondenza si segna che lo deve stampare
            if(strncasecmp(tmp->title, string, strlen(string))==0) print = true;
            else if(strncasecmp(tmp->author, string, strlen(string))==0) print = true;
            else if(strncasecmp(tmp->publisher, string, strlen(string))==0) print = true;
            else if(strncasecmp(tmp->genre, string, strlen(string))==0) print = true;
            else if(strncasecmp(tmp->ISBN, string, strlen(string))==0) print = true;
            if(print) { //se lo deve stampare lo stampa
                printf("%s\t\t%s\n", replace_underscores_with_spaces(tmp->title), replace_underscores_with_spaces(tmp->author));
                printf("Editore:%s\t Genere:%s\t\tAnno di pubblicazione:%d\n", replace_underscores_with_spaces(tmp->publisher), replace_underscores_with_spaces(tmp->genre), tmp->printing_year);
                printf("ISBN:%s\t\t\tValutazione:%.1f\n\n", tmp->ISBN, tmp->rating);
            }
            tmp = tmp->next;    //va al libro successivo nella lista
        }
        
    }
    else {
        bool isfloat = false; //se viene inserito un numero verificare se e' una valutazione o un anno
        for (int i = 0; !isfloat && string[i]!='\0'; i++)
        {
            if(string[i]=='.')
                isfloat = true;
        }

        if(isfloat) { //se e' una valutazione viene convertita in float 
            float rating = (float)strtod(string,NULL);
        
            while(tmp != NULL) {    //e scorre poi fra tutti i libri stampando i libri che hanno una valutazione maggiore di quella inseirta
                if(tmp->rating > rating) {
                    printf("%s\t\t%s\n", replace_underscores_with_spaces(tmp->title), replace_underscores_with_spaces(tmp->author));
                    printf("Editore:%s\t Genere:%s\t\tAnno di pubblicazione:%d\n", replace_underscores_with_spaces(tmp->publisher), replace_underscores_with_spaces(tmp->genre), tmp->printing_year);
                    printf("ISBN:%s\t\t\tValutazione:%.1f\n\n", tmp->ISBN, tmp->rating);
                }
                tmp = tmp->next;    //va al libro successivo nella lista
            }
        }
        else {  //altrimenti il numero inserito e' inteso come anno di pubblicazione e se trova una corrispondenza (trattando la variabile come numero (intero))
            int printing_year = atoi(string);
            while(tmp != NULL) {
                if(tmp->printing_year == printing_year) {   //se trova un libro con quell'anno lo stampa
                    printf("%s\t\t%s\n", replace_underscores_with_spaces(tmp->title), replace_underscores_with_spaces(tmp->author));
                    printf("Editore:%s\t Genere:%s\t\tAnno di pubblicazione:%d\n", replace_underscores_with_spaces(tmp->publisher), replace_underscores_with_spaces(tmp->genre), tmp->printing_year);
                    printf("ISBN:%s\t\t\tValutazione:%.1f\n\n", tmp->ISBN, tmp->rating);
                }
                tmp = tmp->next;    //va al libro successivo nella lista
            }
        }


    }
}

int printBooks(struct Node *head) { //stampa tutti i libri e restituisce se si vuole il numero totale dei libri nella lista.
    printf("\n");
    int counted_books=0;    //variabile che ritorna, indica il nuero di libri stampati (quindi quelli presenti nella lista)
    struct Node *tmp;
    tmp = head;
    while (tmp !=NULL) { //cominciando dalla testa (il primo) li stampa tutti
        printf("%s\t\t%s\n", replace_underscores_with_spaces(tmp->title), replace_underscores_with_spaces(tmp->author));
        printf("Editore:%s\t Genere:%s\t\tAnno di pubblicazione:%d\n", replace_underscores_with_spaces(tmp->publisher), replace_underscores_with_spaces(tmp->genre), tmp->printing_year);
        printf("ISBN:%s\t\t\tValutazione:%.1f\n\n", tmp->ISBN, tmp->rating);
        counted_books++;
        tmp = tmp->next;
    }
    if(counted_books==0)    printf("\nNessun libro presente nel file.\n"); //se non viene stampato nessun libro mostra il messaggio a schermo
    return counted_books;
}

void saveBooksOnFile(struct Node *head) {    //memorizza la lista nel file
    FILE *file;
    file = fopen(ABSOLUTE_FILE, "w"); //apre il file in modalita' di sola scrittura
    
    struct Node *tmp = head; //e incominciando dalla testa
    while (tmp != NULL) {   //memorizza nel file ogni libro secondo la seguente 'logica'
        fprintf(file, "%s %s %s %d %s %s %.2f\n", tmp->title, tmp->author, tmp->publisher, tmp->printing_year, tmp->genre, tmp->ISBN, tmp->rating);
        tmp = tmp->next; //va al libro successivo
    }
    fclose(file);   //chiude il file
}

void loading() { //mostra un caricamento estetico prima di ogni voce selezionata
    printf("\n");
    time_t now = 0;
    float delay = 0.15; //ogni quanti secondi si vuole stampare un quadratino
    COORD old_coords = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)); //prendo le coordinate del puntatore della console

    for (int i = 0; i < 3; i++) { // itera 3 volte
        for (int j = 0; j < 3; j++) { //stampo 3 puntini ogni delay secondi
            now = clock();  //inizializzo il timer
            printf(".");
            for( ; clock() - now < delay * CLOCKS_PER_SEC; );
        }
        gotoxy(old_coords.Y, 0); //imposto il cursore della console alla posizione 0
        for( ; clock() - now < (delay*2) * CLOCKS_PER_SEC; );
        printf("   ");
        gotoxy(old_coords.Y, 0); //imposto il cursore della console alla posizione 0
    }
    clear();
}

char* getString() { //chiede una stringa in input e la restituisce come vettore di stringa 'dinamico'
    char buffer[100];
    //stringa dinamica
    int i=0;
    for (i = 0; (buffer[i] = getch()) != '\r'; i++) //richiede un carattere
    {
        if(buffer[i]==' ')  //se il carattere e' uno spazio lo sotituisce con un '_'
            buffer[i]='_';

        if(buffer[i]== '\b') //funzione di backspace (se si sbalgia a inserire da la possibilita' di cancellare cio' che si e' scritto)
        {
            if(i>0) {
                printf("%c", buffer[i]);
                i-=2;
                printf(" ");
                printf("\b");
            } else i-=1;
        } else printf("%c", buffer[i]);

    }
    buffer[i] = '\0'; //al posto del '\r' inserito per terminare ll'inserimento lo sostituisce con il terminatore di stringa
    char * str = malloc(sizeof(char) * i); //creo la stringa 'dinamica'
    strcpy(str, buffer); //copio il contenuto e la ritorno
    return str;
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput) //prende la posizione attuale del cursore
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

void gotoxy(int y, int x) //mette il cursore nella posizione y x nella console
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    if (!SetConsoleCursorPosition(hConsole, coord)){} //gestisce gli errori
}