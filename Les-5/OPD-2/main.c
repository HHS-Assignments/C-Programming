#include <stdio.h>
#include "sudoku.h"

int main(int argc, char *argv[])
{
	int sudoku[N][N];
	int fouten_rijen[N];
	int fouten_kolommen[N];
	int fouten_blokken[N];
	int aantal_fouten_rijen;
	int aantal_fouten_kolommen;
	int aantal_fouten_blokken;
	const char *bestandsnaam;
	int i;
	int r;
	int k;

	for (i = 1; i <= (argc == 1 ? 1 : argc - 1); i++) {
		if (argc == 1) {
			bestandsnaam = "sudoku.txt";
		} else {
			bestandsnaam = argv[i];
		}

		if (!lees_sudoku(bestandsnaam, sudoku)) {
			printf("Kan bestand niet lezen: %s\n", bestandsnaam);
			continue;
		}

		printf("\nBestand: %s\n", bestandsnaam);
		cl /nologo /P /Fi:main.i main.c		printf("Sudoku zonder hokjes (gewijzigd):\n");
		for (r = 0; r < N; r++) {
			for (k = 0; k < N; k++) {
				printf("%d ", sudoku[r][k]);
			}
			printf("\n");
		}

		aantal_fouten_rijen = controleer_rijen(sudoku, fouten_rijen);
		aantal_fouten_kolommen = controleer_kolommen(sudoku, fouten_kolommen);
		aantal_fouten_blokken = controleer_blokken(sudoku, fouten_blokken);

		if (aantal_fouten_rijen == 0) {
			printf("Alle rijen zijn goed.\n");
		} else {
			printf("Fout in rijen: ");
			for (r = 0; r < aantal_fouten_rijen; r++) {
				printf("%d", fouten_rijen[r] + 1);
				if (r < aantal_fouten_rijen - 1) {
					printf(", ");
				}
			}
			printf("\n");
		}

		if (aantal_fouten_kolommen == 0) {
			printf("Alle kolommen zijn goed.\n");
		} else {
			printf("Fout in kolommen: ");
			for (k = 0; k < aantal_fouten_kolommen; k++) {
				printf("%d", fouten_kolommen[k] + 1);
				if (k < aantal_fouten_kolommen - 1) {
					printf(", ");
				}
			}
			printf("\n");
		}

		if (aantal_fouten_blokken == 0) {
			printf("Alle blokken zijn goed.\n");
		} else {
			printf("Fout in blokken: ");
			for (k = 0; k < aantal_fouten_blokken; k++) {
				printf("%d", fouten_blokken[k] + 1);
				if (k < aantal_fouten_blokken - 1) {
					printf(", ");
				}
			}
			printf("\n");
		}
	}

	return 0;
}
