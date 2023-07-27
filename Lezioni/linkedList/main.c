#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>

struct Node
{
    struct Node *next;

    int numero;
};

void addNode(struct Node **head, int num, ...); //num e' quanti sono i numeri che si inseriranno dopo

int main() {

    struct Node *head = NULL;
    addNode(&head, 3, 1, 2, 3);
  	printf("%d\n", head->anno_pubblicazione); // stampa 6
  	
	addNode(&head, 5, 1, 2, 3, 4, 5);
	printf("%d\n", head->anno_pubblicazione); // stampa 15
    
	return 0;
}

void addNode(struct Node **head, int num, ...) { //uso della lista args
	va_list args;
  	va_start(args, num);
	
	int sum = 0;
  	for (int i = 0; i < num; i++) {
  	  sum += va_arg(args, int);
  	}
  	va_end(args);
    struct Node *new_node = malloc(sizeof(struct Node));
    
	char *buffer = "ciao";
    new_node->titolo = calloc(strlen(buffer) ,sizeof(char));
	strcpy(new_node->titolo, buffer);
	new_node->anno_pubblicazione = sum;

    new_node->next = *head;
    *head = new_node;
}