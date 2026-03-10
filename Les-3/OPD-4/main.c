#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct teamlid {
	int id;
	char naam[20];
	char opleiding[10];
};

int generatieId() {
	static int huidigId = 1000;
	return huidigId++;
}

int main() {
	int aantal;
	int i;
	char zoekOpleiding[10];
	int gevonden = 0;

	printf("Hoeveel teamleden wil je invoeren? ");
	scanf("%d", &aantal);

	if (aantal <= 0) {
		printf("Ongeldig aantal.\n");
		return 1;
	}

	struct teamlid* team = (struct teamlid*)malloc(aantal * sizeof(struct teamlid));

	if (team == NULL) {
		printf("Geheugen allocatie mislukt.\n");
		return 1;
	}

	for (i = 0; i < aantal; i++) {
		team[i].id = generatieId();

		printf("\nTeamlid %d\n", i + 1);
		printf("Naam (zonder spaties): ");
		scanf("%19s", team[i].naam);

		printf("Opleiding (max 9 tekens): ");
		scanf("%9s", team[i].opleiding);
	}

	printf("\nOp welke opleiding wil je zoeken? ");
	scanf("%9s", zoekOpleiding);

	printf("\nResultaten voor opleiding '%s':\n", zoekOpleiding);

	for (i = 0; i < aantal; i++) {
		if (strcmp(team[i].opleiding, zoekOpleiding) == 0) {
			printf("ID: %d | Naam: %s | Opleiding: %s\n", team[i].id, team[i].naam, team[i].opleiding);
			gevonden = 1;
		}
	}

	if (!gevonden) {
		printf("Geen teamleden gevonden met deze opleiding.\n");
	}

	free(team);
	return 0;
}
