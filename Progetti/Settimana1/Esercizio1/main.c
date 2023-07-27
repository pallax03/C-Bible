#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{ 
    /*Gruppo:
   Matricola:  Alex Mazzoni       E-mail: alex.mazzoni3@studio.unibo.it
   Matricola:  Giovanni Luca      E-mail: giovanni.luca@studio.unibo.it
   Matricola:  Michele Farneti    E-mail: michele.farneti@studio.unibo.it
   */
    printf("\nSettimana 1 - Esercizio 1\t E-mail di riferimento: alex.mazzoni3@studio.unibo.it\n");

    int count = 0; //contatore utile per sapere quanti caratteri ogni printf stampa.
    //Tipi di dato
    //char      → ASCII Code format                             (Dimensione solita 1 Byte)
    //int       → Numero intero                                 (Dimensione solita 4 Byte)
    //float     → Numero decimale con precisione di 7 cifre     (Dimensione solita 4 Byte)
    //double    → Numero decimale con precisione di 11 cifre    (Dimensione solita 8 Byte)

    //Qualificatori
    //signed    → con segno (bit significativo)
    //unsigned  → senza segno (bit significativo)
    //long      → Aumenta lo spazio allocato di Byte per quel dato
    //long long → Aumenta lo spazio allocato di Byte per quel dato
    //short     → Diminuisce lo spazio allocato di Byte per quel dato


    //Placeholder
    // %[modificatore][campoMinimo][precisione][modificatoreLunghezza]specificaConversione
    
    //[modificatori]
    // '-' → allinea il risultato a sinistra (di default e' a destra).
    // '+' → il segno davanti al numero verra' sempre stampato (di default compare solo per i negativi il segno).
    // ' ' → inserisce uno spazio davanti al valore se il primo carattere non e' un segno.
    // '#' → se lo specificaConversione e' 'o' il primo valore stampato e' uno 0 poi il valore ottale (apparte quando il valore ottale e' 0).
    // '#' → se lo specificaConversione e' 'x' il primo valore stampato e' uno 0x poi il valore esadecimale (apparte quando il valore esadecimale e' nullo).
    // '0' → il campo viene riempito di 0 invece che con spazi.

    //[campoMinimo]             → puo' essere un numero intero o un '*', se il valore ha meno caratteri del campo vengono aggiunti spazi aggiuntivi, in base al numero intero inserito,
    //                          → se viene usato il '*', inserire subito prima della variabile interessata nell'argomento, un numero intero.
    
    //[precisione]              → si utilizza con '.n', dove n e' un numero intero oppure un '*' (stessa regola del campoMinimo sopra), cambia per ogni specificaConversione:
    //                          → se i, d, o, u, x → minimo numero di cifre.
    //                          → se a, e, f       → minimo numero di cifre dopo il punto decimale (un valore float ha una precisione di 6 cifre, un double di 15, e un long double di 19).
    //                          → se g             → massimo numero di cifre significative.
    
    //[modificatoreLunghezza]   → indica i diversi sottotipi dei tipi di dato:
    //                          → la lettera 'h', seguita da i, d, o, u, x indica che il dato e' uno short int o un signed short int.
    //                          → la lettera 'l', indica che il dato e' un long int o un unsigned long int.
    //                          → la lettera 'L', seguita da g, e, f indica che il dato e' um long double.
    //                          → la lettera 'i', indica che il tipo di dato puo' essere signed o unsigned char, signed o short int, signed o unsigned long int, signed o unsigned long long int.
    
    //specifica Conversione
    //%c   → char
    //%d   → integer
    //%f   → floating points
    //%g   → floating points e esponenziale(non visualizza le successioni di 0 finali)
    //%s   → string
    //%p   → stampa il puntatore della variabile
    //%o   → ottale
    //%x   → esadecimale
    //%e   → esponenziale
    //%le  → long esponenziale
    //%u   → unsigned
    //%hi  → signed integer short
    //%hu  → unsigned integer short
    //%l   → long
    //%llu → long long unsigned (la funzione sizeof() restituisce un valore long long unsigned).


    char lettera = 'a';
    count = printf("\nchar\t\t\tvalore: %0c\t\tdimensione: %llu byte (%d valore minimo %d valore massimo)\n", lettera, sizeof(lettera), CHAR_MIN, CHAR_MAX);
    //Stampo il valore restituito dalla funzione printf, ossia il numero di caratteri stampati
    printf("La funzione printf qui sopra ha stampato: %d caratteri\n", count);

    signed char lettera_signed = 'b';
    count = printf("\nsigned char\t\tvalore: %2c\t\tdimensione: %llu byte (%d valore minimo e %d valore massimo)\n", lettera_signed, sizeof(lettera_signed), SCHAR_MIN, SCHAR_MAX);
    printf("La funzione printf qui sopra ha stampato: %d caratteri\n", count);

    unsigned char lettera_unsigned = 'c';
    count = printf("\nunsigned char\t\tvalore: %-2c\t\tdimensione: %llu byte (0 valore minimo e %d valore massimo)\n", lettera_unsigned, sizeof(lettera_unsigned), UCHAR_MAX);
    //metto 0 poiche' un intero senza segno (unsigned) il suo valore minimo e' 0.
    printf("La funzione printf qui sopra ha stampato: %d caratteri\n\n", count);


    signed short int intero_signed_short = 65;
    count = printf("\nsigned short int\tvalore: %0d\t\tdimensione: %llu byte (%d valore minimo e %hi valore massimo)\n ", intero_signed_short, sizeof(intero_signed_short),SHRT_MIN,SHRT_MAX);
    printf("La funzione printf qui sopra ha stampato: %d caratteri\n", count);
    
    signed int intero_signed = 66;
    count = printf("\nsigned int\t\tvalore: %3d\t\tdimensione: %llu byte (%d valore minimo e %d valore massimo)\n", intero_signed, sizeof(intero_signed),INT_MIN,INT_MAX);
    printf("La funzione printf qui sopra ha stampato: %d caratteri\n", count);
    
    signed long int intero_signed_long = 67;
    count = printf("\nsigned long int\t\tvalore: %-3ld\t\tdimensione: %llu byte (%ld valore minimo e %ld valore massimo)\n", intero_signed_long, sizeof(intero_signed_long),LONG_MIN,LONG_MAX);
    printf("La funzione printf qui sopra ha stampato: %d caratteri\n", count);
    
    signed long long int intero_signed_longlong = 68;
    count = printf("\nsigned long long int\tvalore: % ld\t\tdimensione: %llu byte (%lld valore minimo e %lld valore massimo)\n", intero_signed_longlong, sizeof(intero_signed_longlong),LLONG_MIN,LLONG_MAX);
    printf("La funzione printf qui sopra ha stampato: %d caratteri\n\n", count);


    //unsigned = valore minimo del range 0
    unsigned short int intero_unsigned_short = 69;
    count = printf("\nunsigned short int\tvalore: %0d\t\tdimensione: %llu byte (0 valore minimo e %hu valore massimo)\n", intero_unsigned_short, sizeof(intero_unsigned_short), USHRT_MAX);
    printf("La funzione printf qui sopra ha stampato: %d caratteri\n", count);
    
    unsigned int intero_unsigned = 70;
    count = printf("\nunsigned int\t\tvalore: %4d\t\tdimensione: %llu byte (0 valore minimo e %lu valore massimo)\n", intero_unsigned, sizeof(intero_unsigned), UINT_MAX);
    printf("La funzione printf qui sopra ha stampato: %d caratteri\n", count);
    
    unsigned long int intero_unsigned_long = 71;
    count = printf("\nunsigned long int\tvalore: %-4ld\t\tdimensione: %llu byte (0 valore minimo e %lu valore massimo)\n", intero_unsigned_long, sizeof(intero_unsigned_long), ULONG_MAX);
    printf("La funzione printf qui sopra ha stampato: %d caratteri\n", count);
    
    unsigned long long int intero_unsigned_longlong = 72; //non ho capito molto bene la correzione modificatori + (spazio), ho aggiunto ora sia quello dei formati speciali sia uno spazio
    count = printf("\nunsigned long long int\tvalore: %#ld\t\tdimensione: %llu byte (0 valore minimo e %llu valore massimo)\n", intero_unsigned_longlong, sizeof(intero_unsigned_longlong), ULLONG_MAX);
    printf("La funzione printf qui sopra ha stampato: %d caratteri\n\n", count);


    float decimale_float = 12.3456;
    count = printf("\nfloat\t\t\tvalore: %-6f\tdimensione: %llu byte (%ld valore minimo e %llu valore massimo)\n", decimale_float, sizeof(decimale_float), FLT_MIN, FLT_MAX);
    printf("La funzione printf qui sopra ha stampato: %d caratteri\n", count);
    
    double decimale_double = 12.34567891234567890;
    //Utilizzo %5.4f per specificare la conversione (5 Campo minimo, 10 precisione).
    count = printf("\ndouble\t\t\tvalore: %5.4f\t\tdimensione: %llu byte (%ld valore minimo e %llu valore massimo)\n", decimale_double, sizeof(decimale_double), DBL_MIN, DBL_MAX);
    printf("La funzione printf qui sopra ha stampato: %d caratteri\n", count);
    
    long double decimale_double_long = 12.34567891234567890;
    //Utilizzo '%Le' per stampare in notazione esponenziale.
    count = printf("\nlong double\t\tvalore: %0.4Le\tdimensione: %llu byte (%lld valore minimo e %llu valore massimo)\n", decimale_double_long, sizeof(decimale_double_long), LDBL_MIN, LDBL_MAX);
    printf("La funzione printf qui sopra ha stampato: %d caratteri\n", count);

    return 0;
}
