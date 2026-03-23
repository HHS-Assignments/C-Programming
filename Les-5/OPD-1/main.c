#include <stdio.h>

#define N 9
#define DOEL_SOM 45

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

int som_rij(const int *rij)
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
		printf("Sudoku zonder hokjes:\n");
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
