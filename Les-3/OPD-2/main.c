
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Genereert een array met 'size' random getallen tussen min en max (inclusief).
// Retourneert een pointer naar een nieuw gealloceerde array of NULL bij fout.
int *generate_random_array(int size, int min, int max) {
	if (size <= 0 || min > max) return NULL;
	int *arr = malloc(sizeof(int) * size);
	if (!arr) return NULL;
	for (int i = 0; i < size; ++i) {
		arr[i] = rand() % (max - min + 1) + min;
	}
	return arr;
}

// Berekent een nieuwe array met per index de grootste waarde van a1 en a2.
// Berekent een nieuwe array met per index de grootste waarde van a1 en a2.
// Als de arrays verschillende lengtes hebben, bevat het resultaat de
// grootste waarden voor overlappende indices en de resterende waarden van
// de langere array.
int *max_array(const int *a1, int size1, const int *a2, int size2, int *out_size) {
	if ((size1 <= 0 && size2 <= 0) || !out_size) return NULL;
	int size = (size1 > size2) ? size1 : size2;
	int *res = malloc(sizeof(int) * size);
	if (!res) return NULL;
	for (int i = 0; i < size; ++i) {
		if (i < size1 && i < size2) {
			res[i] = (a1[i] > a2[i]) ? a1[i] : a2[i];
		} else if (i < size1) {
			res[i] = a1[i];
		} else {
			res[i] = a2[i];
		}
	}
	*out_size = size;
	return res;
}

// Print een array op één regel.
void print_array(const char *name, const int *arr, int size) {
	if (!arr) return;
	printf("%s: [", name);
	for (int i = 0; i < size; ++i) {
		printf("%d", arr[i]);
		if (i < size - 1) printf(", ");
	}
	printf("]\n");
}

int main(void) {
	srand((unsigned)time(NULL));

	int size1, size2, min, max;
	printf("Aantal getallen voor Array1: ");
	if (scanf("%d", &size1) != 1 || size1 <= 0) {
		fprintf(stderr, "Ongeldige grootte.\n");
		return 1;
	}
	printf("Aantal getallen voor Array2: ");
	if (scanf("%d", &size2) != 1 || size2 <= 0) {
		fprintf(stderr, "Ongeldige grootte.\n");
		return 1;
	}
	printf("Minimum waarde: ");
	if (scanf("%d", &min) != 1) {
		fprintf(stderr, "Ongeldige invoer.\n");
		return 1;
	}
	printf("Maximum waarde: ");
	if (scanf("%d", &max) != 1) {
		fprintf(stderr, "Ongeldige invoer.\n");
		return 1;
	}
	if (min > max) {
		fprintf(stderr, "Minimum mag niet groter zijn dan maximum.\n");
		return 1;
	}

	// Gebruik de functie om twee arrays te genereren.
	int *array1 = generate_random_array(size1, min, max);
	int *array2 = generate_random_array(size2, min, max);
	if (!array1 || !array2) {
		fprintf(stderr, "Allocatie fout.\n");
		free(array1);
		free(array2);
		return 1;
	}

	// Print pas nadat beide arrays gegenereerd zijn.
	print_array("Array1", array1, size1);
	print_array("Array2", array2, size2);

	// Bereken resultaat en print.
	int result_size = 0;
	int *result = max_array(array1, size1, array2, size2, &result_size);
	if (!result) {
		fprintf(stderr, "Allocatie fout (resultaat).\n");
		free(array1);
		free(array2);
		return 1;
	}
	print_array("Resultaat", result, result_size);

	// Vrijgeven geheugen (geen geheugenlekken)
	free(array1);
	free(array2);
	free(result);
	return 0;
}
