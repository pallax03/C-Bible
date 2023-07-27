#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>


int main() {
    char **stringhe;
    //vettore di stringhe (frasi)
    for (int i = 0; i < 2 ;i++)
    {
        char *stringa;
        //stringa dinamica
        int j=0;
        for (j = 0, stringa = (char *) malloc(sizeof(char)); (stringa[j] = getch()) != '\r' ; j++)
        {
            printf("%c", stringa[j]);
            stringa = (char *)realloc(stringa, sizeof(char));
            // if(stringa[i+1] == NULL) break;
        }
        stringa[j] = '\0';
        if(i==0) stringhe = (char **) malloc(sizeof(stringa));

        stringhe[i] = stringa; 
        stringhe = (char **) realloc(stringhe, sizeof(stringa));
        printf("\n");
    }   
    
    printf("\n\n%c",stringhe[1][0]);    
    
    return 0;
}