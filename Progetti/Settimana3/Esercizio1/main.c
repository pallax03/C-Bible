#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> //utilizzo la libreria <conio.h> per usare la funzione getch(); per prendere come input un char.
#include <ctype.h>
#include <stdbool.h>

#define SEPARATORE printf("\n--------------------------------------------------------------------------------------------------------------\n")

char risposta[10] = {""}; //variabili pubbliche tra tutte le funzioni
int x = 0, y = 0;   //coordinate x=longitudine, y=latitudine
bool correct = true, flag_risposta=true, flag_mappa=false;
unsigned int score = 0;

void mappa()
{
    flag_mappa=true;    //stampa la mappa, e il flag si aggiorna.
    printf("\n\t\t\t\t\tMAPPA DEI CONTINENTI\n"
    "\n\tANTARTIDE = 'J'\tAMERICA = 'G'\tEUROPA = 'E'\tASIA = 'R'\tOCEANIA = '5'\tAFRICA = '#'\n"
    "\n\t\t\t\t\t      (MEDIANA)\n\n"
    "                     ..:~~^^^^:^^^^^~~!!~~~~~!7~^:|^::^~::^!:.....:....::::::... ....\n"                   
    "                 ..::^^::::^GGGGG55GGGGGGGGGGGGG?^|?^^~!^:.::^!:::^~^^^:^:::^^^^::......\n"               
    "             .:GGGGGGGGGGGGGGGGGGGGGGG^.GGGGGG??~:|?^:7EEEE?7E5!RRRRRRRRRRRRRRRRRRRRRR.. ..\n"          
    "           .:^^GGGGGGGGGGGGGGGGPGGGGGGG?..GG~.~.^:|~EEEEEEEEEEEEERRRRRRRRRRRRRRRRRRRRRR.......\n"      
    "        .^^^::^:^:. GGGGGGGGGGGGGGGGGG^: . :~ : ~E|EEEEEEEEEEEEE!RRRRRRRRRRRRRRRRRRRRRRRRR.RR...\n"    
    "      .:::..........~GGGGGGGGGGGGGGGG!^..: ~... ^~|EEEEEEEEEEEEEE~RRRRRRRRRRRRRRRRRRRR^R^R.......\n"   
    "     :^......:......PGGGGGGGGGGGG~ .. : ...7:::.EE|?E?7EE~EEEEEEE`RRRRRRRRRRRR^^.^:......... .....\n"
    "    ^:.:....:.::.:..GGGGGGGGGG:...: .. :.:!.^:^5##|###..##..######!RRRRRRRRRRRRRRR^^.R..R.R...... .\n"
    "   ^: : .: :..: .. : !GGG?.^.GG^: .. :. : ^: .!###|###############J.RRRRRRRRRRRRRR^.R. R .. . .. ..\n"
    "  .^ .. :..: :. : .. :.!GGGG!^^~!.^. :..: ~:..####|################!. RRRR.RRRRR^R R..R .... .. ....\n"
    "  ^. : .. :. : .. .. :  . ^GGGGGGGG:.: .. ~..:!###|#############7 :: RRRR .^R^RRR..R.R..R.R. ...^ ..\n"
    "0 ----------------------------------------------- o ------------------------------------------------   (Equatore)\n"
    "  ^:.: .: :..: .. .. : .. .. !PGGGGGGGGGP~~. : .: | :#######5 #.^ ^: :..: :..:.:^5~5~!5^5!5~:!.:: ^\n"
    "  .~.:. :.:^:^:.: .. :..: .. ::7PGGGGGGG7 ~: :..: | ^######P!##  ~..: .. :..: ..:55555555:..::~.:~\n"
    "   ^: : .. :..: :. : .. :..: .. YGGGGGJ~: ^: : .: | .#####P:.##...~ .. :..: .. :555555555555:.:: ^.\n"
    "    ^^.:....:..: :..: :..: :..: JGGGGY: :.:^ :..: | :.Y###... :.:~ :..: :..: ..?5555555555^...:.^:\n"
    "     :^......:....:....:....: ..?GG5!.: ...~ ...: | : ::#. :..: ~..: :..: :....:...5555~...:55!.\n"  
    "      .^:....................: .~GG^.....: ~... : | : : ...: :.:^ : ...: ............^...:~~5:\n"   
    "        .^::..................:..!Y7^^ :.:::~.: : |.:.: :......~.:::....................:::. \n"     
    "         :^^^^^::^:::^:.::^::::::..^::~^^.::7::.^.|::...^:::^.~:.::::::::::::::.:::::::^^. \n"      
    "              ..:::::.....:::JJJJ:J::JJ~JJJ^......|:JJJJ~~^~^~!J?J!!~!JJJJ?J?J?J??J!J^^::\n"          
    "                 .::::^~JJ?J??JJJJJJ?JJJJJ^~J~~JJ?|JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ!J^:.\n"           
    "                     ..:~JJJJJJJJJJJJJJJJJJJJJJJJJ|JJJJJJJJJJJJJJJJJJJJJJJ~:...  ....\n"   
    );                            //immagine dei confini: https://ibb.co/Vxc4bMC
    // longitudine = x  (-180°<x<180°)
    // latitudine = y   (-90°<y<90°)

                    //    X         //  Y
    //ANTARTIDE:    // -180°, 180°  //-90°, -60°
    //AMERICHE:     // -180°, -30°  //-60°,  90°
    //EUROPA:       // - 30°,  60°  // 35°,  90°
    //ASIA:         //   60°, 180°  //  0°,  90°  
    //OCEANIA:      //   60°, 180°  //-60°,   0° 
    //AFRICA:       // - 30°,  60°  //-60°,  35°
}

void chiediEControllaRisposta(time_t start_clock)
{
    flag_risposta = true;
    printf("\ncoordinate generate:\tlongitudine (x): %d\tlatitudine (y): %d\n", x, y);
    printf("in che continente siamo? ");
    for(int i=0;i<sizeof(risposta);i++) risposta[i]=' '; //ripulisco il vettore potrebbero esserci dentro risposte vecchie
    for(int i=0;flag_risposta; i++) //scorre il vettore lettera per lettera, e esce dal ciclo quando il flag viene aggiornato a false
    {
        risposta[i]=tolower(getch()); //richiede la lettera e la converte a minuscola.
        printf("%c", risposta[i]); 
        time_t tempo_passato = (clock() - start_clock); //calcola il tempo che l'utente sta impiegando per dare una risposta.
        //uso gli else if per una questione di ottimizzazione se il primo e' vero allora non esegue il resto degli else if e cosi a cascata.
        if( tempo_passato > 30000) // se l'utente impiega piu di 30 secondi perde. (1 minuto in ms = 60 000);
        {
            printf("\n\n\tTempo Scaduto!\n\n");
            flag_risposta = false; //esce da questo ciclo
            correct = false;       //flag per far capire che l'utente ha perso
        }
        else if(i>1) //per il programma e' sufficiente inserire le sigle dei continenti, percio' se si richiede la terza lettera (si parte da 0),
        {            //qui ci entra solo se la risposta non e' ne un continente ne la mappa, percio' il ciclo si interrompe e per comodita' imposta come prima lettera la m 
            flag_risposta=false;
            risposta[0]='m';
        }
        else if(risposta[0]=='e')       //europa
        {flag_risposta = false;printf("uropa"); //per estetica stampa le lettere mancanti della parola europa (e' solo una stampa)
            if(x >= -30 && x <= 60) //controlla se le coordinate appartengono effettivamente all'europa
            {
                if(y >= 35 && y <= 90)
                     score += (int)100000/tempo_passato; //se appartengono ad essa calcola il punteggio
                else correct=false; //altrimenti la risposta e' sbagliata
            } else correct=false;
        }
        else if(risposta[0]=='m')
        {    flag_risposta=false;printf("appa");
            if(!flag_mappa) mappa(); else printf("\t\t\tmappa gia' richiesta!");    //stampa la mappa solo se in queste coordinate non l'ha stampata
        }
        else if(risposta[0]=='o')       //oceania
        {flag_risposta = false;printf("ceania");
            if(x >= 60 && x <= 180) //controlla se le coordinate appartengono effettivamente all'oceania
            {
                if(y >= -60 && y <= 0)
                     score += (int)100000/tempo_passato;
                else correct=false;
            } else correct=false;
        }
        else if(risposta[0]=='a')   //ci sono diversi continenti che iniziano per a    
        {
            if(risposta[1]=='f')        //africa
            {flag_risposta = false;printf("rica");
                if(x >= -30 && x <= 60) //controlla se le coordinate appartengono effettivamente all'africa
                {
                    if(y >= -60 && y <= 35)
                         score += (int)100000/tempo_passato;
                    else correct=false;
                } else correct=false;
            }
            else if(risposta[1]=='m')   //america
            {flag_risposta = false;printf("erica"); 
                if(x >= -180 && x <= -30) //controlla se le coordinate appartengono effettivamente all'america
                {
                    if(y >= -60)
                         score += (int)100000/tempo_passato;
                    else correct=false;
                } else correct=false;
            }
            else if(risposta[1]=='n')   //antartide
            {flag_risposta = false;printf("tartide");
                if(y<=-60) score += (int)100000/tempo_passato; //controlla se le coordinate appartengono effettivamente all'antartide
                else correct = false;
            }
            else if(risposta[1]=='s')   //asia
            {flag_risposta = false;printf("ia");
                if(x >= 60 && x <= 180) //controlla se le coordinate appartengono effettivamente all'asia
                {
                    if(y >= 0 && y <= 90)
                         score += (int)100000/tempo_passato;
                    else correct=false;
                } else correct=false;
            }
        }
    }
}

int main() 
{
    /*Gruppo:
   Matricola:  Alex Mazzoni       E-mail: alex.mazzoni3@studio.unibo.it
   Matricola:  Giovanni Luca      E-mail: giovanni.luca@studio.unibo.it
   Matricola:  Michele Farneti    E-mail: michele.farneti@studio.unibo.it
   */
    printf("\nSettimana 3 - Esercizio 1\t E-mail di riferimento: alex.mazzoni3@studio.unibo.it\n\n");

    printf("\t\t\t\t\t     TUTORIAL\n\n"
    "Il gioco consiste nell'indovinare il continente date due coordinate.\n"
    "Per essere il piu' precisi possibili abbiamo preso la mappa in 2D, preso la mediana come asse delle y e l'equatore come asse delle x:\n"
    "\t- asse delle x (equatore) = Longitudine e' un valore compreso tra -180 e 180.\n"
    "\t- asse delle y (mediana) = Latitudine e' un valore compreso tra -90 e 90.\n"
    "Percio possiamo definire punto di origine: o (nella mappa), il punto di coordinate (0,0),\n"
    "i confini dei continenti sono stati presi a rettangoli nel piano percio' anche un punto nell'oceano appartiene al continente piu' vicino,\n"
    "consulatare l'immagine della mappa (https://ibb.co/Vxc4bMC) per capire meglio, le linee nere sono la mediana e l'equatore.\n\n"
    "Se indovini il continente il gioco va avanti (non ha una fine) e ne ripropone un altro con diverse coordinate, se invece sbagli il gioco finisce.\n"
    "Mi raccomando hai solo 30 secondi per indovinare il continente, ma piu' veloce sarai e piu' punti prendi.\n\n"
    "Basta inserire le iniziali per ogni input:\n"
    "\t - an (Antartide): se le coordinate appartengono all'Antartide.\n"
    "\t - am (America):   se le coordinate appartengono all'America del sud o quella del nord.\n"
    "\t - e  (Europa):    se le coordinate appartengono all'Europa.\n"
    "\t - as (Asia):      se le coordinate appartengono all'Asia.\n"
    "\t - o  (Oceania):   se le coordinate appartengono all'Oceania.\n"
    "\t - af (Africa):    se le coordinate appartengono all'Africa.\n"
    "\t - m  (mappa):     se hai bisogno del suggerimento della mappa.\n\n"
    "\nIl gioco iniziera' appena clicchi enter.\n");
    scanf("%c", &risposta[0]);
    
    do
    {
        fflush(stdin); //ripulisce il buffer dell'input da tastiera

        //se si vuole iniziare il gioco dopo 20 secondi
        //time_t now = clock();
        //for (; clock() - now < 20*CLOCKS_PER_SEC;); //il gioco inizia fra 20 secondi, il tempo di leggere il tutorial

        srand(time(NULL));
        int count = 0; //conta quanti continenti sono stati chiesti.


        do
        {
            count++;
            printf("\n\tContinente: %d\t\tpunteggio: %d\n", count, score);
            flag_mappa=false; //flag che se la mappa e' gia' stata chiesta per queste coordinate non la puoi piu' richiedere.
            correct = true;   //flag per capire se la il continente e' inserito e' corretto
            x = rand() % (180 - (-180)) + (-180); //genera la Longitudine valore compreso: -180 < x < 180.
            y = rand() % (90 - (-90)) + (-90);    //genera la Latitudine  valore compreso: - 90 < y <  90.

            time_t start_clock = clock(); //prende il clock di questo istante.
            do
            {
                SEPARATORE;
                chiediEControllaRisposta(start_clock);
            }while(risposta[0]=='m'); //se viene chiesta la mappa richiede l'input del continente, anche se l'utente non inserisce come risposta un continente
            SEPARATORE;

        } while (correct); //se ha indovinato allora richiede un altro continente

        //appena esce vuol dire che ha perso e mostra il punteggio
        printf("\t\nHai perso!!\t\t\t punteggio: %d\n", score);

        printf("\n\nVuoi rigiocare? (digita 'y' per rigiocare) ");
        scanf("%c", &risposta[0]);
    }while(tolower(risposta[0])=='y');
    
    return 0;
}