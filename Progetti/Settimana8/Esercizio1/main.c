#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TESTO_RIGA 200

void Modifica_StampaParola();

int main() {
    /*Gruppo:
    Matricola:  Alex Mazzoni       E-mail: alex.mazzoni3@studio.unibo.it
    Matricola:  Giovanni Luca      E-mail: giovanni.luca@studio.unibo.it
    Matricola:  Michele Farneti    E-mail: michele.farneti@studio.unibo.it
    */

    printf("\nSettimana 8 - Esercizio 1\t E-mail di riferimento: alex.mazzoni3@studio.unibo.it\n\n");
    
    //Dichiaro i buffer che gestiro la frase inmserita e le singole parole individuabili in essa, settando una diemsnione massima
    char buffer_lettura[MAX_TESTO_RIGA + 1];
    char parola[MAX_TESTO_RIGA];
    int ch, count;

    printf("inserisci la frase: ");
    fflush(stdin);

    //Leggo la frase inserita in input e la inserisco nel buffer
    count = 0;
    while ((ch = getchar()) != '\n' && count < MAX_TESTO_RIGA)
    {
        buffer_lettura[count] = ch;
        count++;
    }
    buffer_lettura[count] = '\0';
    
    int word = 0;
    int nletter=0;
    
    //Ralizzo un ciclo che scorre le lettere della frase
    for(int i=0; i < count; i++) 
    {
        //Individuo se il carattero preso in esame é considerabile parte di una parola o meno, sfruttando i valori isalpha
        if(((int)buffer_lettura[i]>= 65 && (int)buffer_lettura[i] <=90)||((int)buffer_lettura[i]>= 97 && (int)buffer_lettura[i] <=122))
        {
            parola[nletter]=buffer_lettura[i]; //Carico il carattere sul buffer delle singole parole
            nletter++; //Incermento il conteggio delle lettere
            word=1;  //Attivo un flag che segnala la presenza di una parola in attesa di essere stampata
        }
        else
        {
            //Viene trovato un carattere non riconducbile ad una parola:
            //Se riconosco che é giá stata letta una parola, mi accingo a chiamare la funzione per la sua modifica e stampa 
            if(word == 1)
            {
                Modifica_StampaParola(parola,nletter);
            }
            
            printf("%c",buffer_lettura[i]);//Stampo il carattere di spaziatura
            word=0;//Resetto il flag
            memset(parola,0,sizeof(parola));//Resetto il buffer
            nletter=0;//Resetto il counter delle lettere
        }
        
        //Stampo l'ultima parola rimasta nel buffer
        if(i+1==count)
        {
            if(nletter>0)
            {
                Modifica_StampaParola(parola,nletter);
            }
        }
    }

    return 0;
}

//Funzione per la modifica e stampa delle parole.
void Modifica_StampaParola(char parola[],int nletter)
{
    parola[nletter]=parola[0];//Copio la prima lettera in fondo alla parola

    //Rendo la lettera spostata minuscola in caso non lo fosse
    if(parola[nletter]>=65 && parola[nletter]<=90)
    {
        parola[nletter]+=32;
    }
    
    //Rendo la nuova prima lettera di tipo conforme alla vecchia
    if(parola[0]>=65 && parola[0]<=90 && parola[1]>=97 && parola[1]<=122)
    {
        parola[1] = parola[1]-32;
    }
    else if(parola[0]>=97 && parola[0]<=122 && parola[1]>=65 && parola[1]<=90)
    {
        parola[1] = parola[1]+32;
    }
    
    //In base al conteggio delle lettere, aggiungo "an" o "o" in coda alla parola
    if(nletter<=3)
    {
        parola[nletter+1]='a';
        parola[nletter+2]='n';
    }
    else
    {
        parola[nletter+1]='o';
    }
    
    //Procedo alla stampa della parola con modifiche effetuate
    int j = 1;
    while(parola[j]!='\0')
    {
        printf("%c",parola[j]);
        j++;
    }
}