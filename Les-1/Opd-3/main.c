/* Opdracht 3:
Een module bestaat uit 6 deelcijfers. Het vak is behaald als minimaal een voldoende hebt als
gemiddelde en maximaal 1 vier. Het vak is met lof behaald indien het gemiddelde minimaal een 7,5
is en geen deelcijfer lager dan een 7. Laat de gebruiker de cijfers invullen.
- Geef ook een toelichting op het behaalde resultaat.
Randvoorwaarde:
- Gebruik 1 functie om het gemiddelde te berekenen
- 1 functie om het aantal te lage cijfers te berekenen
- Alleen in de main mag geprint worden
- Het programma blijft ook doorwerken als gebruikers bewust verkeerde input via het
toetsenbord geeft
- Is je code ook geschikt voor een ander aantal dan 6 deelcijfers?
- Hoeveel code moet je je wijzigen als de regels voor slagen/zakken aangepast worden */

#include <stdio.h>
#include <stdbool.h>

// Flexibele constanten - wijzig hier om aantal cijfers aan te passen
#define AANTAL_CIJFERS 6

// Berekent gemiddelde van array
float bereken_gemiddelde(float cijfers[], int aantal) {
    float som = 0.0;
    for (int i = 0; i < aantal; i++) {
        som += cijfers[i];
    }
    return som / aantal;
}

// Telt hoeveel cijfers onder de grenswaarde zijn
int tel_te_lage_cijfers(float cijfers[], int aantal, float grenswaarde) {
    int teller = 0;
    for (int i = 0; i < aantal; i++) {
        if (cijfers[i] < grenswaarde) {
            teller++;
        }
    }
    return teller;
}

int main() {
    // Constanten - wijzig hier om regels aan te passen
    const float MIN_GEMIDDELDE = 5.5;
    const float LOF_GEMIDDELDE = 7.5;
    const float ONVOLDOENDE_GRENS = 5.5;
    const int MAX_ONVOLDOENDES = 1;
    const float LOF_MIN_CIJFER = 7.0;
    
    float cijfers[AANTAL_CIJFERS];

    
    printf("=== CIJFER BEREKENING ===\n");
    printf("Voer %d deelcijfers in (tussen 0.0 en 10.0):\n\n", AANTAL_CIJFERS);
    
    // Vraag alle cijfers met input validatie
    for (int i = 0; i < AANTAL_CIJFERS; i++) {
        float cijfer;
        int geldig = 0;
        
        while (!geldig) {
            printf("Cijfer %d: ", i + 1);
            
            // Check of scanf een getal heeft gelezen
            if (scanf("%f", &cijfer) == 1) {
                if (cijfer >= 0.0 && cijfer <= 10.0) {
                    cijfers[i] = cijfer;
                    geldig = 1;
                } else {
                    printf("  --> ERROR: Cijfer moet tussen 0.0 en 10.0 zijn!\n");
                }
            } else {
                printf("  --> ERROR: Dat is geen geldig getal!\n");
                while (getchar() != '\n');  // Leeg input buffer
            }
        }
    }
    
    // Bereken resultaten
    float gemiddelde = bereken_gemiddelde(cijfers, AANTAL_CIJFERS);
    int aantal_onvoldoendes = tel_te_lage_cijfers(cijfers, AANTAL_CIJFERS, ONVOLDOENDE_GRENS);
    int aantal_onder_7 = tel_te_lage_cijfers(cijfers, AANTAL_CIJFERS, LOF_MIN_CIJFER);
    
    // Bepaal eindoordeel
    bool behaald = (gemiddelde >= MIN_GEMIDDELDE) && (aantal_onvoldoendes <= MAX_ONVOLDOENDES);
    bool met_lof = (gemiddelde >= LOF_GEMIDDELDE) && (aantal_onder_7 == 0);
    
    // Toon resultaat
    printf("\n=== RESULTAAT ===\n");
    printf("Gemiddelde: %.2f\n", gemiddelde);
    
    if (met_lof) {
        printf("Status: MET LOF BEHAALD!\n");
    } else if (behaald) {
        printf("Status: BEHAALD\n");
    } else {
        printf("Status: NIET BEHAALD\n");
    }
    
    return 0;
}