    //VETTORE DINAMICO
char **double_ptr_insegnamenti;
char *ptr_insegnamenti;

    
    double_ptr_insegnamenti = malloc(sizeof(char*));
    double_ptr_insegnamenti = &ptr_insegnamenti;
    // ptr_insegnamenti = malloc(sizeof(char));
    char ch;
    int i;
    for ( i = 0; (ch = getch()) != '\r' ; i++)
    {
        char tmp[i];
        for (int j = 0; j < i; j++)
        {
            tmp[j] = ptr_insegnamenti[j];
        }
        ptr_insegnamenti = malloc(sizeof(char)*(i+1));
        for (int j = 0; j < i; j++)
        {
            *(ptr_insegnamenti+j) = tmp[j]; 
        }
        *(ptr_insegnamenti+i) = ch;
        printf("%c", *(ptr_insegnamenti+i));
    }
    
    // *(ptr_insegnamenti+0) = 'a';
    // // *(ptr_insegnamenti+1) = malloc(sizeof(char));
    // ptr_insegnamenti[1] = 'b';
    for (int j = 0; j < i; j++)
    {
        printf("%c", *(ptr_insegnamenti+i));
    }
    