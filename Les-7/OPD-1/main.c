#include <stdio.h>
#include <stdlib.h>

struct studieResultaat {
	int id;
	char vak[12];
	int ECTS;
	double cijfer;
};

int vergelijkTekst(const char tekst1[], const char tekst2[]) {
	int i = 0;

	while (tekst1[i] != '\0' && tekst2[i] != '\0') {
		if (tekst1[i] < tekst2[i]) {
			return -1;
		}
		if (tekst1[i] > tekst2[i]) {
			return 1;
		}

		i++;
	}

	if (tekst1[i] == '\0' && tekst2[i] == '\0') {
		return 0;
	}
	if (tekst1[i] == '\0') {
		return -1;
	}

	return 1;
}

void printResultaten(const struct studieResultaat resultaten[], int aantal) {
	int i;

	printf("ID   Vak          ECTS  Cijfer\n");
	printf("-------------------------------\n");

	for (i = 0; i < aantal; i++) {
		printf("%-4d %-12s %-5d %.1f\n",
			   resultaten[i].id,
			   resultaten[i].vak,
			   resultaten[i].ECTS,
			   resultaten[i].cijfer);
	}

	printf("\n");
}

int vergelijkVakNaam(const void *a, const void *b) {
	const struct studieResultaat *r1 = (const struct studieResultaat *)a;
	const struct studieResultaat *r2 = (const struct studieResultaat *)b;

	return vergelijkTekst(r1->vak, r2->vak);
}

int vergelijkEctsDanVak(const void *a, const void *b) {
	const struct studieResultaat *r1 = (const struct studieResultaat *)a;
	const struct studieResultaat *r2 = (const struct studieResultaat *)b;

	if (r1->ECTS < r2->ECTS) {
		return -1;
	}
	if (r1->ECTS > r2->ECTS) {
		return 1;
	}

	return vergelijkTekst(r1->vak, r2->vak);
}

int vergelijkCijferAfloop(const void *a, const void *b) {
	const struct studieResultaat *r1 = (const struct studieResultaat *)a;
	const struct studieResultaat *r2 = (const struct studieResultaat *)b;

	if (r1->cijfer < r2->cijfer) {
		return 1;
	}
	if (r1->cijfer > r2->cijfer) {
		return -1;
	}

	return vergelijkTekst(r1->vak, r2->vak);
}

int main(void) {
	struct studieResultaat resultaten[] = {
		{1001, "Wiskunde", 5, 7.4},
		{1002, "ProgramC", 5, 8.1},
		{1003, "Databases", 4, 6.9},
		{1004, "Netwerken", 3, 7.8},
		{1005, "Embedded", 4, 8.1}
	};

	int aantal = (int)(sizeof(resultaten) / sizeof(resultaten[0]));

	printf("Originele testdata:\n");
	printResultaten(resultaten, aantal);

	qsort(resultaten, aantal, sizeof(resultaten[0]), vergelijkVakNaam);
	printf("Gesorteerd op vaknaam:\n");
	printResultaten(resultaten, aantal);

	qsort(resultaten, aantal, sizeof(resultaten[0]), vergelijkEctsDanVak);
	printf("Gesorteerd op ECTS, daarna vaknaam:\n");
	printResultaten(resultaten, aantal);

	qsort(resultaten, aantal, sizeof(resultaten[0]), vergelijkCijferAfloop);
	printf("Gesorteerd op cijfer aflopend (praktisch):\n");
	printResultaten(resultaten, aantal);

	return 0;
}
