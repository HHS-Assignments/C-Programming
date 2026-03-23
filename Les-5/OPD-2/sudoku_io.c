#include <stdio.h>
#include "sudoku.h"

int lees_sudoku(const char *bestandsnaam, int sudoku[N][N])
{
    FILE *bestand = fopen(bestandsnaam, "r");
    int r;
    int k;

    if (bestand == NULL) {
        return 0;
    }

    for (r = 0; r < N; r++) {
        for (k = 0; k < N; k++) {
            if (fscanf(bestand, "%d", &sudoku[r][k]) != 1) {
                fclose(bestand);
                return 0;
            }
        }
    }

    fclose(bestand);
    return 1;
}
