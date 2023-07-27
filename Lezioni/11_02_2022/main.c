#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define ABSOLUTE_FILE "./file/file.txt"

void spiegazione()
{
    int numero;
    char ch;
    FILE *file;

    fprintf(stdout, "hello world!");

    file = fopen(ABSOLUTE_FILE, "r");   //mode: r → sola-lettura, w → scrittura, p → append.
    if(file != NULL)
    {
        if(feof(file)){}else{fscanf(file, "%d", &numero);}
        ch = fgetc(file);
        fclose(file);
    }

    
    file = fopen(ABSOLUTE_FILE, "w");
    if(file != NULL)
    {
        fprintf(file, "hello world!");   
        fclose(file);
    }
}

void scriviNelFile(FILE *file)
{
    file = fopen(ABSOLUTE_FILE, "w");   //mode: w → scrittura.
    if(file != NULL)
    {
        fprintf(file, "Ciaooooo franco,\n"
        "Come stai??\n"
        "\n"
        "   parole a casco,sasoams,soso.  ew"
        "\n"
        "\n"
        "Cordiali Saluti, VxeM.");   
        fclose(file);
    }
}

int main()
{
    FILE *file;
    scriviNelFile(file);
    
    char ch[2];
    int count=0;
    int word_counter=0;

    file = fopen(ABSOLUTE_FILE, "r");   //mode: r → sola-lettura.
    if(file != NULL)
    {
        while (!feof(file))
        {
            fscanf(file, "%c", &ch[0]);
            if(!isalnum(ch[0]))
            {
                if(isalnum(ch[1]))
                {
                    word_counter++;
                    printf("\n");
                }    
            }
            else printf("%c", ch[0]);
            ch[1]=ch[0];
        }
        fclose(file);
    }
    printf("\n\nparole contate: %d\n", word_counter);

    return 0;
}