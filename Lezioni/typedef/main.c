#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

//il typedef e' un modo per definire il tipo di varibile in modo che per dichiararla puo' essere fatto solo scrivendo il nome definito.
typedef int Intero;

typedef struct
{
    char titolo[20];
    char autore[20];
} Libro;


int main() {
    
    Intero gino = 1; //esempio basico

    printf("%d", gino);

    Libro libri; //esempio struct (utile poiche' non bisogna ripetere il nome struct ogni volta ma basta il nome definito nel typedef).

    return 0;   
}