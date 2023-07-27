#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))

void vettoriStessiValori()
{
    bool flag = true;
    int array[] = {1,2,4,6,2,6,4,7,2,632,26,25,14,75,2};
    const int lenght = sizeof(array)/sizeof(array[0]);
    int arraycount[lenght];
    int count = 0;

    printf("\nVettore: \n");
    for (int i = 0; i < lenght; i++)
    {
        flag = true;
        printf("%d:", array[i]);
        count = 0;
        for (int j = 0; j < lenght && flag ; j++)
        {
            if(array[i]==array[j])
            {
                if(j<i){flag = false;}
                count++;
            }
        }
        arraycount[i] = count;
        
        if(flag)
            printf(" %d\n", arraycount[i]);
        else
            printf(" gia' stampato\n");
    }
}

int main()
{
    int number;
    int x_min=2, y_min=3; //compresi
    int x_max=16, y_max=5; //compresi
    int x=2, y=3;
    clear();
    printf(
        "Enter your number in the box below (click enter to confirm position)\n"
        "+---------------+\n"
        "|               |\n"
        "|               |\n"
        "|               |\n"
        "+---------------+\n"
    );
    gotoxy(y, x);
    char c = ' ';
    while (c!='\r')
    {
        c = getch();
        switch (c)
        {
            case 'H':    // key up
                if(y-1>=y_min)
                    y--;
               break;
           case 'P':    // key down
                if(y+1<=y_max)
                    y++;
               break;
           case 'M':    // key right
                if(x+1<=x_max)
                    x++;
               break;
           case 'K':    // key left
                if(x-1>=x_min)
                    x--;
               break;
        }
        gotoxy(y, x);
    }
    
    scanf("%d", &number);
    

    return 0;
}