#include <stdio.h>  
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

//ho usato anche qua i colori ANSI, ma come si e' visto non funzionano, solo se si installa Mingw.
#define RESET "\x1B[0m"
#define BGCOLOR(r,g,b,c) printf("\e[48;2;%d;%d;%dm" "%c" RESET, (r), (g),(b),(c))
//              "\e[48;2;RED;GREEN;BLUEm"

//grandezza della matrice
#define ROWS    6
#define COLUMNS 6

float randomFloat(float min, float max){ //Funzione che genera numeri float da un intervallo 
   return ((max - min) * ((float)rand() / RAND_MAX)) + min;
}

int calcolaElementoMatrice(int i , int j) //tutte le formule che c'erano nella consegna
{
    float pulsazione = randomFloat(0.15, 0.80); // genera la ω (pulsazione)   nell'intervallo [0.15, 0.80]
    float fase_phi = randomFloat(0.0, 1.0);     // genera la φ (fase)         nell'intervallo [0.00, 1.00]
    float fase_psi = randomFloat(0.0, 1.0);     // genera la ψ (fase)         nell'intervallo [0.00, 1.00]
    float mi = randomFloat(0.0, 20.0);          // genera la μ (numero reale) nell'intervallo [0.00, 20.0]

    float funzione = sinf((pulsazione * i) + fase_phi) + sinf((pulsazione * j) + fase_psi); // fij = sin(ω(i) + φ) + sin(ω(j) + ψ)
    
    int beta = rand() % (129 - 256) + 129; // genera un numero intero nell'intervallo [128 , 256]
    return (int) floorf( (beta + mi) * (1 + (funzione / 2)) ) % beta; // calcolo finale che poi inseriamo all'interno della matrice
}

void stampaMatrice(int m[ROWS][COLUMNS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
            printf("\t%d", m[i][j]);
        printf("\n");
    }
}

int main()
{
    /*Gruppo:
    Matricola:  Alex Mazzoni       E-mail: alex.mazzoni3@studio.unibo.it
    Matricola:  Giovanni Luca      E-mail: giovanni.luca@studio.unibo.it
    Matricola:  Michele Farneti    E-mail: michele.farneti@studio.unibo.it
    */
    printf("\nSettimana 5 - Esercizio 1\t E-mail di riferimento: alex.mazzoni3@studio.unibo.it\n");

    srand(time(NULL));

    //dichiaro 3 matrici di grandezza uguali
    int matrice1[ROWS][COLUMNS];
    int matrice2[ROWS][COLUMNS];
    int matrice3[ROWS][COLUMNS];

    for (int i = 0; i < ROWS; i++)// gira le matrici e calcola ogni elemento, memorizzandolo al suo interno.
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            matrice1[i][j] = calcolaElementoMatrice(i , j);
            matrice2[i][j] = calcolaElementoMatrice(i , j);
            matrice3[i][j] = calcolaElementoMatrice(i , j);
        }
    }

    //io ho interpretato le matrici come una il rosso una il verde e una il blu.
    //formando cosi un colore rgb(matrice1[0][0];matrice2[0][0];matrice3[0][0]). (esempio rgb(20;255;0))
    printf("\n\t    Matrice 1\n\n");stampaMatrice(matrice1); 
    printf("\n\t    Matrice 2\n\n");stampaMatrice(matrice2);
    printf("\n\t    Matrice 3\n\n");stampaMatrice(matrice3);
    
    printf("\n\t    Matrice Uovo\n\n");
    for (int i = 0; i < ROWS; i++)
    {
        printf("\t     ");
        for (int j = 0; j < COLUMNS; j++)
        {
            char formauovo=' '; //219
            BGCOLOR(matrice1[i][j],matrice2[i][j],matrice3[i][j], formauovo);
        }
        printf("\n");
    }
    

    return 0;
}
