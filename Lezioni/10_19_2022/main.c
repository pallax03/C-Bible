#include <stdio.h>

#define SEPARATORE printf("\n-------------------------------------------------------------------------------------\n")
#define RIGA_VUOTA printf("\n")

int main()
{
    int n = 0, i=0;

    printf("inserisci fino a quanti numeri stampare: ");
    scanf("%d", &n);

    SEPARATORE;
    for (i = 0; i <= n; i++)
    {
        if(i%3==0)
            printf("%d, ", i);
    }
    
    SEPARATORE;
    i = 0;
    do
    {
        if(i%3==0)
            printf("%d, ", i);
        i++;
    }while (i <= n);

    SEPARATORE;
    i = 0;
    while (i <= n)
    {
        if(i%3==0)
            printf("%d, ", i);
        i++;
    }

    SEPARATORE;
    RIGA_VUOTA;

    // int contazeri=0;
    // char valore;

    // do
    // {
    //     valore = getch();
    //     if(valore == 0)
    //     {
    //         contazeri++;
    //     }

    // } while (valore == 13); //13 = codice ASCII '\r'.
    
    int numero[] = {1, 2, 3, 4, 5, 6};
    for (int count = 0; count < 6; count++)
    {
        if(numero[count]==2)
        {
            i=0;
        }
        else
        {
            for ( i = 2; i <= numero[count]/2; i++)
            {
                if(numero[count]%i==0)
                {
                    i = numero[count]-1;
                    printf("Il numero %d, non e' un numero primo!\n\n", numero[count]);
                }
            }
        }
        if(i!=numero[count])printf("Il numero %d, e' un numero primo!\n\n", numero[count]);
    }

    return 0;
}