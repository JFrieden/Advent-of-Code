#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 50
/* ----------------------------- Input Helpers ----------------------------- */
char** read_input(char* filename){
    FILE* file = fopen(filename, "r");
    char line[MAX_LINE];

    if (file == NULL) {
        printf("Error opening file %s.\n", filename);
        return NULL;
    }

    while(fgets(line, MAX_LINE, file) != NULL){
        printf("%s", line);    
    }

    fclose(file);
    return NULL;
}

/* ------------------------------------------------------------------------- */
/* ------------------------------- Solution -------------------------------- */



/* ------------------------------------------------------------------------- */
/* --------------------------------- Tests --------------------------------- */



/* ------------------------------------------------------------------------- */
/* --------------------------------- Main ---------------------------------- */
int main() {
    read_input("input.txt");
    return 0;
}
