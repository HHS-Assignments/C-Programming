#include "sudoku.h"

static int som_rij(const int *rij)
{
    int i;
    int som = 0;

    for (i = 0; i < N; i++) {
        som += rij[i];
    }

    return som;
}

int controleer_rijen(const int sudoku[N][N], int fouten[N])
{
    int r;
    int aantal_fouten = 0;

    for (r = 0; r < N; r++) {
        if (som_rij(sudoku[r]) != DOEL_SOM) {
            fouten[aantal_fouten] = r;
            aantal_fouten++;
        }
    }

    return aantal_fouten;
}

int controleer_kolommen(const int sudoku[N][N], int fouten[N])
{
    int r;
    int k;
    int som;
    int aantal_fouten = 0;

    for (k = 0; k < N; k++) {
        som = 0;
        for (r = 0; r < N; r++) {
            som += sudoku[r][k];
        }

        if (som != DOEL_SOM) {
            fouten[aantal_fouten] = k;
            aantal_fouten++;
        }
    }

    return aantal_fouten;
}

int controleer_blokken(const int sudoku[N][N], int fouten[N])
{
    int start_r;
    int start_k;
    int r;
    int k;
    int blok_nummer;
    int som;
    int aantal_fouten = 0;

    blok_nummer = 0;
    for (start_r = 0; start_r < N; start_r += 3) {
        for (start_k = 0; start_k < N; start_k += 3) {
            som = 0;
            for (r = start_r; r < start_r + 3; r++) {
                for (k = start_k; k < start_k + 3; k++) {
                    som += sudoku[r][k];
                }
            }

            if (som != DOEL_SOM) {
                fouten[aantal_fouten] = blok_nummer;
                aantal_fouten++;
            }

            blok_nummer++;
        }
    }

    return aantal_fouten;
}
