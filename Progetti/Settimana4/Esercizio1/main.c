#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h> //per usare i flag (ottimizzare i for).
#include <time.h>
#define LENGHT1 5 //se LENGHT1 > LENGHT2 il programma non funzionerebbe piu' a dovere.
#define LENGHT2 7
#define LENGHTUNIONE (LENGHT1 + LENGHT2)
//utilizzo delle define per inserire delle macro dedite ad assegnare un valore di massima dimensione agli array

int main(void) {
    /*Gruppo:
   Matricola:  Alex Mazzoni       E-mail: alex.mazzoni3@studio.unibo.it
   Matricola:  Giovanni Luca      E-mail: giovanni.luca@studio.unibo.it
   Matricola:  Michele Farneti    E-mail: michele.farneti@studio.unibo.it
   */
    printf("\nSettimana 4 - Esercizio 1\t E-mail di riferimento: alex.mazzoni3@studio.unibo.it\n\n");

    //dichiarazioni vari array/ variabili utili al risultato finale.
    int array1[LENGHT1];
    int array2[LENGHT2];
    int array_intersezione_ripetizioni[LENGHT2];
    int array_intersezione_noripetizioni[LENGHTUNIONE];
    int array_unione[LENGHTUNIONE];
    int count = 0; //contatore dei vettori intersezione

    srand(time(NULL));

    printf("\ninserisci %d numeri dentro il primo vettore: ", LENGHT1);
    for (int i = 0; i < LENGHT1; i++) {
        scanf("%d", &array1[i]); //uso lo scanf, sfruttando un vantaggio di esso. (esso appunto mi permette di inserire velocemente i numeri, scrivendo i numeri in seguito suddividendoli con un non numero).
        //esempio: 1 3  3 5 5 6  4(lui prendera' solo i numeri, finche' ci stanno nel vettore, in questo caso dal 4 in poi li scarta).
    }
    printf("\n\narray 1 = "); //stampo il vettore inserito. (potevo stamparli direttamente sopra ma per un estetica piu' carina ho deciso di stamparli in un secondo ciclo).
    for (int i = 0; i < LENGHT1; i++) {
        printf("%d%s", array1[i], i+1<LENGHT1 ? ", ":".");
    }
    fflush(stdin);

    // richiedendo anche il secondo vettore come input 
    // printf("\ninserisci %d numeri dentro il secondo vettore: ", LENGHT2);
    // for (int i = 0; i < LENGHT2; i++) {
    //     scanf("%d", &array2[i]);
    // }
    // printf("\n\narray number 2 = "); //stampo il vettore inserito.
    // for (int i = 0; i < LENGHT2; i++) {
    //     printf("%d%s", array2[i], i+1<LENGHT2 ? ", ":".");
    // }
    // fflush(stdin);

    //usando il rand
    //il secondo vettore i suoi elementi vengono generati in maniera casuale da un range da 1 a 10.
    printf("\narray 2 = ");
    for (int i = 0; i < LENGHT2; i++) { //scorro il secondo vettore
        array2[i] = rand()% (10 - 1) + 1; //genero un numero casuale da 1 a 10
        printf("%d%s", array2[i], i+1<LENGHT2 ? ", ":"."); // e lo stampo
    }


    //intersezione con ripetizioni. 
    // Esempio:
    // array1    = { 1, 2, 1, 2, 1}
    // array2    = { 1, 2, 3, 4, 5, 6, 7}
    // risultato = { 1, 1, 2, 2, 1}
    count=0;
    bool nessuna_intersezione = true;
    printf("\n\nvettore intersezione (con ripetizioni): ");
    for (int i = 0; i < LENGHT1; i++) //scorro il primo vettore
    {
        for (int j = 0; j < LENGHT2; j++) //scorro il secondo
        {
            if(array1[i]==array2[j])//avremo quindi una situazione che compara tutti gli elementi del secondo vettorecon un elemento del primo
            {
                array_intersezione_ripetizioni[count] = array1[i];//e se trova due uguali lo memorizza in un vettore
                printf("%d, ", array_intersezione_ripetizioni[count]); //stampando subito l'elemento del vettore
                count++;
                nessuna_intersezione=false;
            }

        }
    }
    if(nessuna_intersezione) //se non viene trovato nessun numero uguale stampa questo.
        printf("nessuna intersezione trovata!");


    //intersezione cancellando le ripetizioni.
    printf("\nvettore intersezione (senza ripetizioni): ");
    count = 0;
    bool intersezione = false;
    nessuna_intersezione = true;
    for (int i = 0; i < LENGHT1; i++) //scorre il primo vettore
    {
        intersezione = false; //imposta il flag come falso ad ogni iterazione
        for (int j = 0; j < LENGHT2 && !intersezione ; j++)//scorre il secondo vettore e se trova una ripetizione nel vettore si interrompe e ne conta solo uno cosi
        {
            if(array1[i]==array2[j])
            {
                intersezione = true; //si segna che il numero del primo vettore e' in comune con un element del secondo vettore
                for (int m = 0; m < count && intersezione; m++) // se ne trova un altro gia memorizzato allora non lo memorizza in seguito e il ciclo si interrompe appena lo trova.
                {
                    if(array_intersezione_noripetizioni[m]==array1[i]) intersezione=false;
                }
            }
        }
        if(intersezione)//se e' stato trovato un elemento nel secondo vettore uguale all'elemento del primo vettore
        {
            array_intersezione_noripetizioni[count] = array1[i]; //memorizza il numero in comune
            printf("%d, ", array_intersezione_noripetizioni[count]); // e lo stampa
            nessuna_intersezione = false; //impostando quindi che ha trovato almeno un numero uguale.
            count++;
        }
    }
    if(nessuna_intersezione)//se ha trovato almeno un numero uguale non stampa il print sotto
        printf("nessuna intersezione trovata!");


    //quarta parte: costituzione di un quarto vettore dedito ad ospitare l'unione dei due array ottenuti dai precedenti input
    printf("\n\nvettore unione: ");
    for (int i = 0; i < LENGHTUNIONE; i++)//scorro il vettore unione
    {
        if(i<LENGHT1)   //metto i primi elementi del primo vettore, (capisce con questo if se li ha messi tutti)
            array_unione[i] = array1[i];
        else
            array_unione[i] = array2[i-LENGHT1]; //poi metto gli elementi del secondo (sottraendo gli elementi del primo cosi poi riparte da  0 e conclude)
        printf("%d ", array_unione[i]); //stampo il vettore
    }

    //stampo tutti gli indirizzi e le grandezzi dei vettori.

    //int array1[LENGHT1];
    printf("\n\narray1\t\tgrandezza totale: %llu byte ", sizeof(array1));
    for (int i = 0; i < LENGHT1; i++)   printf("\narray1[%d] indirizzo: %x, grandezza: %llu byte ", i, &array1[i], sizeof(array1[i]));
        
    //int array2[LENGHT2];
    printf("\n\narray2\t\tgrandezza totale: %llu byte ", sizeof(array2));
    for (int i = 0; i < LENGHT2; i++)   printf("\narray2[%d] indirizzo: %x, grandezza: %llu byte ", i, &array2[i], sizeof(array2[i]));
    
    //int array_intersezione_noripetizioni[LENGHTUNIONE];
    printf("\n\narray_intersezione_noripetizioni\t\tgrandezza totale: %llu byte ", sizeof(array_intersezione_noripetizioni));
    for (int i = 0; i < LENGHTUNIONE; i++)   printf("\narray_intersezione_noripetizioni[%d] indirizzo: %x, grandezza: %llu byte ", i, &array_intersezione_noripetizioni[i], sizeof(array_intersezione_noripetizioni[i]));
    
    //int array_intersezione_ripetizioni[LENGHT2];
    printf("\n\narray_intersezione_ripetizioni\t\tgrandezza totale: %llu byte ", sizeof(array_intersezione_ripetizioni));
    for (int i = 0; i < LENGHT2; i++)   printf("\narray_intersezione_ripetizioni[%d] indirizzo: %x, grandezza: %llu byte ", i, &array_intersezione_ripetizioni[i], sizeof(array_intersezione_ripetizioni[i]));
    
    //int array_unione[LENGHTUNIONE];
    printf("\n\narray_unione\t\tgrandezza totale: %llu byte ", sizeof(array_unione));
    for (int i = 0; i < LENGHTUNIONE; i++)   printf("\narray_unione[%d] indirizzo: %x, grandezza: %llu byte ", i, &array_unione[i], sizeof(array_unione[i]));
    

    return 0;
}