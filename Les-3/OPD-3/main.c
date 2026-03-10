
#include <stdio.h>
#include <string.h>

struct vak {
	char naam[20];
	int ECTS;
};

// Print alle vakken in een array
void print_vakken(const struct vak vakken[], int size) {
	printf("Lijst van vakken:\n");
	for (int i = 0; i < size; ++i) {
		printf("%d: %s (%d ECTS)\n", i, vakken[i].naam, vakken[i].ECTS);
	}
}

void wijzig_vak_pointer(struct vak *v) {
	if (!v) return;
	printf("Nieuwe naam: ");
	if (scanf("%19s", v->naam) != 1) return;
	printf("Nieuwe ECTS: ");
	if (scanf("%d", &v->ECTS) != 1) return;
}

// (c) Wijzig een vak dat als waarde (copy) is doorgegeven.
// Omdat dit een kopie is, heeft dit geen effect op het origineel buiten de functie.
void wijzig_vak_value(struct vak v) {
	printf("(In functie, bewerk kopie) Nieuwe naam: ");
	if (scanf("%19s", v.naam) != 1) return;
	printf("(In functie, bewerk kopie) Nieuwe ECTS: ");
	if (scanf("%d", &v.ECTS) != 1) return;
	printf("(In functie) Gewijzigd: %s (%d ECTS)\n", v.naam, v.ECTS);
}

int main(void) {
	// Hardcoded array van vakken (a)
	struct vak vakken[] = {
		{"Programmeren", 6},
		{"Wiskunde", 5},
		{"Embedded Systems", 4},
	};
	int n = sizeof(vakken) / sizeof(vakken[0]);

	print_vakken(vakken, n);


	// Deel (b): wijzig via pointer — origineel in array verandert wel
	int index;
	printf("\n(b) Kies index van vak om te wijzigen: ");
	if (scanf("%d", &index) == 1 && index >= 0 && index < n) {
		printf("Huidig: %s (%d ECTS)\n", vakken[index].naam, vakken[index].ECTS);
		printf("Voer nieuwe gegevens in:\n");
		wijzig_vak_pointer(&vakken[index]);
		printf("Na functie-aanroep (main):\n");
		print_vakken(vakken, n);
	} else {
		printf("Ongeldige index of invoer, sla over.\n");
	}

	return 0;
}

