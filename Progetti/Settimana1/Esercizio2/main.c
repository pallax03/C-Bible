#include <stdio.h>

int main()
{
    /*Gruppo:
    Matricola:  Alex Mazzoni       E-mail: alex.mazzoni3@studio.unibo.it
    Matricola:  Giovanni Luca      E-mail: giovanni.luca@studio.unibo.it
    Matricola:  Michele Farneti    E-mail: michele.farneti@studio.unibo.it
    */
    printf("\nSettimana 1 - Esercizio 2\t E-mail di riferimento: alex.mazzoni3@studio.unibo.it\n");

    //Dichiarazioni variabili
    float migliapercorse, galloniconsumati; //Considero tutto in float poiche' penso che sia le miglia sia i galloni consumati possano essere anche decimali
    const float galloneperkm_litro = 235.214583571397; //Constante Km/Litro
    float migliapergallone, litriper100km;

    //Richiesta delle variabili
    printf("\nInserire le miglia percorse: ");
    scanf("%f", &migliapercorse); //richiedo dall'utente le miglia percorse
    printf("Inserire i galloni di benzina consumati: ");
    scanf("%f", &galloniconsumati); //richiedo dall'utente i galloni di benzina consumati

    //Calcolo MPG (Miles Per Gallon US)
    migliapergallone = migliapercorse / galloniconsumati;
    printf("\nMiglia Per Galloni = %.2f MPG (Miles Per Gallon)\n", migliapergallone); //usiamo nel placeholder gli attributi %.kf, nella quale la k sta per quanta precisione dopo la virgola si vuole

    //Calcolo MPG in Litri per 100Km 
    litriper100km = galloneperkm_litro / migliapergallone; //rapporto fra la costante e MPG
    printf("LitriPer100km = %.3f 100km/Litro \n", litriper100km);

    return 0;
}