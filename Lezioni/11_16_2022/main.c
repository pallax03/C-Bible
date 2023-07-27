#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// int calcola(int numero1, int numero2) {
//     return numero1 * numero2;
// }
// int calcola(int numero1, int *numero2) {
//     *numero2 = 20;
//     return numero1 * *numero2;
// }
int calcola(int numero1, int *numero2)
{
    *numero2 = 20;
    return 0;
}

void prePausa()
{
    // solo allocazione
    int A, B, C;
    int *ptr1, *ptr2, *ptr3;
    ptr1 = &A;

    printf("A   >     %d    %lld\n", A, &A);
    printf("ptr >     %lld    %lld    %d\n", ptr1, &ptr1, *ptr1);

    // inizializzazione
    A = 7;
    ptr1 = &A;

    printf("A   >    %d    %lld\n", A, &A);
    printf("ptr >     %lld    %lld    %d\n", ptr1, &ptr1, *ptr1);
    //-----------------------------------------

    A = 6;
    B = 4;
    C = 5;

    ptr3 = &A;
    ptr2 = &B;
    ptr1 = &C;
    printf("numeri: ");
    printf("%d\t%d\t%d", *ptr1, *ptr2, *ptr3);

    if (A >= B)
    {
        if (B >= C)
        {
            // sono già giusti
        }
        else
        {
            if (A >= C)
            { // n1,n3,n2
                ptr3 = &A;
                ptr2 = &C;
                ptr1 = &B;
            }
            else
            { // n3,n1,n2
                ptr3 = &C;
                ptr2 = &A;
                ptr1 = &B;
            }
        }
    }
    else
    {
        if (A >= C)
        { // n2,n1,n3
            ptr3 = &B;
            ptr2 = &A;
            ptr1 = &C;
        }
        else
        {
            if (B >= C)
            { // n2,n3,n1
                ptr3 = &B;
                ptr2 = &C;
                ptr1 = &A;
            }
            else
            { // n3,n2,n1
                ptr3 = &C;
                ptr2 = &B;
                ptr1 = &A;
            }
        }
    }
    printf(" -> ");
    printf("%d      %d      %d\n", *ptr1, *ptr2, *ptr3);

    // printf("%d * %d = %d", A, B, calcola(A, B));
    // printf("%d * %d = %d", A, B, calcola(A, &B));
    printf("B=%d\n", B);
    calcola(A, &B);
    printf("B ora vale = %d\n\n", B);
}

float calcolatrice(int numero1, char op, int numero2)
{
    float ris = 0.0;
    switch (op)
    {
    case '+':
        ris = numero1 + numero2;
        break;
    case '-':
        ris = numero1 - numero2;
        break;
    case '*':
        ris = numero1 * numero2;
        break;
    case '/':
        ris = numero1 / numero2;
        break;
    }
    return ris;
}

int richiediInput()
{
    int A = 0;
    char op;
    int B = 0;

    printf("\ninserire l'operazione da effettuare: ");
    scanf("%d%c%d", &A, &op, &B);
    printf("\t%d %c %d = %.1f", A, op, B, calcolatrice(A, op, B));
}

int main()
{
    prePausa();
    int casuale =  rand() % (-1 - 9) + -1; //[-1,8]
    
    int A[] = {1, 2, 3};
    int *ptr;
    ptr = &A[0];

    printf("%lld %d %d %d\n", A, A[0], A[1], A[2]);

    printf("%d %d %d %d\n", *ptr, ptr[0], ptr[1], ptr[2]);

    richiediInput();

    return 0;
}