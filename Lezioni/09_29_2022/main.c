//Librerie
#include <stdio.h>  // input / output
#include <stdlib.h> // gestione della memoria
#include <math.h>   // gestisce le operazioni matematiche
#include <time.h>   // data e ora
#include <string.h> // gestione delle stringhe

//Funzioni Aggiuntive
void stampaTabellaASCII(){
    for (int i = 0; i < 256; i++) { //ciclo eseguito dall'inizializzazione (i=0) fino alla condizione inserita (i<256), ad ogni ciclo la i incrementa di 1
        printf("numero: %d | ASCII: %c |\n", i, i); //ASCII CODE 27 bug
    }
}
void stampaTipiDato(int numero, float numero_razionale, char lettera){
    //%llu = long, tipo di dato di grandi dimensioni
    printf("tipo dato: int\t\tvalore: %d\t\tdimensione: %llu byte\n", numero, sizeof(int)); //sizeof restituisce la dimensione del tipo di dato
    printf("tipo dato: float\tvalore: %f\tdimensione: %llu byte\n", numero_razionale, sizeof(float));
    printf("tipo dato: char\t\tvalore: %c\t\tdimensione: %llu byte\n", lettera, sizeof(char));
}
void calcolatriceNoInput() {
    int numero1, numero2;
    float risultato;

    puts("inserisci il primo numero: ");
    scanf("%d", &numero1);

    puts("inserisci il secondo numero: ");
    scanf("%d", &numero2);

    risultato = numero1 + numero2;
    printf("%d + %d = %.0f\n", numero1, numero2, risultato); //arrotonda il float a quanto il segnaposto definisce (.1f)

    risultato = numero1 - numero2;
    printf("%d - %d = %.0f\n", numero1, numero2, risultato);

    risultato = numero1 * numero2;
    printf("%d(%d) = %.0f\n", numero1, numero2, risultato);

    risultato = (float) numero1 / numero2; //cast (trasformazione implicita del tipo di dato), non cambia il tipo di dato della variabile
    printf("%d/%d = %.1f\n", numero1, numero2, risultato);

    risultato = (float) (numero1 + numero2)/2;
    printf("La media fra %d e %d = %.2f\n", numero1, numero2, risultato);
}

//Inizio del programma
int main() {
    int numero = 6;
    float numero_razionale = 12.345678;
    char lettera = 'a';
    char stringa[] = "ciao";

    printf("Stampe iniziali\n"); // '\n' torna a capo | '\r' va nel rigo selezionato(?) | '\a' fa fare un beep al pc | '\t' e' una tabulazione(TAB)

    //placeholders preceduti dal '%'                                      //formato:
    printf("valore = %d %d %d\n", numero, numero_razionale, lettera);     //%d = numeric
    printf("valore = %f %f %f\n", numero, numero_razionale, lettera);     //%f = float
    printf("valore = %c %c %c\n", numero, numero_razionale, lettera);     //%c = char
    printf("valore = %s\n", stringa);                                     //%s = string

    //  Esercizio 1
    printf("\nTabella ASCII\n");
    stampaTabellaASCII();

    //  Esercizio 2
    printf("\nTipi di dati:\n");
    stampaTipiDato(numero, numero_razionale, lettera);

    //  Esercizio 3
    printf("\nCalcolatrice base:\n");
    calcolatriceNoInput();

    //  Esercizio 4
    printf("\nDato un input calcolare il suo valore in ASCII:\n");
    puts("inserisci il numero: ");
    scanf("%d", &numero);
    printf("numero: %d | ASCII: %c\n", numero, numero);

    return 0;
}
