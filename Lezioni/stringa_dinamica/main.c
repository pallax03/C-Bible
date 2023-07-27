char* getString() {
    char buffer[100];
    //stringa dinamica
    int i=0;
    for (i = 0; (buffer[i] = getch()) != '\r'; i++)
    {
        if(buffer[i]==' ')
            buffer[i]='_';
        else if(buffer[i]=='\b') {
            if(i!=0) i--;
        }
        printf("%c", buffer[i]);
    }
    buffer[i] = '\0';
    char * str = malloc(sizeof(char) * i);
    strcpy(str, buffer);
    return str;
}