/* Opdracht 1:
Maak een functie die inkomsten belasting uitrekent bij een bepaald inkomen:
Zie https://www.belastingdienst.nl/wps/wcm/connect/nl/werk-en-inkomen/content/hoeveel-
inkomstenbelasting-betalen voor de specificatie van de tarieven. De functie hoeft geen rekening te
houden met personen die dit jaar AOW krijgen.
NB: Voor een belastingsysteem met schijven geldt: Als je 1 Euro bruto meer verdient, is je netto
salaris nooit lager dan als je 1 Euro minder had verdiend. Zie ook: https://nl.wikipedia.org/wiki/Schijventarief
Maak in de main een stuk code om de functie te testen. Printen en invoer van het toetsenbord alleen
in de main. */
#include <stdio.h>

#define SCHIJF_1_GRENS 38883.0
#define SCHIJF_2_GRENS 78426.0
#define TARIEF_1 0.3575
#define TARIEF_2 0.3756
#define TARIEF_3 0.4950

double berekenInkomstenbelasting(double inkomen) {
    if (inkomen <= 0) return 0.0;
    if (inkomen <= SCHIJF_1_GRENS) return inkomen * TARIEF_1;
    if (inkomen <= SCHIJF_2_GRENS) 
        return SCHIJF_1_GRENS * TARIEF_1 + (inkomen - SCHIJF_1_GRENS) * TARIEF_2;
    return SCHIJF_1_GRENS * TARIEF_1 + (SCHIJF_2_GRENS - SCHIJF_1_GRENS) * TARIEF_2 + 
           (inkomen - SCHIJF_2_GRENS) * TARIEF_3;
}

int main() {
    double inkomen, belasting;
    
    printf("Bruto jaarinkomen (euros): ");
    if (scanf("%lf", &inkomen) != 1 || inkomen < 0) {
        printf("Ongeldige invoer\n");
        return 1;
    }
    
    belasting = berekenInkomstenbelasting(inkomen);
    
    printf("\nBruto:      € %.2f\n", inkomen);
    printf("Belasting:  € %.2f\n", belasting);
    printf("Netto:      € %.2f\n", inkomen - belasting);
    printf("Tarief:     %.2f%%\n", inkomen > 0 ? (belasting / inkomen * 100) : 0);
    
    return 0;
}
