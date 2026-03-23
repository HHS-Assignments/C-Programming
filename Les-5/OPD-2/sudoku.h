#ifndef SUDOKU_H
#define SUDOKU_H

#define N 9
#define DOEL_SOM 45

int lees_sudoku(const char *bestandsnaam, int sudoku[N][N]);
int controleer_rijen(const int sudoku[N][N], int fouten[N]);
int controleer_kolommen(const int sudoku[N][N], int fouten[N]);
int controleer_blokken(const int sudoku[N][N], int fouten[N]);

#endif
