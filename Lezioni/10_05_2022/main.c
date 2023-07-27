#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

void formuleComposte()
{
    float decimal = 0;
    
    //somma
    printf("\n//somma\n");
    decimal = decimal + 1;
    printf("%.2f = %.2f + 1;\n", decimal, decimal-1);
    decimal += 10;
    printf("%.2f += 10;\t//decimal = %.2f\n", decimal-10, decimal);

    //incremento di 1
    printf("\n//incremento\n");
    printf("%.2f++;\t//decimal = %.2f\n", decimal++, decimal);
    printf("decimal = %.2f (in questo modo la usa e poi la incrementa)\n", decimal);
    printf("++%.2f;\t//decimal = %.2f\n", ++decimal, decimal);
    printf("decimal = %.2f (in questo modo la incrementa poi la usa)\n", decimal); 


    //differenza
    printf("\n\n//differenza\n");
    decimal = decimal - 2;
    printf("%.2f = %.2f - 2;\n", decimal, decimal+2);
    decimal -= 5;
    printf("%.2f -= 5;\t//decimal = %.2f\n", decimal+5, decimal);
    
    //decremento di 1
    printf("\n//decremento\n");
    printf("%.2f--;\t//decimal = %.2f\n", decimal--, decimal);
    printf("decimal = %.2f (in questo modo la usa e poi la decrementa)\n", decimal);
    printf("--%.2f;\t//decimal = %.2f\n", --decimal, decimal);
    printf("decimal = %.2f (in questo modo la decrementa poi la usa)\n", decimal); 


    //prodotto
    printf("\n\n//prodotto\n");
    decimal = decimal * 3;
    printf("%.2f = %.2f * 3;\n", decimal, decimal/3);
    decimal *= 2;
    printf("%.2f *= 2;\t//decimal = %.2f\n", decimal/2, decimal);


    //rapporto
    printf("\n\n//rapporto\n");
    decimal = decimal / 4;
    printf("%.2f = %.2f / 4;\n", decimal, decimal*4);
    decimal /= 2;
    printf("%.2f /= 2;\t//decimal = %.2f\n", decimal*2, decimal);
}
void scanfProblems()
{
    char lettera;
    int numero;

    printf("\ninserisci un numero: ");
    fflush(stdin); //ripulisce il buffer della tastiera permette di evitare sbagli
    scanf("%d", &numero);
    printf("numero: %d\n", numero);

    printf("\ninserisci una lettera: ");
    fflush(stdin); //ripulisce il buffer della tastiera permette di evitare sbagli
    scanf("%c", &lettera);
    printf("lettera: %c\n", lettera);
}
void numeroPariODispari()
{
    int numero;
    printf("\ninserisci un numero: ");
    fflush(stdin); //ripulisce il buffer della tastiera permette di evitare sbagli
    scanf("%d", &numero);
    if((numero%2)==0)printf("numero inserito: %d e' pari\n", numero);else printf("numero inserito: %d e' dispari\n", numero);
}

int main() {
    return 0;
}