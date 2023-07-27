#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

#define PAROLE 5

void aggiungiParola(char *stringa[], int *count) {
    if(stringa[*count] == NULL)
    {
        char tmp[100];
        printf("\ninserisci la parola %d: ", *count + 1);
        scanf("%s", tmp);
        tmp[strlen(tmp)]='\0';
        stringa[*count] = malloc(sizeof(char)*strlen(tmp));
        if(stringa[*count]!=NULL)
        {
            strcpy(stringa[*count], tmp);
            *count = *count + 1;
            printf("parola aggiunta con successo\n");
        }
    }
}

void stampaParole(char *stringa[], int *count) {
    for (int i = 0; i < *count; i++)
    {
        if(stringa[i] != NULL)
        {
            printf("\t%s\n", stringa[i]);
        }
    }
}

int main() { 
    char *stringa[PAROLE];
    int count_parole=0;
    
    for (int i = 0; i < PAROLE; i++)
    {
        stringa[i] = NULL;
    }

    aggiungiParola(stringa, &count_parole);
    aggiungiParola(stringa, &count_parole);
    aggiungiParola(stringa, &count_parole);
    printf("\n");
    stampaParole(stringa, &count_parole);
    
    return 0;
}