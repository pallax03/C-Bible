#include <stdio.h>
#include <math.h>

//Operatori utilizzati

int main(void) 
{
    /*Gruppo:
   Matricola:  Alex Mazzoni       E-mail: alex.mazzoni3@studio.unibo.it
   Matricola:  Giovanni Luca      E-mail: giovanni.luca@studio.unibo.it
   Matricola:  Michele Farneti    E-mail: michele.farneti@studio.unibo.it
   */
    printf("\nSettimana 2 - Esercizio 1\t E-mail di riferimento: alex.mazzoni3@studio.unibo.it\n");

    double op1 = 5;
    double op2 = 7;

    //Operatori algebrici di base
    printf("La somma tra gli operandi %2.f e%2.f, realizzata mediante l'operatore '+', restituisce risultato %2.f\n",
           op1, op2, (op1 + op2));
    printf("La differenza tra gli operandi %2.f e%2.f, realizzata mediante l'operatore '-', restituisce risultato %2.f\n",
           op1, op2, (op1 - op2));
    printf("La moltiplicazione tra gli operandi %2.f e%2.f, realizzata mediante l'operatore '*', restituisce risultato %2.f\n",
           op1, op2, (op1 * op2));
    printf("La divisione tra gli operandi %2.f e%2.f, realizzata mediante l'operatore '/', restituisce risultato %f\n",
           op1, op2, (op1 / op2));
    //Nel caso del modulo, sono accettati solo operandi interi, perciò utilizzo il casting

    printf("Il modulo tra gli operandi %2.f e%2.f, realizzato mediante l'operatore '%', restituisce risultato %i\n\n",
           op1, op2, ((int) op1 % (int) op2));

    //Operatori incremento/decremento
    printf("L'operando 1, incrementato utilizzando l'operatore ++, dal valore di partenza %2.f, acquisiscie valore %2.f\n",
           op1++, op1);
    printf("L'operando 1, decrementato utilizzando l'operatore --, dal valore di partenza %2.f, acquisiscie valore %2.f\n\n",
           op1–, op1);
    printf("L'operando 1, incrementato utilizzando l'operatore ++, dal valore di partenza %2.f, acquisiscie valore %2.f\n",
           ++op1, op1);
    printf("L'operando 1, decrementato utilizzando l'operatore --, dal valore di partenza %2.f, acquisiscie valore %2.f\n\n",
           --op1, op1);

    //Operatori con assegnazione
    printf("La somma, effettuata mediante la sintassi op1 += op2 tra gli operandi %2.f e%2.f, assegna al primo operando il valore %2.f\n",
           op1, op2, op1 += op2);
    printf("La differenza, effettuata mediante la sintassi op1 -= op2 tra gli operandi %2.f e%2.f, assegna al primo operando il valore %2.f\n",
           op1, op2, op1 -= op2);
    printf("La moltiplicazione, effettuata mediante la sintassi op1 *= op2 tra gli operandi %2.f e%2.f, assegna al primo operando il valore %2.f\n",
           op1, op2, op1 *= op2);
    printf("La divisione, effettuata mediante la sintassi op1 /= op2 tra gli operandi %2.f e%2.f, assegna al primo operando il valore %2.f\n\n",
           op1, op2, op1 /= op2);

    int n = 256;
    //Operatori bitwise, agiscono sui bit
    //Operando singolo
    printf("Lo shift a destra di 2 bit, realizzato mediante l'operatore >>2 sulla variabile di valore %i, trasforma il valore della variabile in %i\n",
           n, n >> 2);
    printf("Lo shift a sinistra di 4 bit, realizzato mediante l'operatore <<4 sulla variabile di valore %i, trasforma il valore della variabile in %i\n",
           n, n << 4);
    printf("L'inversione dei bit, realizzato mediante l'operatore ~ sulla variabile di valore %i, trasforma il valore della variabile in %i\n",
           n, ~n);

    int bop1 = 382;
    int bop2 = 294;
    //Due operandi
    printf("L'AND logico dei bit, realizzato mediante l'operatore & sulle variabili di valore %i e %i, restituisce il valore %i\n",
           bop1, bop2, bop1 & bop2);
    printf("L'OR logico dei bit, realizzato mediante l'operatore | sulle variabili di valore %i e %i, restituisce il valore %i\n",
           bop1, bop2, bop1 | bop2);
    printf("Lo XOR logico dei bit, realizzato mediante l'operatore ^ sulle variabili di valore %i e %i, restituisce il valore %i\n\n",
           bop1, bop2, bop1 ^ bop2);

    //Operatori relazionali
    op1 = 5;
    op2 = 7;
    printf("Operatori relazionali;");

    printf("I Valori %2.f e %2.f sono uguali (op1==op2)?  ", op1, op2);
    if (op1 == op2) {
        printf("Vero\n");
    } else {
        printf("Falso\n");
    }

    printf("I Valori %2.f e %2.f sono diversi (op1!=op2)?  ", op1, op2);
    if (op1 != op2) {
        printf("Vero\n");
    } else {
        printf("Falso\n");
    }

    printf("Il valore %2.f e maggiore o uguale di %2.f (op1>=op2)?  ", op1, op2);
    if (op1 >= op2) {
        printf("Vero\n");
    } else {
        printf("Falso\n");
    }

    printf("Il valore %2.f e minore o uguale di %2.f (op1<=op2)?  ", op1, op2);
    if (op1 <= op2) {
        printf("Vero\n");
    } else {
        printf("Falso\n");
    }

    printf("Il valore %2.f e strettamente maggiore di %2.f (op1>op2)?  ", op1, op2);
    if (op1 >= op2) {
        printf("Vero\n");
    } else {
        printf("Falso\n");
    }

    printf("Il valore %2.f e strettamente minore di %2.f (op1<op2)?  ", op1, op2);

    if (op1 < op2)
    {
        printf("Vero\n");
    }
    else
    {
        printf("Falso\n");
    }

    //mostro comportamento scorretto con tipi non adeguati alla dimensione della variabile

    char MyChar = 150;
    printf("Valore char: %d\n", MyChar);
    int MyInt = 1.0e20;
    printf("Valore int: %d\n", MyInt);
    float MyFloat = 1.0e100;
    printf("Valore char: %f\n", MyFloat);
    int MyInt2 = 504.23;
    printf("Valore secondo int: %d\n (Si perdono le cifre decimali)\n", MyInt2);
    printf("Comportamento scorretto; il programma elaborerà in modo indefinito.\n\n");

    //mostro caso in cui operatori di side effects si trovano nella stessa istruzione
    int Side1 = 3;
    printf("valore Side1:  %d\n", Side1);
    int Side2 = 5;
    printf("valore Side2:  %d\n", Side2);
    int Side3;
    Side3 = (Side1++) + Side2;
    printf("Valore Side3(Somma tra le due var precedenti: %d\n", Side3);
    printf("Nota bene: La macchina su cui abbiamo elaborato il codice sembra dare la somma esatta,"
           "ma ciò può cambiare da architettura ad architettura\n\n");

    /*in questo caso è un problema poiché il programma potrebbe capire di fare prima la somma assegnandola
     e poi aumentando di uno la prima variabile, oppure prima aumentare di una unità la variabile e in seguito
     sommare, provocando così un risultato diverso. ATTENZIONE
     */

    //mostro cosa accade con regole di conversione implicita applicate
    char Charetto = 'a';
    printf("Charetto = %c\n", Charetto);
    int Integeretto = 10;
    printf("Integeretto = %d\n", Integeretto);
    float Floetto = 5.000000;
    printf("Floetto = %f\n", Floetto);
    double Doubletto = 6 ;
    printf("Doubletto = %lf\n", Doubletto);

    Integeretto = Charetto;
    printf("Char convertito in integer; Valore: %d\n", Integeretto);
    Floetto = Integeretto;
    printf("Integer convertito in float; Valore: %f\n", Floetto);
    Doubletto = Floetto;
    printf("Float convertito in double; Valore: %lf\n", Doubletto);
    Integeretto = Doubletto;
    printf("Double convertito in integer; Valore: %d\n", Integeretto);

    //principali funzioni di math.h
    printf("\nQueste sono invece le principali funzioni dellaa libreria <math.h>\n");
    int num1 = 2;
    int powy = 3;
    printf("floor(num1)= %f\n", floor(num1));
    printf("ceil(num1)= %f\n", ceil(num1));
    printf("fabs(num1)= %f\n", fabs(num1));
    printf("log(num1)= %f\n", log(num1));
    printf("log10(num1)= %f\n", log10(num1));
    printf("exp(num1)= %f\n", exp(num1));
    printf("sqrt(num1)= %f\n", sqrt(num1));
    printf("pow(num1, powy)= %f\n", pow(num1, powy));
    return 0;
}