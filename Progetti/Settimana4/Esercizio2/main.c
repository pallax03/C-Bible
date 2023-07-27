#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int main() {
    /*Gruppo:
    Matricola:  Alex Mazzoni       E-mail: alex.mazzoni3@studio.unibo.it
    Matricola:  Giovanni Luca      E-mail: giovanni.luca@studio.unibo.it
    Matricola:  Michele Farneti    E-mail: michele.farneti@studio.unibo.it
    */
    printf("\nSettimana 4 - Esercizio 2\t E-mail di riferimento: alex.mazzoni3@studio.unibo.it\n");

    srand(time(NULL));

    //Dichiaro la matrice su cui verrá eseguita la random walk
    char Matrice[10][10];

    //Utilizzo due cicli for per riempire la matrice di caratteri '.',
    //equivalenti ad uno slot non occupato
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            Matrice[i][j] = '.';
        }
    }

    //Come contatore per indicare le posizioni visitate utilizzo un intero, che inizializzo al valore 65,
    //in quanto, esendo equivalente al carattere ASCII 'A', venendo incrementato mi permetterá di segnare
    //le caselle come richiesto.
    int c = 65;
    //Utilizzo due varaibili per memorizzare la posizone di passo in passo durante la passeggiata
    int i = 0;
    int j = 0;

    int mossa;

    //flag
    bool mossepossibili[] = {true, true, true, true};
    bool f=false;

    //Genero la passeggiata
    while(c<=90)//finche' la c e' = a Z
    {
        Matrice[i][j]=c;//memorizza la lettera nella posizione.

        //Ripeto la genereazione casuale della mossa finché non ne trovo una fattibile o
        //non riconosco che non ce non é piú possibile muoversi
        do
        {
            //Genero casualmente la mossa da fare.
            mossa = rand()%4;
            //Valuto se é possibile o meno eseguire la mossa, in caso memorizzo gli indici della nuova posizione
            switch(mossa)
            {
                case 0:
                    if(i+1<10)//controlla se la riga successiva rientra nei limiti della matrice
                    {
                        if(Matrice[i+1][j] == '.')//se trova posto (non c'e' una lettera)
                        {
                            i++;//si posiziona al posto giusto
                            f=true;//esce dal ciclo do-while
                        }
                        else
                        {
                            mossepossibili[0]=false; //altrimenti si segna che la mossa nella riga successiva non si puo' effettuare
                        }
                    }
                    else
                    {
                        mossepossibili[0]=false; //altrimenti si segna che la mossa nella riga successiva non si puo' effettuare
                    }
                    break;
                case 1:
                    if(i>0)//controlla se la riga precedente rientra nei limiti della matrice
                    {
                        if(Matrice[i-1][j] == '.')//se trova posto (non c'e' una lettera)
                        {
                            i--;//si posiziona al posto giusto
                            f=true;//esce dal ciclo do-while
                        }
                        else
                        {
                            mossepossibili[1]=false;//altrimenti si segna che la mossa nella riga precedente non si puo' effettuare
                        }
                    }
                    else
                    {
                        mossepossibili[1]=false;//altrimenti si segna che la mossa nella riga precedente non si puo' effettuare
                    }
                    break;
                case 2:
                    if(j+1<10)//controlla se la colonna successiva rientra nei limiti della matrice
                    {
                        if(Matrice[i][j+1] == '.')//se trova posto (non c'e' una lettera)
                        {
                            j++;//si posiziona al posto giusto
                            f=true;//esce dal ciclo do-while
                        }
                        else
                        {
                            mossepossibili[2]=false;//altrimenti si segna che la mossa nella colonna successiva non si puo' effettuare
                        }
                    }
                    else
                    {
                        mossepossibili[2]=false;//altrimenti si segna che la mossa nella colonna successiva non si puo' effettuare
                    }
                    break;
                case 3:
                    if(j>0)//controlla se la colonna precedente rientra nei limiti della matrice
                    {
                        if(Matrice[i][j-1] == '.')//se trova posto (non c'e' una lettera)
                        {
                            j--;//si posiziona al posto giusto
                            f=true;//esce dal ciclo do-while
                        }
                        else
                        {
                            mossepossibili[3]=false;//altrimenti si segna che la mossa nella colonna precedente non si puo' effettuare
                        }
                    }
                    else
                    {
                        mossepossibili[3]=false;//altrimenti si segna che la mossa nella colonna precedente non si puo' effettuare
                    }
                    break;
            }
        }while(!f && (mossepossibili[0] || mossepossibili[1] || mossepossibili[2] || mossepossibili[3]));//se il flag (f) e' vero interrompe subito il ciclo altrimenti controlla se tutte le mossee possibili sono state controllate
        
        //In caso non sia stato possibile effetuare una mossa, esco da ciclo e arresto il programma.
        if(!mossepossibili[0] &&  !mossepossibili[1] &&  !mossepossibili[2] &&  !mossepossibili[3])
        {
            printf("\nNon e stato possibile completare la random walk, ultimo carattere stampato: %c\n\n",c);
            break;
        }
        //Resetto i flag
        f=false;
        mossepossibili[0]=true;
        mossepossibili[1]=true;
        mossepossibili[2]=true;
        mossepossibili[3]=true;
        c++;
    }

    if(c==91)
    {
        printf("\nRandom walk completata: \n\n");
    }

    //Funzione per la stampa dei valori della matrice, per un migliore
    //effetto estetico, inserisco delle spaziature predefinite tra i caratteri
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            printf("%4c",Matrice[i][j]);
        }
        printf("\n");
    }


    return 0;
}
