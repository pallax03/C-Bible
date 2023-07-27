void bubbleSort(int array[]) {
    int size = sizeof(array) / sizeof(array[0]); //grandezza del vettore

    for (int i = 0; i < size - 1; i++) {    //gira per ogni elemento del vettore
        for (int j = 0; j < size - i - 1; j++) {    //controlla le coppie rimanenti in base alla i
            // cambiare il '>' se si vuole fare per ordine decrescente
            if (array[j] > array[j + 1]) {  //scambia di posto se il numero a destra e' minore del numero[j]
                //scambio di posto
                swap(array[j], array[j + 1]);
            }
        }
    }
}

void cocktailSort(int array[]) {
    int size = sizeof(array) / sizeof(array[0]); //grandezza del vettore

    bool swapped = true;
    int start = 0;
    int end = size - 1;
 
    while (swapped) {
        swapped = false;    //reset the flag
 
        //bubble sort
        for (int i = start; i < end; ++i) {
            if (array[i] > array[i + 1]) {
                swap(array[i], array[i + 1]);
                swapped = true; //if swapped set flag to true
            }
        }
 
        // se flag = false allora il vettore e' sorted
        if (!swapped)
            break;
 
        //reset the swapped flag
        swapped = false;
 
        // move the end point back by one, because
        // item at the end is in its rightful spot
        --end;
 
        // from right to left, doing the
        // same comparison as in the previous stage
        // so bubble but in the other direction
        for (int i = end - 1; i >= start; --i) {
            if (array[i] > array[i + 1]) {
                swap(array[i], array[i + 1]);
                swapped = true;
            }
        }
 
        // increase the starting point, because
        // the last stage would have moved the next
        // smallest number to its rightful spot.
        ++start;
    }
}