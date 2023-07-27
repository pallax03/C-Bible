#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAX 20  // il define non utilizza memoria, semplicemente il compilatore sostituisce le istruzioni che la richiamano con il valore stabilito
#define MIN 1
#define RIGA_VUOTA printf("\n")
#define PULISCI system("cls")

void ordineCrescente()
{
        int numero1=0, numero2=0,numero3=0;
    printf("n1: ");
    fflush(stdin);
    scanf("%d", &numero1);
    printf("n2: ");
    fflush(stdin);
    scanf("%d", &numero2);
    printf("n3: ");
    fflush(stdin);
    scanf("%d", &numero3);
    RIGA_VUOTA;

    if(numero1>=numero2)
    {
        if(numero2>=numero3)
        {//n1,n2,n3
            printf("gia' in ordine crescente, pollo\n");
            printf("%d, %d, %d", numero1, numero2, numero3);
        }
        else
        {
            if(numero1>=numero3)
            {//n1,n3,n2
                printf("%d, %d, %d", numero1, numero3, numero2);
            }
            else
            {//n3,n1,n2
                printf("%d, %d, %d", numero3, numero1, numero2);
            }
        }
    }
    else
    {
        if(numero1>=numero3)
        {//n2,n1,n3
            printf("%d, %d, %d", numero2, numero1, numero3);
        }
        else
        {
            if(numero2>=numero3)
            {//n2,n3,n1
                printf("%d, %d, %d", numero2, numero3, numero1);
            }
            else
            {//n3,n2,n1
                printf("%d, %d, %d", numero3, numero2, numero1);
            }
        }
    }
}
void indovinaNumero() 
{
    srand(time(NULL)); //libreria per generare un numero casuale
    //indovina il numero
    char tmp = 'y';
    int n;
    int tentativi;

    do
    {
        printf("tentativi? ");
        fflush(stdin); //ripulisce il buffer della tastiera permette di evitare sbagli
        scanf("%d", &tentativi);

        int sorteggiato = rand() % (MAX - MIN) + MIN;

        int count=0;
        while (count<tentativi)
        {
            printf("\ntry n.%d\tinserisci un numero: ", count+1);
            fflush(stdin); //ripulisce il buffer della tastiera permette di evitare sbagli
            scanf("%d", &n);
            if(n==sorteggiato)
            {
                printf("\tBravooooo!");
                count = tentativi;
            }
            else
            {
                printf("\tHAI SBAGLIATO!!\n");
                if((int)count>=round(tentativi/2)) //il programma mostra i suggerimenti solo dopo la meta' dei tentativi rimasti
                {
                    if(n<sorteggiato)
                        printf("\t(Il numero inserito e' piu' piccolo del numero sorteggiato)\n\n");
                    else 
                        printf("\tIl numero inserito e' piu' grande del numero sorteggiato\n\n");
                }
            }
            count++;
        }
        printf("\n\n VUOI CONTINUARE? ");
        fflush(stdin);
        scanf("%c", &tmp);
    } while (tmp =='y' || tmp =='Y');
}
void provaRandom() 
{
    for (int i = 0; i < 20; i++)
        printf("numero: %d\n", rand() % (MAX - MIN) + MIN);
}

int main() {
    int i=1;
    while (i<256)
    {
        printf("numero: %d | ASCII: %c\n", i, i);
        i++;
    }

    return 0;
}