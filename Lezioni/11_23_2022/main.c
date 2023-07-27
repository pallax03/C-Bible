#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>


ESERCIZIO 1
//con puntatori
struct giocatore
{
    char nome[10];
    int titolare;
    int maglia;
};

//senza puntatori
// struct giocatore
// {
//     char nome[10];
//     int titolare;
//     int maglia;
//     bool occupato;
// };

#define MAX 4

void inserisciGiocatori(struct giocatore *elenco[]);

int main() {

    // struct giocatore elenco_giocatori[MAX]; //vettore di struttura
    //con puntatori
    struct giocatore *elenco_giocatori[MAX]; //vettore di struttura

    // for (int i = 0; i < MAX; i++)
    // {
    //     elenco_giocatori[i].occupato=false;
    // }

    for (int i = 0; i < MAX; i++)
    {
        elenco_giocatori[i]=NULL;
    }

    inserisciGiocatori(elenco_giocatori);

    return 0;
}

//con puntatori
void inserisciGiocatori(struct giocatore *elenco[]) {
    
    for (int i = 0; i < MAX; i++)
    {
        if(elenco[i]==NULL)
        {
            elenco[i] = malloc(sizeof(struct giocatore));
            if(elenco[i]==NULL) {exit(1);} // se la malloc non riesce a aggiungere spazio in memoria
            printf("Giocatore %d\n", i+1);
            printf("\nNome giocatore: ");
            scanf("%s", elenco[i]->nome);
            printf("\nTitolare?[0,1] ");
            scanf("%d", &elenco[i]->titolare);
            printf("\nMaglia giocatore: ");
            scanf("%d", &elenco[i]->maglia);
        }
    }
}

//senza puntatori
// void inserisciGiocatori(struct giocatore elenco[]){
//     for (int i = 0; i < MAX; i++)
//     {
//         printf("Giocatore %d\n", i+1);
//         printf("\nNome giocatore: ");
//         scanf("%s", elenco[i].nome);
//         printf("\nTitolare?[0,1] ");
//         scanf("%d", &elenco[i].titolare);
//         printf("\nMaglia giocatore: ");
//         scanf("%d", &elenco[i].maglia);
//         elenco[i].occupato = true;
//     }
// }

// con puntatori
void stampaGiocatori(struct giocatore *elenco[]) {   
    for (int i = 0; i < MAX; i++)
    {
        if(elenco[i]!=NULL)
        {
            printf("Giocatore %s\n", elenco[i]->nome);
            printf("\ttitolare: %d\n", elenco[i]->titolare);
            printf("\tmaglia: %d\n", elenco[i]->maglia);
        }
    }
}

// senza puntatori
// void stampaGiocatori(struct giocatore elenco[]) {
//     for (int i = 0; i < MAX; i++)
//     {
//         if(elenco[i].occupato)
//         {
//             printf("Giocatore %s\n", elenco[i].nome);
//             printf("\ttitolare: %d\n", elenco[i].titolare);
//             printf("\tmaglia: %d\n", elenco[i].maglia);
//         }
//     }
// }

// // ESERCZIO 2
// //VARIANTE 1
// // struct punto
// // {
// //     int x;
// //     int y;
// // };
// //void elabora();


// //VARIANTE 2
// // struct punto
// // {
// //     int x;
// //     int y;
// // };
// // struct punto elabora() {
// //     struct punto p;
// //     p.x = 10;
// //     p.y = 5;

// //     return p;
// // }

// //VARIANTE 3
// struct punto
// {
//     int *x;
//     int y;
// };
// struct punto elabora() {
//     struct punto p;
//     int A = 10;
//     p.x = &A;
//     p.y = 5;

//     return p;
// }

// int main () {
//     //VARIANTE 3
//     struct punto p;
//     p=elabora();

//     //VARIANTE 2
//     // struct punto p;
//     // p=elabora();

//     //VARIANTE 1
//     //struct punto p;
//     // p.x = 10;
//     // p.y = 5;
//     // elabora(&p); //abbiamo passato l'indirizzo della variabile



//     return 0;
// }

// //VARIANTE 1
// // void elabora(struct punto *p) {
// //     p->x=432;
// //     p->y=84;

// // }