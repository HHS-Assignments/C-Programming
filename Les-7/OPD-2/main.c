#include <stdio.h>

#define MAX_METINGEN 100

typedef double (*ConversieFunctie)(double);

double fahrenheit_naar_celsius(double fahrenheit) {
	return (fahrenheit - 32.0) * 5.0 / 9.0;
}

double volt_naar_celsius(double volt) {
	return -20.0 + (volt * 100.0 / 5.0);
}

int lees_meetwaardes(const char *bestandsnaam, double waarden[], int maxWaarden) {
	FILE *bestand;
	double waarde;
	int aantal = 0;

	bestand = fopen(bestandsnaam, "r");
	if (bestand == NULL) {
		printf("Kan bestand %s niet openen.\n", bestandsnaam);
		return 0;
	}

	while (aantal < maxWaarden && fscanf(bestand, "%lf", &waarde) == 1) {
		waarden[aantal] = waarde;
		aantal++;
	}

	fclose(bestand);
	return aantal;
}

void kopieer_met_conversie(const double waarden[], int aantal, ConversieFunctie conversie) {
	int i;

	for (i = 0; i < aantal; i++) {
		double geconverteerd = conversie(waarden[i]);
		printf("Origineel: %6.2f  -->  Geconverteerd: %6.2f\n", waarden[i], geconverteerd);
	}
}

int main(void) {
	double waarden[MAX_METINGEN];
	int aantal;

	printf("Fahrenheit naar Celsius:\n");
	aantal = lees_meetwaardes("fahrenheit.txt", waarden, MAX_METINGEN);
	kopieer_met_conversie(waarden, aantal, fahrenheit_naar_celsius);

	printf("\nVolt naar Celsius:\n");
	aantal = lees_meetwaardes("volt.txt", waarden, MAX_METINGEN);
	kopieer_met_conversie(waarden, aantal, volt_naar_celsius);

	printf("\nBij een druksensor maak je een nieuwe conversiefunctie met dezelfde vorm: double functie(double waarde). Daarna geef je die functie mee aan kopieer_met_conversie.\n");

	return 0;
}
