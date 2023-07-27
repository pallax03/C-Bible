#include <stdio.h>
#include <conio.h> //utilizzo la libreria <conio.h> per usare la funzione getch(); per prendere come input un char.
#include <ctype.h>

int main(void) 
{
    /*Gruppo:
   Matricola:  Alex Mazzoni       E-mail: alex.mazzoni3@studio.unibo.it
   Matricola:  Giovanni Luca      E-mail: giovanni.luca@studio.unibo.it
   Matricola:  Michele Farneti    E-mail: michele.farneti@studio.unibo.it
   */
    printf("\nSettimana 3 - Esercizio 2\t E-mail di riferimento: alex.mazzoni3@studio.unibo.it\n");

    int i=0; //contatore usato per scorrere il vettore, per poi usarlo per sapere i caratteri totali inseriti.
    char array[100]; // si puo' inserire un testo di massimo 100 caratteri! (se viene inserito un testo da piu' di 100 caratteri il programma prende solo fino a 100!).
    // il sizeof potrebbe non funzionare, dipende da come viene dichiarato il vettore, se il vettore fosse dichiarato nel seguente modo:  array[] = {'c', 'i', 'a', 'o'},
    // non avrebbe funzionato, poiche' trattiamo la variabile come un vero e proprio puntatore e sta poi al sistema operativo assegnare quanto spazio darle percui il valore puo' essere ambiguo.
    
    // contatori, dei caratteri inseriti.
    int conta_spazi = 0, conta_a_capo=0, conta_numeri=0, conta_minuscole=0, conta_maiuscole=0, conta_caratteri_strani=0;

    printf("\ninserisci un testo di massimo %d caratteri! (termina l'inserimento digitando '#'): ", sizeof(array)); //mostra anche se il sizeof funziona.
    for(i=0; i < sizeof(array) && (array[i]=getch()) != '#' ; i++) //il programma controlla se il vettore supera la sua grandezza preimpostata (usando il sizeof: 100),
    {   //se e' minore della sua grandezza allora esce dal ciclo, anche se il carattere inserito e' un '#'.  
        //uso questi if annidati per utilizzare tutte le funzioni della libreria <ctype.h>.
        if(isalnum(array[i])) //se il carattere inserito e' tra A - Z, o a - z, oppure tra 0 - 9.
        {
            if(isupper(array[i]))       conta_maiuscole++; //se e' tra A - Z, conta un carattere maiuscolo.
            else if(islower(array[i]))  conta_minuscole++; //se e' tra a - z, conta un carattere minuscolo.
            else if(isdigit(array[i]))  conta_numeri++;    //se e' tra 0 - 9, conta un numero. (potevo anche fare un else senza un else if, ma devo usare tutte le funzioni).
        }
        else if(array[i] == ' ')   conta_spazi++; //se inserito uno spazio, lo conta.
        else if(array[i] == '\r') {array[i]='\n';conta_a_capo++;} //se premuto il tasto invio, memorizza un '\r' (carriage return),
        //pero' l'utente quando preme l'invio vuole andare alla linea successiva (e non rimanere alla stessa) quindi lo scambio con un '\n' (new line) e lo considero come tale.
        else conta_caratteri_strani++; //qualsiasi altro carattere che non rientra nei sopra elencati viene contato da questo contatore.
        printf("%c", array[i]); //stampa il carattere inserito.
    }
    if(array[i]!='#') printf("\n\n\tCaratteri esauriti!\n"); //se il ciclo e' terminato perche' raggiunta la massima capacita' del vettore stampa: "Caratteri esauriti!".

    printf("\n\nStatistiche:\n");
    printf("spazi: %d\ta capo('\\n'): %d\t\tnumeri: %d\tminuscole: %d\tmaiuscole: %d\tcaratteri strani: %d\tcaratteri totali: %d\n", conta_spazi, conta_a_capo, conta_numeri,conta_minuscole, conta_maiuscole, conta_caratteri_strani, i);

    return 0;
}