/* Opdracht 4:
We gaan nu met een tekstbestand werken. Zie H9.7
In het tekstbestand staat uitslagen van een voetbalclub. Hier onder een voorbeeld. Bij een andere 
aantal regels (max 36) en uitslagen werkt je programma ook correct. Een regel is wel op de manier 
uit het voorbeeld opgebouwd:
Thuis 1 - 0 PSV
Uit 0 – 3 ADO
Uit 2 – 0 Sparta

a) Gebruik een struct om ieder regel uit het bestand op te slaan. 
b) Print nu alle tegenstanders
c) Vervolgens ga je op basis van de array van structs de punten en het doelsaldo bereken.
d) Sla ook het resultaat van deze berekening op in een andere struct. Print op basis van dit 
   bestand: 3 wedstrijden, 6 punten en doelsaldo (4-2). NB: gelijkspelen kunnen uiteraard ook
e) Geef de gebruiker de mogelijkheid om de naam van een tegenstander in te typen en geef 
   aan of van die club is gewonnen of niet. */

#include <stdio.h>
#include <string.h>

#define MAX_WEDSTRIJDEN 36
#define MAX_TEAMNAAM 50

/* Struct om een wedstrijd op te slaan */
struct Wedstrijd {
    char thuisOfUit[10];  /* "Thuis" of "Uit" */
    int doelpuntenVoor;   /* Aantal doelpunten van ons team */
    int doelpuntenTegen;  /* Aantal doelpunten van tegenstander */
    char tegenstander[MAX_TEAMNAAM];  /* Naam van de tegenstander */
};

/* Struct om de totale statistieken op te slaan */
struct Statistieken {
    int aantalWedstrijden;
    int totaalPunten;
    int doelsaldoVoor;    /* Totaal aantal gemaakte doelpunten */
    int doelsaldoTegen;   /* Totaal aantal gekregen doelpunten */
};

/* Functie om punten te berekenen voor een wedstrijd */
int berekenPunten(int doelpuntenVoor, int doelpuntenTegen) {
    if (doelpuntenVoor > doelpuntenTegen) {
        return 3;  /* Gewonnen */
    } else if (doelpuntenVoor == doelpuntenTegen) {
        return 1;  /* Gelijk gespeeld */
    } else {
        return 0;  /* Verloren */
    }
}

/* Functie om statistieken te berekenen */
struct Statistieken berekenStatistieken(struct Wedstrijd wedstrijden[], int aantal) {
    struct Statistieken stats;
    stats.aantalWedstrijden = aantal;
    stats.totaalPunten = 0;
    stats.doelsaldoVoor = 0;
    stats.doelsaldoTegen = 0;
    
    /* Loop door alle wedstrijden */
    for (int i = 0; i < aantal; i++) {
        stats.totaalPunten += berekenPunten(wedstrijden[i].doelpuntenVoor, 
                                            wedstrijden[i].doelpuntenTegen);
        stats.doelsaldoVoor += wedstrijden[i].doelpuntenVoor;
        stats.doelsaldoTegen += wedstrijden[i].doelpuntenTegen;
    }
    
    return stats;
}

/* Functie om te zoeken of er van een tegenstander is gewonnen */
void zoekTegenstander(struct Wedstrijd wedstrijden[], int aantal, char* teamnaam) {
    int gevonden = 0;
    
    for (int i = 0; i < aantal; i++) {
        if (strcmp(wedstrijden[i].tegenstander, teamnaam) == 0) {
            gevonden = 1;
            int punten = berekenPunten(wedstrijden[i].doelpuntenVoor, 
                                       wedstrijden[i].doelpuntenTegen);
            
            printf("\nWedstrijd tegen %s (%s): %d - %d\n", 
                   wedstrijden[i].tegenstander,
                   wedstrijden[i].thuisOfUit,
                   wedstrijden[i].doelpuntenVoor,
                   wedstrijden[i].doelpuntenTegen);
            
            if (punten == 3) {
                printf("Resultaat: Gewonnen!\n");
            } else if (punten == 1) {
                printf("Resultaat: Gelijk gespeeld\n");
            } else {
                printf("Resultaat: Verloren\n");
            }
        }
    }
    
    if (!gevonden) {
        printf("\nTegenstander '%s' niet gevonden\n", teamnaam);
    }
}

int main() {
    FILE* fp;
    struct Wedstrijd wedstrijden[MAX_WEDSTRIJDEN];
    int aantalWedstrijden = 0;
    char zoekNaam[MAX_TEAMNAAM];
    
    /* Open het bestand voor lezen */
    fp = fopen("uitslagen.txt", "r");
    
    /* Controleer of het bestand geopend kon worden */
    if (fp == NULL) {
        printf("Bestand kan niet geopend worden\n");
        return -1;
    }
    
    /* Lees alle wedstrijden uit het bestand */
    while (aantalWedstrijden < MAX_WEDSTRIJDEN) {
        int resultaat = fscanf(fp, "%s %d - %d %s", 
                               wedstrijden[aantalWedstrijden].thuisOfUit,
                               &wedstrijden[aantalWedstrijden].doelpuntenVoor,
                               &wedstrijden[aantalWedstrijden].doelpuntenTegen,
                               wedstrijden[aantalWedstrijden].tegenstander);
        
        /* Stop als we het einde van het bestand bereiken */
        if (resultaat != 4) {
            break;
        }
        
        aantalWedstrijden++;
    }
    
    /* Sluit het bestand */
    fclose(fp);
    
    printf("=== VOETBAL UITSLAGEN ===\n\n");
    
    /* b) Print alle tegenstanders */
    printf("Alle tegenstanders:\n");
    for (int i = 0; i < aantalWedstrijden; i++) {
        printf("- %s\n", wedstrijden[i].tegenstander);
    }
    
    /* c) en d) Bereken en print statistieken */
    struct Statistieken stats = berekenStatistieken(wedstrijden, aantalWedstrijden);
    
    printf("\n=== STATISTIEKEN ===\n");
    printf("%d wedstrijden, %d punten en doelsaldo (%d-%d)\n", 
           stats.aantalWedstrijden,
           stats.totaalPunten,
           stats.doelsaldoVoor,
           stats.doelsaldoTegen);
    
    /* e) Geef gebruiker mogelijkheid om tegenstander te zoeken */
    printf("\n=== ZOEK TEGENSTANDER ===\n");
    printf("Voer de naam van een tegenstander in: ");
    scanf("%s", zoekNaam);
    
    zoekTegenstander(wedstrijden, aantalWedstrijden, zoekNaam);
    
    return 0;
}