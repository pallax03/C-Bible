#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>


//crea un file con questo nome quando si vogliono esportare i contatti, e legge il file quando si vogliono importare
#define ABSOLUTE_FILE "./contatti.txt"

//definiamo la grandezza della rubrica e la dichiariamo globale
#define CONTATTI_TOTALI 1000
#define GRANDEZZA_NOME 20       //grandezza massima del nome + 1 per il carattere di split ';'
#define GRANDEZZA_TELEFONO 10   //grandezza massima del numero di telefono + 1 per il terminatore '\0'

char * dati[] = {"Nome", "Numero di telefono"}; //vettore per una stampa piu' efficace
int grandezza_dati[] = {GRANDEZZA_NOME, GRANDEZZA_TELEFONO};    //vettore parallelo di dati per adattarsi nei for 

char *lista[CONTATTI_TOTALI]; //matrice contenente 1000 contatti massimo dove ognuno possiede un vettore di stringhe frastagliato
int count=0; //contatore per sapere a quale posizione e' la matrice con i contatti.

#define CARATTERE_DI_FINE_INSERIMENTO '\r' //enter //utile per gli input

void aggiungiContatto() { //opzione 1 nel menu
    int m=0;
    char buffer_lettura[GRANDEZZA_NOME + 1 + GRANDEZZA_TELEFONO + 1];
    for (int i = 0; i < sizeof(dati)/sizeof(dati[0]); i++) //scorre per quanti dati deve richiedere
    {
        printf("\n%s: ", dati[i]);                         //stampa cosa chiede
        int j=0;
        for (j = 0; j < grandezza_dati[i] && ((buffer_lettura[j+m]=getch()) != '\r'); j++) //e richiede l'input di dati[i]. 
        { //(appena si interrompe l'inserimento si ripete per il secondo dato da richiedere e cosi via). 
            if( buffer_lettura[j+m] == '\b') //possibilita di cancellare i caratteri inseriti con il backspace
            {
                if(j>0) //controlla se effettivamente si puo' cancellare perche' se si e' arrivati all'elemento 0 non si puo' cancellare piu' nulla (elemento iniziale della stringa)
                {
                    printf("%c", buffer_lettura[j+m]);
                    j-=2;
                }  
            }
            else if(i==0) //sta inserendo il nome, non permette di inserire numeri
            {
                if(isdigit(buffer_lettura[j+m])) j--;
                else printf("%c", buffer_lettura[j+m]);
            }
            else if (i==1) //sta inserendo il numero di telefono, non permette di inserire lettere
            {
                if(isalpha(buffer_lettura[j+m])) j--;
                else printf("%c", buffer_lettura[j+m]);
            }
            else
            {
                printf("%c", buffer_lettura[j+m]);
            }
        }
        m+=j;
        if(i+1 < sizeof(dati)/sizeof(dati[0])) //mette il carattere di split dei dati
            buffer_lettura[m] = ';';
        else
            buffer_lettura[m] = '\0';
        m++;
    }
    lista[count] = malloc(sizeof(char) * m); //alloca nuovo spazio in memoria per quanti byte e' la stringa inseritae gia' formattata
    if (lista[count] != NULL) { //e se c'e' abbastanza spazio la aggiunge
        strcpy(lista[count], buffer_lettura);
        count++;
        printf("\ncontatto aggiunto.");
    }
    else
    {
        printf("\nimpossibile aggiungere il contatto.");
    }
} 

void richiediValoreRicerca(char *tmp) { //richiede in input unvettore di char e lo memorizza nella variabile tmp
    printf("\ninserire il dato che si vuole cercare (se numero cerchera' fra i numeri di telefono altirmenti nei nomi): ");
    int m=0;
    for (int i = 0; i < GRANDEZZA_NOME -1 && ((tmp[i]=getch()) != '\r'); i++) //chiede in input la parola o caratteri da confrontare
    {
        if(tmp[i]== '\b') //funzione di backspace
        {
            if(i>0) //cancella solo se non si e' all'elemento 0
            {
                if(isalnum(tmp[i-1])) //controlla se effettivamente si e' all'elemento 0 (per un effetto visivo piu' bello)
                {
                    printf("%c", tmp[i]);
                    i-=2;
                    printf("%c", ' ');
                    printf("%c", '\b');
                }
                else{i-=1;}
            }
            else
            {
                i-=1;
            }
        }
        else if(i>0) //funzione che se inserisci le lettere consente solo inserimento di altre lettere o il contrario per i numeri.
        {
            if(isdigit(tmp[0]))
            {
                if(!isdigit(tmp[i])) i--;
                else printf("%c", tmp[i]);
            }
            else if(isalpha(tmp[0]))
            {
                if(!isalpha(tmp[i])) i--;
                else printf("%c", tmp[i]);
            }
            else printf("%c", tmp[i]);
        }
        else
        {
            printf("%c", tmp[i]);
        }
        m=i;
    }
    tmp[m+1]='\0';//aggiunge il carattere terminatore nella stringa inserita (poiche' poi nei cicli lo uso come controllo)
}

void ricercaEsatta() { //opzione 2 nel menu
    char tmp[GRANDEZZA_NOME]; //variabile di appoggio
    richiediValoreRicerca(&tmp[0]); //per suddividere meglio il programma visto che le due ricerche chiedono nello stesso modo un valore in input. 
    printf("\n");

    for (int i = 0; i < count; i++) //ciclo che scorre contatto per contatto
    {
        bool trovato = true;
        if(isdigit(tmp[0])) //qui controlla se deve cercare fra nomi o numeri
        {
            int m=0;
            for (int j = 0; lista[i][j] != ';' ; j++){m=j;} m+=2; //se la ricerca e' fra numeri allora essendo la stringa all'interno di un contatto formata da "nome;numero\0"
            //fa in modo che controlla solo la stringa numero
            //adesso in m abbiamo da quanto deve iniziare la stringa in lista per cominciare dai numeri
            for (int j = 0; trovato && !(tmp[j]=='\0' && lista[i][j+m] == '\0'); j++) //passa al carattere successivo se ancora le due stringhe non sono finite entrambe
            {
                if(tmp[j]!=lista[i][j+m]) trovato=false; //se il carattere non corrisponde interrompe il ciclo e non stampera' quel contatto
            }
        }
        else 
        {
            for (int j = 0; trovato && !(tmp[j]=='\0' && lista[i][j] == ';'); j++) //l'algoritmo di ricerca e' uguale al numero cambia solo che il contatore della lista parte effettivamente da 0 e si ferma al ;
            {
                if(tmp[j]!=lista[i][j]) trovato=false;
            }
        }

        if(trovato) //se ha trovato il contatto nella ricerca lo stampa
        {
            for (int j = 0; lista[i][j] != '\0' ; j++)
            {
                if(lista[i][j]==';') printf("\tnumero: ");
                else printf("%c", lista[i][j]);
            }
            printf("\n"); 
        }
    }
}

void ricercaApprossimata() { //opzione 3 nel menu
    char tmp[GRANDEZZA_NOME]; //variabile di appoggio
    richiediValoreRicerca(&tmp[0]); //per suddividere meglio il programma visto che le due ricerche chiedono nello stesso modo un valore in input. 
    printf("\n");
    // ho cercato di usare un algoritmo che funzionasse in entrambe le ricerche quindi sono praticamente uguali
    for (int i = 0; i < count; i++) //ciclo che scorre contatto per contatto
    {
        bool trovato = true;
        if(isdigit(tmp[0])) //qui controlla se deve cercare fra nomi o numeri
        {
            int m=0;
            for (int j = 0; lista[i][j] != ';' ; j++){m=j;} m+=2; //se la ricerca e' fra numeri allora essendo la stringa all'interno di un contatto formata da "nome;numero\0"
            //fa in modo che controlla solo la stringa numero
            for (int j = 0; trovato && tmp[j]!='\0'; j++) //cambia solo la condizione che qui si ferma solo quando finisce la stringa in input
            {
                if(tmp[j]!=lista[i][j+m]) trovato=false;  //se il carattere non corrisponde interrompe il ciclo e non stampera' quel contatto
            }
        }
        else 
        {
            for (int j = 0; trovato && tmp[j]!='\0'; j++) //l'algoritmo di ricerca e' uguale al numero cambia solo che il contatore della lista parte effettivamente da 0 e si ferma al ;
            {
                if(tmp[j]!=lista[i][j]) trovato=false;
            }
        }

        if(trovato) //se ha trovato il contatto nella ricerca lo stampa
        {
            for (int j = 0; lista[i][j] != '\0' ; j++)
            {
                if(lista[i][j]==';') printf("\tnumero: ");
                else printf("%c", lista[i][j]);
            }
            printf("\n"); 
        }
    }
}

void stampaRubrica() { //opzione 4 nel menu
    printf("\n\nLista Contatti: \n");
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; lista[i][j] != '\0' ; j++)
        {
            if(lista[i][j]==';')
            {
                printf("\t\tnumero: ");
            }
            else
                printf("%c", lista[i][j]);
        }
        printf("\n"); 
    }
    if(count==0)
        printf("\n\tPremi 1 nel menu per aggiungere nuovi contatti!");
}

void importaEsportaRubrica() { //opzione 5 nel menu
    char c='a';
    FILE *file;
    printf("\n(e = export | i = import | chiude sotto-menu se non inserisci ne' i ne' e)\n");
    printf("Vuoi esportare o importare? ");
    fflush(stdin);
    scanf("%c", &c);
    if(c=='i')
    {
        file = fopen(ABSOLUTE_FILE, "r");   //mode: r → sola-lettura.
        int contatti_ora=count;
        char x;
        if(file != NULL)
        {
            int i=0;
            char buffer_lettura[GRANDEZZA_NOME + 1 + GRANDEZZA_TELEFONO + 1];
            while (!feof(file))
            {
                fscanf(file, "%c", &x);
                if(x=='\n')
                {
                    
                }
                else if(x=='\0')
                {
                    buffer_lettura[i] = x;
                    lista[count] = malloc(sizeof(char) * i);
                    if (lista[count] != NULL) 
                    {
                        strcpy(lista[count], buffer_lettura);
                        count++;
                    }
                    i= 0;
                }
                else
                {
                    buffer_lettura[i] = x;
                    i++;
                }
            }
            fclose(file);
        }
        printf("\t\nimportati correttamente %d contatti", count - contatti_ora);
    }
    else if(c=='e')
    {      
        file = fopen(ABSOLUTE_FILE, "w");   //mode: w → scrittura.
        for (int i = 0; i < count; i++)
        {
            int j=0;
            for (j = 0; lista[i][j] != '\0' ; j++)
            {
                fprintf(file,"%c", lista[i][j]);
            }
            fprintf(file,"%c", lista[i][j]);
            fprintf(file,"\n");
        }
        fclose(file);
        printf("\nfile esportati con successo.");
    }
    printf("\n");
}

int main()
{
    /*Gruppo:
    Matricola:  Alex Mazzoni       E-mail: alex.mazzoni3@studio.unibo.it
    Matricola:  Giovanni Luca      E-mail: giovanni.luca@studio.unibo.it
    Matricola:  Michele Farneti    E-mail: michele.farneti@studio.unibo.it
    */
    printf("\nSettimana 6 - Esercizio 1\t E-mail di riferimento: alex.mazzoni3@studio.unibo.it\n");

    int voce_selezionata=99;
    do
    {
        printf("\nInserisci il numero della voce che desideri effettuare: ");
        if(voce_selezionata!=99)
            printf("(voce selezionata precedentemente: %d)", voce_selezionata);
        printf("\n\n\t1. Aggiungi un nuovo contatto nella rubrica.\n");
        printf("\t2. Ricerca di una voce esatta (per nome o per numero di telefono).\n");
        printf("\t3. Ricerca di una voce approssimata (per nome o per numero di telefono).\n");
        printf("\t4. Visualizzazione della rubrica.\n");
        printf("\t5. Importa o Esporta la rubrica.\n");
        printf("\t0. Termina il programma.\n");
        printf("\n\tinserire il numero della voce che vuole effettuare: ");
        scanf("%d", &voce_selezionata);
        fflush(stdin);
        switch (voce_selezionata) {
        case 0://esce
            break;
        case 1:
            aggiungiContatto();
            break;
        case 2:
            ricercaEsatta();
            break;
        case 3:
            ricercaApprossimata();
            break;
        case 4:
            stampaRubrica();
            break;
        case 5:
            importaEsportaRubrica();
            break;
        }
        printf("\n\n");
    } while (voce_selezionata!=0);

    return 0;
}