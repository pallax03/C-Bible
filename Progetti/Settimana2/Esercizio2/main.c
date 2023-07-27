#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SEPARATORE printf("\n----------------------------------------------------------------------------------------------------\n")

//variabili pubbliche
int min=0, max=0; //variabili del range inserito
int numero_generato; //variabile dove memorizzo il numero generato che propongo all'utente
char risposta; //variabile per memoriazzare gli input dell'utente
int flag=0, flag_risposta_YN=0, flag_risposta_minmax=0; //flag vari per uscire dai cicli


//le due funzioni sono simili, poiche' devono svolgere la stessa cosa, cambia solo il ciclo che si interrompe quando i tentativi sono terminati e qualche output aggiuntivo.
// non ho voluto racchiudere le istruzioni dentro i due for perche', sarebbe stato piu' complesso e poco intuitivo passare tanti argomenti.
void indovinaConTentativi(int try)
{
    // il ciclo for, inizializza il contatore i per contare il numero di tantativi impiegati, e si incrementa ad ogni ciclo
    for (int i = 0, flag=0; i < try && flag==0; i++) //si interrompe appena viene trovato il numero che l'utente ha scelto
    {
        numero_generato = rand() % (max - min) + min; //non e' perfetto, ho cercato qualsiasi 'formula' per generare un numero da un intervallo preciso ma nessuna funziona.
        printf("\nTentativi rimasti: %d", try-i); //stampa i tentativi rimasti
        printf("\nrange: %d - %d\n", min, max); //stampa il range che il computer usa per provare ad indovinare il numero
        do
        {
            flag_risposta_YN=0;
            printf("\nNumero generato %d, e' giusto?(Y/N) ", numero_generato);
            fflush(stdin);
            scanf("%c", &risposta);
            if(risposta=='Y' || risposta=='y') //se viene digitato y = 'yes', stampa i tentativi utilizzati con messaggio di vittoria
            {
                printf("\nnumero indovinato in %d tentativi\n", i+1);
                flag=1; //interrompe il ciclo for
            }
            else if(risposta=='N' || risposta=='n') // se invece viene digitato n = 'no'
            {
                if(i+1==try)
                {
                    printf("\nTentativi terminati!\n\nHai perso!!\n");
                }
                else
                {
                    do
                    {   //richiede se il numero generato e' minore o maggiore del numero scelto.
                        flag_risposta_minmax=0;
                        printf("\nE' minore o maggiore del numero scelto? (digitare: < o >) ");
                        fflush(stdin);
                        scanf("%c", &risposta);
                        if(risposta == '<') //se il numero generato e' minore allore il programma restringe il range
                            min = numero_generato;
                        else if(risposta == '>') //se il numero generato e' maggiore allore il programma restringe il range
                            max = numero_generato;
                        else
                            flag_risposta_minmax=1; //se non viene inserito ne un '<' ne un '>', allora ripete le istruzioni all'interno delll'iterazione do while(flag_risposta_minmax==1)
                        SEPARATORE; //estetica dell'output
                    }while(flag_risposta_minmax==1);
                }
            }
            else //se non viene inserito ne 'y' ne 'n', allora ripete le istruzioni all'interno delll'iterazione do while(flag_risposta_YN==1)
                flag_risposta_YN=1;

        } while (flag_risposta_YN==1);
    }
}

void indovinaSenzaTentativi()
{
    // il ciclo for, inizializza il contatore i per contare il numero di tantativi impiegati, e si incrementa ad ogni ciclo
    for (int i = 0, flag=0; flag==0; i++) //si interrompe appena viene trovato il numero che l'utente ha scelto
    {
        numero_generato = rand() % (max - min) + min; //non e' perfetto, ho cercato qualsiasi 'formula' per generare un numero da un intervallo preciso ma nessuna funziona.
        printf("\nrange: %d - %d\n", min, max); //stampa il range che il computer usa per provare ad indovinare il numero
        do
        {
            flag_risposta_YN=0;
            printf("\nNumero generato %d, e' giusto?(Y/N) ", numero_generato);
            fflush(stdin);
            scanf("%c", &risposta);
            if(risposta=='Y' || risposta=='y') //se viene digitato y = 'yes', stampa i tentativi utilizzati con messaggio di vittoria
            {
                printf("\nnumero indovinato in %d tentativi\n", i+1);
                flag=1; //interrompe il ciclo for
            }
            else if(risposta=='N' || risposta=='n') // se invece viene digitato n = 'no'
            {
                do
                {   //richiede se il numero generato e' minore o maggiore del numero scelto. 
                    flag_risposta_minmax=0;
                    printf("\nE' minore o maggiore del numero scelto? (digitare: < o >) ");
                    fflush(stdin);
                    scanf("%c", &risposta);
                    if(risposta == '<') //se il numero generato e' minore allore il programma restringe il range
                        min = numero_generato;
                    else if(risposta == '>') //se il numero generato e' maggiore allore il programma restringe il range
                        max = numero_generato;
                    else
                        flag_risposta_minmax=1; //se non viene inserito ne un '<' ne un '>', allora ripete le istruzioni all'interno delll'iterazione do while(flag_risposta_minmax==1)
                    SEPARATORE; //estetica dell'output
                }while(flag_risposta_minmax==1);
            }
            else //se non viene inserito ne 'y' ne 'n', allora ripete le istruzioni all'interno delll'iterazione do while(flag_risposta_YN==1)
                flag_risposta_YN=1;

        } while (flag_risposta_YN==1);
    }
}

int main()
{
    /*Gruppo:
   Matricola:  Alex Mazzoni       E-mail: alex.mazzoni3@studio.unibo.it
   Matricola:  Giovanni Luca      E-mail: giovanni.luca@studio.unibo.it
   Matricola:  Michele Farneti    E-mail: michele.farneti@studio.unibo.it
   */
    printf("\nSettimana 2 - Esercizio 2\t E-mail di riferimento: alex.mazzoni3@studio.unibo.it\n");

    srand(time(NULL));

    do //richiedi intervallo
    {
        flag=0;
        printf("\nInserire l'intervallo entro cui ha scelto il numero da (min>0) e (min<max):\nmin:");
        fflush(stdin);
        scanf("%d", &min);
        printf("max:");
        fflush(stdin);
        scanf("%d",&max);
        if (min <= 0 || min > max ) //se il numero min e' minore o uguale a zero la condizione esegue direttamente l'if senza controllare l'altra condizione (caratteristica dell'operatore OR (||))
        {
            printf("Numeri non validi\n\n");
            flag = 1;
        }
    } while (flag==1); // se non sono validi i numeri del range ripete le istruzioni 
    
    printf("Intervallo inserito: da %d a %d\n", min, max);

    int tentativi=0; //tentativi 
    printf("\ninserire il numero di tentativi con la quale si vuole giocare (0 = senza tentativi): ");
    fflush(stdin);
    scanf("%d", &tentativi); //non viene effettuato un controllo, percio' anche se immette una lettera il programma esegue il gioco senza tentativi. 

    //Avvia gioco    
    if(tentativi==0)    //la modalita' con i tentativi viene eseguita solo quando si inserisce un numero maggiore di 0
        indovinaSenzaTentativi();
    else
        indovinaConTentativi(tentativi);
    
    return 0;
}